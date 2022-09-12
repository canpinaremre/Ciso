#include "gui_main.h"
#include <shellapi.h>
#include <windows.h>

GuiMain::GuiMain() {}

GuiMain::~GuiMain() {}

void GuiMain::MenuBar() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open", "Ctrl+O")) {

        std::thread t([&]() { ciso.open_file(); });

        t.detach();
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) {
      }
      if (ImGui::MenuItem("Save As")) {
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

  ImGui::Text("Welcome to Ciso!");
  ImGui::End();
  ImGui::PopStyleVar();
}
