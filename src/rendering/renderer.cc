#include "rendering/renderer.h"
#include "gl_util/gl_debug.h"
#include "gl_util/gl_shader.h"

namespace editor {

Renderer::Renderer(nanogui::Widget *parent) : nanogui::GLCanvas(parent) {}

bool Renderer::initProgram() {
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
  GL_CHECK(u_photo_brightness_location =
               glGetUniformLocation(photo_program, "u_Brightness"));
  GL_CHECK(u_photo_vignette_intensity_location =
               glGetUniformLocation(photo_program, "u_VignetteIntensity"));
  GL_CHECK(u_photo_vignette_radius_location =
               glGetUniformLocation(photo_program, "u_VignetteRadius"));

  GL_CHECK(glGenBuffers(1, &photo_vertex_buffer));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, photo_vertex_buffer));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(texture_data), texture_data,
                        GL_STATIC_DRAW));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GL_CHECK(glGenTextures(1, &photo_texture));

  return true;
}

void Renderer::drawTexture() {
  GL_CHECK(glUseProgram(photo_program));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, photo_vertex_buffer));
  GL_CHECK(glActiveTexture(GL_TEXTURE0));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, photo_texture));

  // Bind uniforms
  GL_CHECK(glUniform1i(u_photo_texture_location, 0));
  GL_CHECK(glUniform1f(u_photo_brightness_location, brightness));
  GL_CHECK(glUniform1f(u_photo_vignette_intensity_location, vignetteIntensity));
  GL_CHECK(glUniform1f(u_photo_vignette_radius_location, vignetteRadius));

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

void Renderer::setTexture(Halide::Runtime::Buffer<uint8_t> *buffer) {
  texture = buffer;
  texture_width = buffer->width();
  texture_height = buffer->height();
  GLint image_type = buffer->channels() == 3 ? GL_RGB : GL_RGBA;
  GL_CHECK(glActiveTexture(GL_TEXTURE0));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, photo_texture));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, image_type, buffer->width(),
                        buffer->height(), 0, image_type, GL_UNSIGNED_BYTE,
                        buffer->data()));

  GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                           GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::drawGL() {
  if (texture != nullptr) {
    drawTexture();
  }
}

} // namespace editor
