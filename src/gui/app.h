#ifndef GUI_APP_H_
#define GUI_APP_H_

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "nanogui/glcanvas.h"
#include "nanogui/screen.h"
#include "rendering/renderer.h"

namespace editor {

class App : public nanogui::Screen {
public:
  App(const int width, const int height);
  void setSize(const int width, const int height);
  void loadFile(const std::string &path);
  void mainloop();

private:
  int width;
  int height;

  GLFWwindow *window;
  Renderer *renderer;

  void buildInterface();
};

} // namespace editor

#endif // GUI_APP_H_
