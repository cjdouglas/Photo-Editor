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
  renderer->setVisible(false);

  FormHelper *form = new FormHelper(this);
  ref<Window> nanoWindow =
      form->addWindow(Eigen::Vector2i(10, 10), "Editor Controls");
  form->addButton("Open file", [&] {
    loadFile(
        file_dialog({{"png", "PNG"}, {"jpg", "JPG"}, {"jpeg", "JPEG"}}, false));
  });

  form->addGroup("Color");
  Slider *brightnessSlider = new Slider(nanoWindow);
  brightnessSlider->setValue(1);
  brightnessSlider->setRange({0.5, 1.5});
  brightnessSlider->setCallback([&](float v) { renderer->setBrightness(v); });
  form->addWidget("Brightness", brightnessSlider);

  form->addGroup("Vignette");
  Slider *vignetteIntensity = new Slider(nanoWindow);
  Slider *vignetteRadius = new Slider(nanoWindow);
  vignetteIntensity->setValue(0);
  vignetteIntensity->setRange({0, 0.75});
  vignetteIntensity->setCallback(
      [&](float v) { renderer->setVignetteIntensity(v); });
  vignetteRadius->setValue(0.75);
  vignetteRadius->setRange({0.5, 1});
  vignetteRadius->setCallback([&](float v) { renderer->setVignetteRadius(v); });
  form->addWidget("Intensity", vignetteIntensity);
  form->addWidget("Radius", vignetteRadius);

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
      {(width - output.width()) / 2, (height - output.height()) / 2});
  renderer->setSize({output.width(), output.height()});
  renderer->setTexture(&output);
  if (!renderer->visible()) {
    renderer->setVisible(true);
  }
}

void App::mainloop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawContents();
    drawWidgets();

    glfwSwapBuffers(window);
  }

  glfwTerminate();
}
