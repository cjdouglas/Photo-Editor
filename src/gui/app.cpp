#include "gui/app.h"

#include <nanogui/button.h>
#include <nanogui/layout.h>
#include <nanogui/window.h>

using namespace nanogui;

App::App() : Screen(Eigen::Vector2i(1200, 800), "OpenGL Editor", false) {
  Window *window = new Window(this, "OpenGL Editor");
  window.setLayout(new GroupLayout());

  Widget *tools = new Widget(window);
  tools->setLayout(
      new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 5));
  Button *b0 = new Button(tools, "Random Color");
  Button *b1 = new Button(tools, "Random Rotation");
  performLayout();
}

virtual void App::draw(NVGcontext *ctx) { Screen::draw(ctx); }
