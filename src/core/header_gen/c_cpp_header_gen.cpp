#include "c_cpp_header_gen.h"

int C_CPP_HeaderGen::set_file_path(std::string file_path)
{
    if (file_path.empty())
    {
        return false;
    }

    this->file_path = file_path;
    return true;
}

std::string C_CPP_HeaderGen::get_file_path(std::string icd_name = std::string())
{
    if (file_path.empty())
    {
        if (icd_name.empty())
        {
            icd_name = "temp";
        }

        // Remove spaces
        icd_name.erase(std::remove(icd_name.begin(), icd_name.end(), ' '), icd_name.end());

        // Remove non-alphabetic characters
        icd_name.erase(
            std::remove_if(icd_name.begin(), icd_name.end(), [](unsigned char c) { return !std::isalpha(c); }),
            icd_name.end());

        icd_name += ".h";

        return icd_name;
    }
    else
    {
        return file_path;
    }
}

int C_CPP_HeaderGen::create_header(pugi::xml_document &doc)
{
    // virtual func. will be override
}

int CHeaderGen::create_header(pugi::xml_document &doc)
{
}

int CPPHeaderGen::create_header(pugi::xml_document &doc)
{
    std::string icd_name = doc.child("ICD").attribute("name").value();

    std::ofstream outputFile(get_file_path(icd_name));

    if (!outputFile.is_open())
    {
        // TODO error code maybe?
        return false;
    }

    outputFile << "//Auto-generated header file" << std::endl;
    // TODO change icd_name to real xml file name
    outputFile << "//XML source: " << icd_name << std::endl;

    outputFile << std::endl;
    outputFile << std::endl;

    outputFile << "#ifndef __" << toUpperCase(icd_name) << "_H__" << std::endl;
    outputFile << "#define __" << toUpperCase(icd_name) << "_H__" << std::endl;

    outputFile << "#include <stdint.h> " << std::endl;
    outputFile << "#define PACKED __attribute__((packed)) " << std::endl;

    outputFile << std::endl;
    outputFile << std::endl;

    // For loop for MSG
    pugi::xml_node root = doc.child("MSG");
    recursive_node(root, 0, outputFile, 0);

    outputFile << std::endl;
    outputFile << std::endl;
    outputFile << "#endif // __" << toUpperCase(icd_name) << "_H__" << std::endl;
    outputFile.close();
    return 0;
}

