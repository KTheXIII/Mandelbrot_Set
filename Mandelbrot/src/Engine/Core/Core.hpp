#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <filesystem>
#include <chrono>

#include <string>
#include <vector>
#include <type_traits>

#include <stdint.h>

namespace EN {
    // Type defines for internal use only
    // Any external return needs to use the original typedef from stdint.h
    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
    typedef int8_t   i8;
    typedef int16_t  i16;
    typedef int32_t  i32;
    typedef int64_t  i64;
    typedef float    f32;
    typedef double   f64;

    namespace fs = std::filesystem;
}  // namespace EN
