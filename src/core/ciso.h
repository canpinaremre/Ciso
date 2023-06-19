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
  int create_cpp_header(std::string file_name);
  std::string toUpperCase(const std::string& str);
  std::string type_to_c(std::string type);

private:
  FileDialog m_file_dialog;
  pugi::xml_document doc;
};
