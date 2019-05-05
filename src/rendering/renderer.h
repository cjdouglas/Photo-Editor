#ifndef RENDERING_RENDERER_H_
#define RENDERING_RENDERER_H_

#include <nanogui/glcanvas.h>
#include <nanogui/window.h>

class Renderer : public nanogui::GLCanvas {
public:
  Renderer(nanogui::Widget *parent, GLFWwindow *window);
  bool initProgram();
  virtual void drawGL() override;

private:
  GLFWwindow *window;

  GLuint photo_program = 0;

  GLuint photo_texture;
  GLuint photo_vertex_buffer;

  GLuint a_photo_position_location;
  GLuint a_photo_texture_position_location;
  GLuint u_photo_color_location;
  GLuint u_photo_texture_location;

  float texture_data[16] = {
      -0.5f, 0.5f,  0.f, 0.f, // Top left
      -0.5f, -0.5f, 0.f, 1.f, // Bottom left
      0.5f,  0.5f,  1.f, 0.f, // Top right
      0.5f,  -0.5f, 1.f, 1.f  // Bottom right
  };
};

#endif // RENDERING_RENDERER_H_