int CPPHeaderGen::recursive_node(pugi::xml_node node, int indentation, std::ofstream &outputFile, unsigned int rez_cnt)
{
    std::string indent(indentation, '\t');
    std::string indent_in(indentation + 1, '\t');

    std::string struct_name = node.attribute("name").value();
    outputFile << indent << "class PACKED " << struct_name << "_t" << std::endl;
    outputFile << indent << "{" << std::endl;
    outputFile << indent << "public:" << std::endl;

    for (pugi::xml_node childNode : node.children())
    {
        std::string NodeName = childNode.name();
        std::string dataName = childNode.attribute("name").value();
        std::string dataType = toCType(childNode.attribute("type").value());
        std::string arrayLen = toUintStringNZ(childNode.attribute("len").value());
        std::string repSrc = childNode.attribute("rep_src").value();
        bool doNotPrint = true;

        if (NodeName == "MessageDataContainer")
        {
            doNotPrint = false;

            if (dataName.empty())
            {
                // containers need names
                continue;
            }
            dataType = dataName + "_t";
            unsigned int hold_rez_cnt = rez_cnt;

            recursive_node(childNode, indentation + 1, outputFile, rez_cnt);

            // node size is hold_rez_cnt TODO check
            hold_rez_cnt = rez_cnt - hold_rez_cnt;
            hold_rez_cnt *= (std::stoul(arrayLen) - 1);
            rez_cnt += hold_rez_cnt;
        }

        if (dataName.empty())
        {
            dataName = "__rezerve_at_" + std::to_string(rez_cnt);
        }

        if (NodeName == "MessageData")
        {
            doNotPrint = false;
        }
        else if (NodeName == "MessageBitField")
        {
            doNotPrint = false;

            outputFile << indent_in << "class PACKED " << dataName << "_t" << std::endl;
            outputFile << indent_in << "{" << std::endl;
            outputFile << indent_in << "public:" << std::endl;

            // In terms of bit, size(byte) * 8(bits)
            unsigned int bit_count = typeToSize(childNode.attribute("type").value()) * 8;
            unsigned int pre_res_bits = 0;
            for (pugi::xml_node bitNode : childNode.children())
            {
                std::string bitNode_bitName = bitNode.attribute("name").value();
                if (bitNode_bitName.empty())
                {
                    bitNode_bitName = "rezerve_" + std::to_string(pre_res_bits++);
                }

                std::string bitNode_name = bitNode.name();
                // Only care for MessageBit
                if (bitNode_name == "MessageBit")
                {
                    // Get bit count
                    std::string node_bits_st = bitNode.attribute("bitsize").value();
                    if (node_bits_st.empty())
                    {
                        node_bits_st = "1"; // Default bit size
                    }
                    unsigned int node_bits = std::stoul(node_bits_st);
                    if (node_bits <= 0)
                    {
                        node_bits = 1; // Default bit size
                    }
                    // Keep track of bits left
                    bit_count -= node_bits;
                    addTabs(bitNode_bitName);
                    outputFile << indent_in << "\t" << dataType << " " << bitNode_bitName << ":"
                               << std::to_string(node_bits) << ";" << std::endl;
                }

                // Miss calculated bits, break the loop
                if (bit_count < 0)
                {
                    break;
                }
            }

            // Insert reserve
            if (bit_count)
            {
                std::string bit_rez = "__bit_rez_at_" + std::to_string(rez_cnt);
                addTabs(bit_rez);
                outputFile << indent_in << "\t" << dataType << " " << bit_rez << ":" << std::to_string(bit_count) << ";"
                           << std::endl;
            }

            outputFile << indent_in << "};" << std::endl;
            dataType = dataName + "_t";
            rez_cnt += typeToSize(childNode.attribute("type").value()) * std::stoul(arrayLen);
        }

        if (doNotPrint)
        {
            continue;
        }
        if (repSrc.empty())
        {
            if (arrayLen == "1")
            {
                outputFile << indent_in << dataType << " " << dataName << ";" << std::endl;
            }
            else
            {
                outputFile << indent_in << dataType << " " << dataName << "[" << arrayLen << "];" << std::endl;
            }
        }
        else
        {
            outputFile << indent_in << dataType << " " << dataName << "[1]; // dumy array, src =" << repSrc
                       << std::endl;
        }
    }

    outputFile << indent << "};" << std::endl;

    return true;
}

std::string C_CPP_HeaderGen::toCType(std::string type)
{
    if (type == "UINT8")
    {
        return "uint8_t";
    }
    else if (type == "UINT16")
    {
        return "uint16_t";
    }
    else if (type == "UINT32")
    {
        return "uint32_t";
    }
    else if (type == "UINT64")
    {
        return "uint64_t";
    }
    else if (type == "INT8")
    {
        return "int8_t";
    }
    else if (type == "INT16")
    {
        return "int16_t";
    }
    else if (type == "INT32")
    {
        return "int32_t";
    }
    else if (type == "INT64")
    {
        return "int64_t";
    }
    else if (type == "DOUBLE")
    {
        return "double";
    }
    else if (type == "FLOAT")
    {
        return "float";
    }
    else
        return "uint8_t";
}

unsigned int C_CPP_HeaderGen::typeToSize(std::string type)
{
    if (type == "UINT8")
    {
        return sizeof(uint8_t);
    }
    else if (type == "UINT16")
    {
        return sizeof(uint16_t);
    }
    else if (type == "UINT32")
    {
        return sizeof(uint32_t);
    }
    else if (type == "UINT64")
    {
        return sizeof(uint64_t);
    }
    else if (type == "INT8")
    {
        return sizeof(int8_t);
    }
    else if (type == "INT16")
    {
        return sizeof(int16_t);
    }
    else if (type == "INT32")
    {
        return sizeof(int32_t);
    }
    else if (type == "INT64")
    {
        return sizeof(int64_t);
    }
    else if (type == "DOUBLE")
    {
        return sizeof(double);
    }
    else if (type == "FLOAT")
    {
        return sizeof(float);
    }
    else
        return sizeof(uint8_t);
}