// This generator is used to change a planar layout image
// to chunky/packed/interleaved format for OpenGL.
// The output buffer must be initialized as an interleaved
// buffer (Halide::Runtime::Buffer<T>::make_interleaved)

#include "Halide.h"

class FormatChunkyGenerator : public Halide::Generator<FormatChunkyGenerator> {
public:
  GeneratorParam<bool> vectorize_{"vectorize", true};
  GeneratorParam<bool> parallelize_{"parallelize", true};

  Input<Buffer<uint8_t>> input{"input", 3};
  Output<Buffer<uint8_t>> output{"output", 3};

  Var x, y, c;

  void generate() {
    output(x, y, c) = input(x, y, c);

    output.dim(0).set_stride(input.channels());
    output.dim(1).set_stride(input.width() * input.channels());
    output.dim(2).set_stride(1);

    if (vectorize_) {
      output.vectorize(x, natural_vector_size<uint8_t>());
    }

    if (parallelize_) {
      output.parallel(y);
    }
  }
};

HALIDE_REGISTER_GENERATOR(FormatChunkyGenerator, format_chunky)
