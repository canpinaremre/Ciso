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
      if (ImGui::BeginMenu("Open Path")) {
        static char filePath[256] = "";

        ImGui::InputText("##filePath", filePath, 256);
        
        if(ImGui::Button("Open##withpath"))
        {
          ciso.open_file(filePath);
        }
        ImGui::EndMenu();
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
  // Start of main screen
  static int i = 0;
  ImGui::Text("Welcome to Ciso! %d", i++);

  static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | 
  ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;


  if (ImGui::BeginTable("XML Config", 7, flags))
  {
    // Submit columns name with TableSetupColumn() and call TableHeadersRow() to create a row with a header in each column.
    // (Later we will show how TableSetupColumn() has other uses, optional flags, sizing weight etc.)
    ImGui::TableSetupColumn("Variable");
    ImGui::TableSetupColumn("Type");
    ImGui::TableSetupColumn("Len");
    ImGui::TableSetupColumn("coef");
    ImGui::TableSetupColumn("offset");
    ImGui::TableSetupColumn("bswap");
    ImGui::TableSetupColumn("desc");
    ImGui::TableHeadersRow();
    for (int row = 0; row < 6; row++)
    {
      ImGui::TableNextRow();
      for (int column = 0; column < 3; column++)
      {
        ImGui::TableSetColumnIndex(column);
        ImGui::Text("Hello %d,%d", column, row);
      }
    }
    ImGui::EndTable();
  }









  // End of main screen
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
