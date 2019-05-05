#ifndef GL_UTIL_GL_DEBUG_H_
#define GL_UTIL_GL_DEBUG_H_

#include <GL/glew.h>
#include <csignal>
#include <iostream>

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    raise(SIGKILL);

#define GL_CHECK(stmt)                                                         \
  GLClearError();                                                              \
  stmt;                                                                        \
  ASSERT(GLLogCall(#stmt, __FILE__, __LINE__))

void GLClearError() {
  while (glGetError() != GL_NO_ERROR) {
  }
}

bool GLLogCall(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] "
              << "(" << error << "):" << function << " " << file << ":" << line
              << std::endl;
    return false;
  }
  return true;
}

#endif // GL_UTIL_GL_DEBUG_H_
