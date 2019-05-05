#include "gui/app.h"
#include "format_chunky.h"

#include <Halide.h>
#include <Halide/Tools/halide_image_io.h>
#include <nanogui/button.h>
#include <nanogui/formhelper.h>
#include <nanogui/layout.h>
#include <nanogui/slider.h>
#include <nanogui/window.h>

#include <iostream>

using namespace nanogui;

namespace {
static void cursorPosCallback(GLFWwindow *window, double x, double y) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->cursorPosCallbackEvent(x, y);
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                int mods) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->mouseButtonCallbackEvent(button, action, mods);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->keyCallbackEvent(key, scancode, action, mods);
}

static void charCallback(GLFWwindow *window, unsigned int codepoint) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->charCallbackEvent(codepoint);
}

static void dropCallback(GLFWwindow *window, int count, const char **paths) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->dropCallbackEvent(count, paths);
}

static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->scrollCallbackEvent(xoffset, yoffset);
}

static void resizeCallbackF(GLFWwindow *window, int width, int height) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->setSize(width, height);
  app->resizeCallbackEvent(width, height);
}
} // namespace

App::App(const int width, const int height) {
  this->width = width;
  this->height = height;

  glfwInit();
  window = glfwCreateWindow(width, height, "Photo Editor", NULL, NULL);
  glfwSetWindowUserPointer(window, this);
  glfwMakeContextCurrent(window);
  initialize(window, true);
  glewInit();
  buildInterface();
}

void App::setSize(const int width, const int height) {
  this->width = width;
  this->height = height;
}

void App::buildInterface() {
  renderer = new Renderer(this);
  renderer->setDrawBorder(false);
  renderer->setBackgroundColor({0, 0, 0, 255});
  renderer->initProgram();

  FormHelper *form = new FormHelper(this);
  ref<Window> nanoWindow =
      form->addWindow(Eigen::Vector2i(10, 10), "Editor Controls");
  form->addButton("Open file", [&] {
    loadFile(
        file_dialog({{"png", "PNG"}, {"jpg", "JPG"}, {"jpeg", "JPEG"}}, false));
  });
  Slider *slider = new Slider(nanoWindow);
  slider->setValue(1.f);
  slider->setRange(std::pair<float, float>(0.5f, 1.5f));
  slider->setCallback([&](float v) { renderer->setBrightness(v); });
  form->addWidget("Brightness", slider);

  setVisible(true);
  performLayout();

  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCharCallback(window, charCallback);
  glfwSetDropCallback(window, dropCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetWindowSizeCallback(window, resizeCallbackF);
}

void App::loadFile(const std::string &path) {
  // Test load texture
  Halide::Runtime::Buffer<uint8_t> input = Halide::Tools::load_image(path);
  if (input.channels() < 3) {
    std::cout << "Error: image has too few channels" << std::endl;
    return;
  }

  Halide::Runtime::Buffer<uint8_t> output =
      Halide::Runtime::Buffer<uint8_t>::make_interleaved(
          input.type(), input.width(), input.height(), input.channels());
  if (format_chunky(input, output) != 0) {
    std::cout << "Error: changing image data layout failed" << std::endl;
    return;
  }

  renderer->setPosition(
      {(width - input.width()) / 2, (height - input.height()) / 2});
  renderer->setSize({input.width(), input.height()});
  renderer->setTexture(output);
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
