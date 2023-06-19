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

  outputFile << "//Auto-generated header file" << std::endl;
  outputFile << "//XML source: TODO" << std::endl;
  
  outputFile << std::endl;
  outputFile << std::endl;

  pugi::xml_node root = doc.child("ICD");
  std::string struct_name = root.attribute("name").value();

  outputFile << "#ifndef "<< toUpperCase(struct_name) << std::endl;
  outputFile << "#define "<< toUpperCase(struct_name) << std::endl;

  outputFile << "#include <stdint.h> "<<std::endl;
  outputFile << "#define PACKED __attribute__((packed)) "<<std::endl;

  outputFile << std::endl;
  outputFile << std::endl;


  outputFile << "class PACKED " <<struct_name << "_t"<<std::endl;
  outputFile << "{" <<std::endl;
  outputFile << "public:" <<std::endl;


  for (pugi::xml_node childNode : root.children()) 
  {
    std::string nodeName = childNode.attribute("name").value();
    std::string nodeType = type_to_c(childNode.attribute("type").value());

    outputFile << "  "<< nodeType << " " << nodeName << ";" <<std::endl;
  }

  outputFile << "};" <<std::endl;


  outputFile << std::endl;
  outputFile << std::endl;
  outputFile << "#endif // "<< toUpperCase(struct_name) << std::endl;
  outputFile.close();
  return 0;
}

std::string CISO::toUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
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
    return "uint64t";
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
    return "int64t";
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