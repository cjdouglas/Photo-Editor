#ifndef HALIDE____home___cdoug___gitroot___photoeditor_______genfiles___format_chunky___format_chunky_h
#define HALIDE____home___cdoug___gitroot___photoeditor_______genfiles___format_chunky___format_chunky_h
#include <stdint.h>

// Forward declarations of the types used in the interface
// to the Halide pipeline.
//
// For the definitions of these structs, include HalideRuntime.h

// Halide's representation of a multi-dimensional array.
// Halide::Runtime::Buffer is a more user-friendly wrapper
// around this. Its declaration is in HalideBuffer.h
struct halide_buffer_t;

// Metadata describing the arguments to the generated function.
// Used to construct calls to the _argv version of the function.
struct halide_filter_metadata_t;

// The legacy buffer type. Do not use in new code.
struct buffer_t;

#ifndef HALIDE_FUNCTION_ATTRS
#define HALIDE_FUNCTION_ATTRS
#endif



#ifdef __cplusplus
extern "C" {
#endif

int format_chunky(struct halide_buffer_t *_input_buffer, struct halide_buffer_t *_output_buffer) HALIDE_FUNCTION_ATTRS;
int format_chunky_argv(void **args) HALIDE_FUNCTION_ATTRS;
const struct halide_filter_metadata_t *format_chunky_metadata() HALIDE_FUNCTION_ATTRS;


// This allows the includer of this file to get the argv/metadata entry points
// for this file without needing to know the specific function names;
// if HALIDE_GET_STANDARD_ARGV_FUNCTION is defined before this file is
// included, an inline function with that name is provided that return
// a function pointer to the _argv() entry point (similarly,
// HALIDE_GET_STANDARD_METADATA_FUNCTION -> _metadata() entry point).
#ifdef HALIDE_GET_STANDARD_ARGV_FUNCTION
inline int (*HALIDE_GET_STANDARD_ARGV_FUNCTION())(void**) {
    return format_chunky_argv;
}
#endif
#ifdef HALIDE_GET_STANDARD_METADATA_FUNCTION
inline const struct halide_filter_metadata_t* (*HALIDE_GET_STANDARD_METADATA_FUNCTION())() {
    return format_chunky_metadata;
}
#endif


int format_chunky_old_buffer_t(struct buffer_t *_input, struct buffer_t *_output) HALIDE_FUNCTION_ATTRS;

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
