#include "util/image.h"

namespace editor {

Image::Image(Halide::Runtime::Buffer<uint8_t> *buf) { this->buf = buf; }

Image::Image(Halide::Runtime::Buffer<uint8_t> &&buf) { this->buf = &buf; }

Image::~Image() { delete buf; }

Halide::Runtime::Buffer<uint8_t> *Image::mutable_buffer() { return buf; }

const Halide::Runtime::Buffer<uint8_t> &Image::buffer() const { return *buf; }

halide_type_t Image::type() const { return buf->type(); }

int Image::width() const { return buf->width(); }

int Image::height() const { return buf->height(); }

int Image::channels() const { return buf->channels(); }

} // namespace editor
