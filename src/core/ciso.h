#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <cctype>
#include <fstream>
#include <thread>

#include "c_cpp_header_gen.h"
#include "file_dialog.h"
#include "pugixml.hpp"

#define START_AND_DETACH_THREAD(x)                                                                                     \
    {                                                                                                                  \
        std::thread t([&]() { x; });                                                                                   \
        t.detach();                                                                                                    \
    }

class CISO
{
  public:
    enum
    {
        OK,
        FAIL
    };

  public:
    int open_file(std::string path = std::string());
    int save_file();
    int save_as_file();

  private:
    FileDialog m_file_dialog;
    pugi::xml_document doc;
};
