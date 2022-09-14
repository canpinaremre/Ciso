#include "gui_main.h"
#include <shellapi.h>
#include <windows.h>

GuiMain::GuiMain() {}

GuiMain::~GuiMain() {}

void GuiMain::MenuBar() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open", "Ctrl+O")) {
        START_AND_DETACH_THREAD(ciso.open_file());
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) {
        START_AND_DETACH_THREAD(ciso.save_file());
      }
      if (ImGui::MenuItem("Save As", "Ctrl+Shift+S")) {
        START_AND_DETACH_THREAD(ciso.save_as_file());
      }
      if (ImGui::MenuItem("Export")) {
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View")) {
      if (ImGui::BeginMenu("Theme")) {
        if (ImGui::MenuItem("Light")) {
          ImGui::StyleColorsLight();
        }
        if (ImGui::MenuItem("Dark")) {
          ImGui::StyleColorsDark();
        }
        if (ImGui::MenuItem("Classic")) {
          ImGui::StyleColorsClassic();
        }
        ImGui::EndMenu();
      }
      if (ImGui::MenuItem("Docking")) {
      }
      if (ImGui::MenuItem("Search")) {
      }
      if (ImGui::MenuItem("Apperance")) {
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Tools")) {
      if (ImGui::MenuItem("Tool1")) {
      }
      if (ImGui::MenuItem("Tool2")) {
      }
      if (ImGui::MenuItem("Tool3")) {
      }
      if (ImGui::MenuItem("Tool4")) {
      }
      if (ImGui::MenuItem("Tool5")) {
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("Get Started")) {
      }
      if (ImGui::MenuItem("Documentation")) {
      }
      if (ImGui::MenuItem("Release Notes")) {
      }
      if (ImGui::MenuItem("Github")) {
        ShellExecute(NULL, NULL, "https://github.com/canpinaremre/ciso", NULL,
                     NULL, SW_SHOWNORMAL);
      }
      if (ImGui::MenuItem("About")) {
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

void GuiMain::Draw(bool *stay_open) {
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12);
  ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
  ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
  ImGui::Begin("Ciso MainWindow",
               stay_open, // TODO: Get these settings from "View" menu
               ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking |
                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);

  MenuBar();
  static int i = 0;
  ImGui::Text("Welcome to Ciso! %d", i++);
  ImGui::End();
  ImGui::PopStyleVar();

  if (ImGui::IsKeyDown(ImGuiKey_ModCtrl) && ImGui::IsKeyDown(ImGuiKey_O)) {
    START_AND_DETACH_THREAD(ciso.open_file());
  }

  if (ImGui::IsKeyDown(ImGuiKey_ModCtrl) && ImGui::IsKeyDown(ImGuiKey_S)) {
    START_AND_DETACH_THREAD(ciso.save_file());
  }

  if (ImGui::IsKeyDown(ImGuiKey_ModCtrl) && ImGui::IsKeyDown(ImGuiKey_S) &&
      ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
    // TODO: shift catched by another app
    START_AND_DETACH_THREAD(ciso.save_as_file());
  }
}
