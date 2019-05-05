#include "rendering/renderer.h"
#include "gl_util/gl_debug.h"
#include "gl_util/gl_shader.h"

Renderer::Renderer(nanogui::Widget *parent, GLFWwindow *window)
    : nanogui::GLCanvas(parent) {
  this->window = window;
}

bool Renderer::initProgram() {
  if (!glfwInit()) {
    return false;
  }

  glfwMakeContextCurrent(this->window);

  if (!glewInit() != GLEW_OK) {
    return false;
  }

  GL_CHECK(glEnable(GL_BLEND));
  GL_CHECK(glEnable(GL_TEXTURE_2D));
  GL_CHECK(glDisable(GL_CULL_FACE));

  GLuint vertex_shader =
      CreateShader(GL_VERTEX_SHADER, "src/shaders/photo_vsh.glsl");
  GLuint fragment_shader =
      CreateShader(GL_FRAGMENT_SHADER, "src/shaders/photo_fsh.glsl");
  GL_CHECK(photo_program = glCreateProgram());
  GL_CHECK(glAttachShader(photo_program, vertex_shader));
  GL_CHECK(glAttachShader(photo_program, fragment_shader));
  GL_CHECK(glLinkProgram(photo_program));

  // Verify program links correctly
  int link_status;
  GL_CHECK(glGetProgramiv(photo_program, GL_LINK_STATUS, &link_status));
  if (link_status == GL_FALSE) {
    std::cout << "Error linking photo program" << std::endl;
    return false;
  }

  GL_CHECK(a_photo_position_location =
               glGetAttribLocation(photo_program, "a_Position"));
  GL_CHECK(a_photo_texture_position_location =
               glGetAttribLocation(photo_program, "a_TexturePosition"));
  GL_CHECK(u_photo_texture_location =
               glGetUniformLocation(photo_program, "u_Texture"));

  GL_CHECK(glGenBuffers(1, &photo_vertex_buffer));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, photo_vertex_buffer));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(texture_data), texture_data,
                        GL_STATIC_DRAW));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GL_CHECK(glGenTextures(1, &photo_texture));

  return true;
}

void Renderer::drawGL() {
  GL_CHECK(glUseProgram(photo_program));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, photo_vertex_buffer));
  GL_CHECK(glActiveTexture(GL_TEXTURE0));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, photo_texture));

  GL_CHECK(glUniform1i(u_photo_texture_location, 0));
  GL_CHECK(glEnableVertexAttribArray(a_photo_position_location));
  GL_CHECK(glVertexAttribPointer(
      a_photo_position_location, /* size= */ 2, GL_FLOAT, GL_FALSE,
      /* stride= */ 4 * sizeof(float), reinterpret_cast<const void *>(0)));
  GL_CHECK(glEnableVertexAttribArray(a_photo_texture_position_location));
  GL_CHECK(glVertexAttribPointer(
      a_photo_texture_position_location, /* size= */ 2, GL_FLOAT, GL_FALSE,
      /* stride= */ 4 * sizeof(float),
      reinterpret_cast<const void *>(2 * sizeof(float))));

  GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, /* first= */ 0, /* count= */ 4));

  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}
