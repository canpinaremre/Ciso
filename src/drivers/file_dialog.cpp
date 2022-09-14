#include "file_dialog.h"

#include <commdlg.h>

std::string
FileDialog::open_file(const char *filter = "All Files (*.*)\0*.*\0") {

  OPENFILENAMEA ofn;
  CHAR szFile[260] = {0};
  ZeroMemory(&ofn, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = (HWND)ImGui::GetMainViewport()->PlatformHandleRaw;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = filter;
  ofn.nFilterIndex = 1;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
  if (GetOpenFileNameA(&ofn) == TRUE) {
    return ofn.lpstrFile;
  }
  return std::string();
}

std::string FileDialog::save_file(const char *filter) {
  OPENFILENAMEA ofn;
  CHAR szFile[260] = {0};
  ZeroMemory(&ofn, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = (HWND)ImGui::GetMainViewport()->PlatformHandleRaw;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = filter;
  ofn.nFilterIndex = 1;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
  if (GetSaveFileNameA(&ofn) == TRUE) {
    return ofn.lpstrFile;
  }
  return std::string();
}