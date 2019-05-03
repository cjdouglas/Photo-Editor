#include "rendering/renderer.h"
#include "format_chunky.h"
#include "gl_util/gl_debug.h"
#include "gl_util/gl_shader.h"

bool Renderer::InitializePrograms() {
  /* Initialize the library */
  if (!glfwInit()) {
    return false;
  }

  window =
      glfwCreateWindow(window_width, window_height, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return false;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    std::cout << "glew init failed" << std::endl;
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

void Renderer::SetTexture(const Halide::Runtime::Buffer<uint8_t> &buffer) {
  GLint image_type = buffer.channels() == 3 ? GL_RGB : GL_RGBA;
  GL_CHECK(glActiveTexture(GL_TEXTURE0));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, photo_texture));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, image_type, buffer.width(),
                        buffer.height(), 0, image_type, GL_UNSIGNED_BYTE,
                        buffer.data()));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                           GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::DrawTexture() {
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

void Renderer::DrawFrame() {
  Halide::Runtime::Buffer<uint8_t> input =
      Halide::Tools::load_image("src/images/dice.png");
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

  SetTexture(output);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    GL_CHECK(glClearColor(0.f, 0.f, 0.f, 1.f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    DrawTexture();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return;
}
