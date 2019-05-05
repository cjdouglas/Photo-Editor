#include "gui/app.h"

#include <iostream>
#include <nanogui/nanogui.h>

using namespace nanogui;

int main(void) {
  App app = App(1200, 800);
  app.mainloop();
}
