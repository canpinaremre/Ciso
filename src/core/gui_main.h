#include "ciso.h"
#include "imgui.h"

class GuiMain
{
  public:
    GuiMain();
    void Draw(bool *stay_open);
    ~GuiMain();

  public:
    void MenuBar();

    CISO ciso;

  private:
};
