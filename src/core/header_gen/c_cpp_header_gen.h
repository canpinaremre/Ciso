#ifndef __C_CPP_HEADER_GEN_H__
#define __C_CPP_HEADER_GEN_H__
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>

#include "pugixml.hpp"
#include "text_manipulator.h"

class C_CPP_HeaderGen
{
  protected:
    std::string file_path;

  public:
    int set_file_path(std::string file_path);
    virtual int create_header(pugi::xml_document &doc);
    std::string get_file_name();
    std::string get_file_path(std::string icd_name);

  protected:
    std::string toCType(std::string type);
    unsigned int typeToSize(std::string type);
};

class CHeaderGen : public C_CPP_HeaderGen
{
  public:
    int create_header(pugi::xml_document &doc) override;
};

class CPPHeaderGen : public C_CPP_HeaderGen
{
  public:
    int create_header(pugi::xml_document &doc) override;
    int recursive_node(pugi::xml_node node, int indentation, std::ofstream &outputFile, unsigned int rez_cnt);
};

#endif // __C_CPP_HEADER_GEN_H__