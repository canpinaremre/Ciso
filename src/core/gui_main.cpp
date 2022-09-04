#include "gui_main.h"

GuiMain::GuiMain() {}

GuiMain::~GuiMain() {}

void GuiMain::Draw(bool *stay_open) {
  ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
  ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
  if (ImGui::Begin("Dear ImGui Demo", stay_open,
                   ImGuiWindowFlags_NoSavedSettings |
                       ImGuiWindowFlags_NoDocking |
                       ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoCollapse)) {

    // Menu Bar
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("Menu")) {
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Examples")) {
        ImGui::MenuItem("Main menu bar", NULL);

        ImGui::EndMenu();
      }
      // if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem()
      // inside a menu bar!
      if (ImGui::BeginMenu("Tools")) {
        ImGui::MenuItem("Metrics/Debugger", NULL);
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }

    ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION,
                IMGUI_VERSION_NUM);

    ImGui::End();
  }
}