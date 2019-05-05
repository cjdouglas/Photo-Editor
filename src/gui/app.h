#ifndef GUI_APP_H_
#define GUI_APP_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nanogui/screen.h>

class App : public nanogui::Screen {
public:
  App(const int width, const int height);
  void mainloop();

private:
  GLFWwindow *window;

  void buildInterface();
};

#endif // GUI_APP_H_
