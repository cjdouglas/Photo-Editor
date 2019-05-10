#ifndef UTIL_IMAGE_H_
#define UTIL_IMAGE_H_

#include "Halide.h"

namespace editor {

class Image {
public:
  Image(Halide::Runtime::Buffer<uint8_t> *buf);
  Image(Halide::Runtime::Buffer<uint8_t> &&buf);
  Halide::Runtime::Buffer<uint8_t> *mutable_buffer();
  const Halide::Runtime::Buffer<uint8_t> &buffer() const;
  int width() const;
  int height() const;
  int channels() const;

private:
  Halide::Runtime::Buffer<uint8_t> *buf;
};

} // namespace editor

#endif // UTIL_IMAGE_H_
