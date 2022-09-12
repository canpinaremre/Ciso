#include <string>
#include <windows.h>

class FileDialog {
public:
  static std::string open_file(const char *filter);
  static std::string save_file(const char *filter);
};