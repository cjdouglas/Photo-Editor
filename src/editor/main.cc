#include <iostream>

#include "gui/app.h"

int main(void) {
  editor::App app = editor::App(1200, 800);
  app.mainloop();
}
