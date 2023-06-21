#pragma once

#include <GLFW/glfw3.h>
#include <windows.h>

#include <string>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "imgui.h"

class FileDialog
{
  public:
    static std::string open_file(const char *filter);
    static std::string save_file(const char *filter);
};