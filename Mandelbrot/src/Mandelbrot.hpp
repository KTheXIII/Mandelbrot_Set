#pragma once

#include <cmath>

namespace MSET {
    template <typename T, typename = typename std::enable_if<
                              std::is_floating_point<T>::value, T>::type>
    int mandelbrot(T x, T y, int max, T scale = 1.0, T offset_x = 0.0,
                   T offset_y = 0, T radius = 2.0) {
        T r2 = radius * radius;

        T zr = 0;
        T zr_tmp = 0;
        T zi = 0;

        scale = std::pow(2.0, scale);
        T cr = x * scale + offset_x;
        T ci = y * scale + offset_y;

        int iterations = 0;

        for (int i = 0; i < max; i++) {
            zr_tmp = zr * zr - zi * zi + cr;
            zi = 2.0 * zr * zi + ci;
            zr = zr_tmp;

            if (zr * zr + zi * zi > r2) break;

            iterations++;
        }

        return iterations;
    }

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
