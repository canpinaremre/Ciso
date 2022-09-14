#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "imgui.h"
#include <GLFW/glfw3native.h>

class FileDialog {
public:
  static std::string open_file(const char *filter);
  static std::string save_file(const char *filter);
};