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
  void setTexture(Halide::Runtime::Buffer<uint8_t> *buffer);
  virtual void drawGL() override;

  // Effect setters
  void setBrightness(const float v) { brightness = v; }
  void setVignetteIntensity(const float v) { vignetteIntensity = v; }
  void setVignetteRadius(const float v) { vignetteRadius = v; }

private:
  Halide::Runtime::Buffer<uint8_t> *texture = nullptr;

  // Programs
  GLuint photo_program = 0;

  // Textures & buffers
  GLuint photo_texture;
  GLuint photo_vertex_buffer;

  // Attributes & uniforms
  GLuint a_photo_position_location;
  GLuint a_photo_texture_position_location;
  GLuint u_photo_color_location;
  GLuint u_photo_texture_location;

  // Effects
  GLuint u_photo_brightness_location;
  GLuint u_photo_vignette_intensity_location;
  GLuint u_photo_vignette_radius_location;

  float texture_data[16] = {
      -1.0f, 1.0f,  0.f, 0.f, // Top left
      -1.0f, -1.0f, 0.f, 1.f, // Bottom left
      1.0f,  1.0f,  1.f, 0.f, // Top right
      1.0f,  -1.0f, 1.f, 1.f  // Bottom right
  };

  int texture_width;
  int texture_height;

  float brightness = 1.0f;
  float vignetteIntensity = 0.0f;
  float vignetteRadius = 0.75f;
};

#endif // RENDERING_RENDERER_H_
