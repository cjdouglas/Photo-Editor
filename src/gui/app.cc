#include "gui/app.h"

#include <nanogui/button.h>
#include <nanogui/formhelper.h>
#include <nanogui/layout.h>
#include <nanogui/window.h>

#include <iostream>

using namespace nanogui;

App::App(const int width, const int height) {
  glfwInit();

  this->window = glfwCreateWindow(width, height, "Photo Editor", NULL, NULL);
  glViewport(0, 0, width, height);

  glfwMakeContextCurrent(this->window);
  glewInit();
  buildInterface();
}

void App::buildInterface() {
  this->initialize(window, true);
  FormHelper *form = new FormHelper(this);
  ref<Window> nanoWindow = form->addWindow(Eigen::Vector2i(10, 10), "Test");
  form->addGroup("Basic types");
  bool bval = true;
  std::string sval = "Hello";
  form->addVariable("bool", bval);
  form->addVariable("string", sval);
  form->addGroup("Other widgets");
  form->addButton("A button",
                  []() { std::cout << "Button pressed." << std::endl; });
  setVisible(true);
  performLayout();

  // Callback hell
  glfwSetCursorPosCallback(window, [this](GLFWwindow *, double x, double y) {
    cursorPosCallbackEvent(x, y);
  });
}

void App::mainloop() {
  while (!glfwWindowShouldClose(this->window)) {
    glfwPollEvents();
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->drawContents();
    this->drawWidgets();

    glfwSwapBuffers(this->window);
  }

  glfwTerminate();
}
