#include "rendering/renderer.cc"
#include <nanogui/nanogui.h>

using namespace nanogui;

int main(void) {
  nanogui::init();
  Screen *screen = new Screen(Vector2i(1500, 700), "NanoGUI Test");
  FormHelper *gui = new FormHelper(screen);
  ref<Window> window =
      gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
  gui->addGroup("Other widgets");
  gui->addButton("A button",
                 []() { std::cout << "Button pressed." << std::endl; });

  screen->setVisible(true);
  screen->performLayout();
  window->center();

  nanogui::mainloop();
  /*
Renderer renderer;
if (!renderer.InitializePrograms()) {
std::cout << "Renderer failed to initalize programs" << std::endl;
return -1;
}
renderer.DrawFrame();
  */
}
