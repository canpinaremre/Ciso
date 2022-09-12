#include "ciso.h"

int CISO::open_file() {
  printf(file_dialog.open_file("All Files (*.*)\0*.*\0").c_str());
  return 0;
}
