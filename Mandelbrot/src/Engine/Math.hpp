#pragma once
#include <type_traits>

namespace MSET {

    template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value, T>::type>
    T clamp(T x, T min, T max) {
        return x < max ? (x > min ? x : min) : max;
    }

    template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value, T>::type>
    T map(T x, T in_min, T in_max, T out_min, T out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

}  // namespace MSET
