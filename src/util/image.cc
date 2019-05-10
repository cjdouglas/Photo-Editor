#include "util/image.h"

namespace editor {

Image::Image(Halide::Runtime::Buffer<uint8_t> *buf) { this->buf = buf; }

Image::Image(Halide::Runtime::Buffer<uint8_t> &&buf) { this->buf = &buf; }

Halide::Runtime::Buffer<uint8_t> *Image::mutable_buffer() { return buf; }

const Halide::Runtime::Buffer<uint8_t> &Image::buffer() const { return *buf; }

int Image::width() const { return buf->width(); }

int Image::height() const { return buf->height(); }

int Image::channels() const { return buf->channels(); }

} // namespace editor
