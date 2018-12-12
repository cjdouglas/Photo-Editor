#ifndef GL_UTIL_GL_SHADER_H_
#define GL_UTIL_GL_SHADER_H_

#include <GL/glew.h>
#include <fstream>
#include <sstream>

GLuint CreateShader(GLenum shader_type, const char *source) {
  std::ifstream ifs;
  std::stringstream ss;
  ifs.open(source);
  if (ifs.fail()) {
    std::cout << "Failed to open file " << source << std::endl;
    return -1;
  }
  ss << ifs.rdbuf();
  ifs.close();

  GL_CHECK(GLuint shader_id = glCreateShader(shader_type));
  std::string temp = ss.str();
  const char *src = temp.c_str();
  GL_CHECK(glShaderSource(shader_id, 1, &src, nullptr));
  GL_CHECK(glCompileShader(shader_id));

  // Check for compilation error
  int result;
  GL_CHECK(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    int length;
    GL_CHECK(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
    auto message = (char *)alloca(length * sizeof(char));
    GL_CHECK(glGetShaderInfoLog(shader_id, length, &length, message));
    std::cout << "Failed to compile "
              << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << " shader" << std::endl;
    std::cout << message << std::endl;
    GL_CHECK(glDeleteShader(shader_id));
    return 0;
  }

  return shader_id;
}

#endif // GL_UTIL_GL_SHADER_H_
