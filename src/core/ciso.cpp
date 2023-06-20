#include "ciso.h"

int CISO::open_file(std::string path) {

  if(path.empty())
  {
     path = m_file_dialog.open_file("All Files (*.*)\0*.*\0").c_str();
  }
  pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result)
        return -1;// TODO
  
  

  return 0;
}

int CISO::save_file() {
  // TODO: if file name is know, just save, do not open dialog
  
  create_cpp_header(m_file_dialog.save_file("All Files (*.*)\0*.*\0").c_str());

  return 0;
}

int CISO::save_as_file() {
  printf(m_file_dialog.save_file("All Files (*.*)\0*.*\0").c_str());
  return 0;
}

int CISO::create_cpp_header(std::string file_name)
{
  std::ofstream outputFile(file_name);

  if (!outputFile.is_open()) 
  {
    return -1;
  }

  std::string icd_name = doc.child("ICD").attribute("name").value();

  outputFile << "//Auto-generated header file" << std::endl;
  // TODO change icd_name to real xml file name
  outputFile << "//XML source: " << icd_name << std::endl;
  
  outputFile << std::endl;
  outputFile << std::endl;


  outputFile << "#ifndef __" << toUpperCase(icd_name) << "_H__" << std::endl;
  outputFile << "#define __" << toUpperCase(icd_name) << "_H__" << std::endl;

  outputFile << "#include <stdint.h> "<<std::endl;
  outputFile << "#define PACKED __attribute__((packed)) "<<std::endl;

  outputFile << std::endl;
  outputFile << std::endl;

  // For loop for MSG
  pugi::xml_node root = doc.child("MSG");
  recursive_node_cpp(root, 0, outputFile, 0);

  outputFile << std::endl;
  outputFile << std::endl;
  outputFile << "#endif // __"<< toUpperCase(icd_name) << "_H__" << std::endl;
  outputFile.close();
  return 0;
}

void CISO::recursive_node_cpp(pugi::xml_node node, int indentation, std::ofstream& outputFile, unsigned int rez_cnt)
{
  std::string indent(indentation, ' ');
  std::string indent_in(indentation + 1, ' ');

  std::string struct_name = node.attribute("name").value();
  outputFile << indent << "class PACKED " << struct_name << "_t"<<std::endl;
  outputFile << indent << "{" <<std::endl;
  outputFile << indent << "public:" <<std::endl;
  
  for (pugi::xml_node childNode : node.children()) 
  {

    std::string NodeName = childNode.name();

    if(NodeName == "MessageData")
    {
      std::string dataName = childNode.attribute("name").value();
      std::string dataType = type_to_c(childNode.attribute("type").value());
      
      if(dataName.empty())
      {
        dataName = "__rezerve_at_" + std::to_string(rez_cnt);
      }

      outputFile << indent_in << dataType << " " << dataName << ";" <<std::endl;
      rez_cnt += type_to_size(childNode.attribute("type").value());
    }
    else if(NodeName == "MessageDataContainer")
    {

      recursive_node_cpp(childNode, ++indentation, outputFile, rez_cnt);
    
    }
    else if(NodeName == "MessageBitField")
    {
      
    }
    else if(NodeName == "MessageDataArray")
    {
      
      std::string arrayLen = len_to_uint_string(childNode.attribute("len").value());
      std::string dataName = childNode.attribute("name").value();
      if(dataName.empty())
      {
        dataName = "__rezerve_at_" + std::to_string(rez_cnt);
      }
      std::string dataType = type_to_c(childNode.attribute("type").value());
      outputFile << indent_in << dataType << " " << dataName << "[" << arrayLen << "]"<< ";" <<std::endl;
      rez_cnt += type_to_size(childNode.attribute("type").value()) * std::stoul(arrayLen);
    }
  }

  outputFile << indent << "};" <<std::endl;
}

std::string CISO::toUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}
std::string CISO::len_to_uint_string(std::string len)
{
  unsigned int num = std::stoul(len);
  if(num <= 0)
  {
    num = 1;
  }
  return std::to_string(num);
}

std::string CISO::type_to_c(std::string type)
{
  if(type == "UINT8")
  {
    return "uint8_t";
  }
  else if(type == "UINT16")
  {
    return "uint16_t";
  }
  else if(type == "UINT32")
  {
    return "uint32_t";
  }
  else if(type == "UINT64")
  {
    return "uint64_t";
  }
  else if(type == "INT8")
  {
    return "int8_t";
  }
  else if(type == "INT16")
  {
    return "int16_t";
  }
  else if(type == "INT32")
  {
    return "int32_t";
  }
  else if(type == "INT64")
  {
    return "int64_t";
  }
  else if(type == "DOUBLE")
  {
    return "double";
  }
  else if(type == "FLOAT")
  {
    return "float";
  }
  else
    return "uint8_t";
  
}

unsigned int CISO::type_to_size(std::string type)
{
  if(type == "UINT8")
  {
    return sizeof(uint8_t);
  }
  else if(type == "UINT16")
  {
    return sizeof(uint16_t);
  }
  else if(type == "UINT32")
  {
    return sizeof(uint32_t);
  }
  else if(type == "UINT64")
  {
    return sizeof(uint64_t);
  }
  else if(type == "INT8")
  {
    return sizeof(int8_t);
  }
  else if(type == "INT16")
  {
    return sizeof(int16_t);
  }
  else if(type == "INT32")
  {
    return sizeof(int32_t);
  }
  else if(type == "INT64")
  {
    return sizeof(int64_t);
  }
  else if(type == "DOUBLE")
  {
    return sizeof(double);
  }
  else if(type == "FLOAT")
  {
    return sizeof(float);
  }
  else
    return sizeof(uint8_t);
  
}
