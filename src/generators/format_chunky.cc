// This generator is used to change a planar layout image
// to chunky/packed/interleaved format for OpenGL

#include <Halide.h>

class FormatChunkyGenerator : public Halide::Generator<FormatChunkyGenerator> {
public:
  GeneratorParam<bool> vectorize_{"vectorize", true};
  GeneratorParam<bool> parallelize_{"parallelize", true};

  Input<Buffer<uint8_t>> input{"input", 3};
  Output<Buffer<uint8_t>> output{"output", 3};

  Var x, y, c;

  void generate() {
    output(x, y, c) = cast<uint8_t>(min(input(x, y, c) * 1.5f, 255));

    if (vectorize_) {
      output.vectorize(x, natural_vector_size<uint8_t>());
    }

    if (parallelize_) {
      output.parallel(y);
    }
  }
};

HALIDE_REGISTER_GENERATOR(FormatChunkyGenerator, format_chunky)
