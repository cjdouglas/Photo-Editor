#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Halide.h>
#include <Halide/Tools/halide_image_io.h>

class Renderer {
public:
  bool InitializePrograms();
  bool InitializeContexts();
  void SetTexture(const Halide::Runtime::Buffer<uint8_t> &buffer);
  void DrawTexture();
  void DrawFrame();

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
