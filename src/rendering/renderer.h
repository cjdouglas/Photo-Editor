#ifndef RENDERING_RENDERER_H_
#define RENDERING_RENDERER_H_

#include <GL/glew.h>
#include <Halide.h>
#include <nanogui/glcanvas.h>
#include <nanogui/window.h>

class Renderer : public nanogui::GLCanvas {
public:
  Renderer(nanogui::Widget *parent);
  bool initProgram();
  void drawTexture();
  void setTexture(const Halide::Runtime::Buffer<uint8_t> &buffer);
  virtual void drawGL() override;

  // Effect setters
  void setBrightness(const float &b) { brightness = b; }

private:
  int texture_width;
  int texture_height;

  GLuint photo_program = 0;

  GLuint photo_texture;
  GLuint photo_vertex_buffer;

  GLuint a_photo_position_location;
  GLuint a_photo_texture_position_location;
  GLuint u_photo_color_location;
  GLuint u_photo_texture_location;

  // Effects
  GLuint u_photo_brightness_location;

  float texture_data[16] = {
      -1.0f, 1.0f,  0.f, 0.f, // Top left
      -1.0f, -1.0f, 0.f, 1.f, // Bottom left
      1.0f,  1.0f,  1.f, 0.f, // Top right
      1.0f,  -1.0f, 1.f, 1.f  // Bottom right
  };

  float brightness = 1.0f;
};

#endif // RENDERING_RENDERER_H_
