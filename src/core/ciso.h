#pragma once
#include "file_dialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <windows.h>
#include "pugixml.hpp"
#include <fstream>
#include <cctype>

#define START_AND_DETACH_THREAD(x)                                             \
  {                                                                            \
    std::thread t([&]() { x; });                                               \
    t.detach();                                                                \
  }

class CISO {
public:
  enum { OK, FAIL };

public:
  int open_file(std::string path  = std::string());
  int save_file();
  int save_as_file();
  
  std::string toUpperCase(const std::string& str);

  // C/C++ Functions
  std::string len_to_uint_string(std::string len);
  unsigned int type_to_size(std::string type);
  std::string type_to_c(std::string type);

  // C++ Functions
  int create_cpp_header(std::string file_name);
  void recursive_node_cpp(pugi::xml_node node, int indentation, std::ofstream& outputFile, unsigned int rez_cnt);

  // C Functions
  int create_c_header(std::string file_name);

private:
  FileDialog m_file_dialog;
  pugi::xml_document doc;
};
