#include "Mandelbrot.hpp"

namespace MSET {
    int mandelbrot(const float& x, const float& y, const int& max_iteration,
                   const float& scale_x, const float& scale_y,
                   const float& offset_x, const float& offset_y,
                   const float& radius) {
        float r2 = radius * radius;

        float z_real = 0;
        float z_real_tmp = 0;

        float z_imaginary = 0;

        float c_real = x * scale_x + offset_x;
        float c_imaginary = y * scale_y + offset_y;

        int iterations = 0;

        for (int i = 0; i < max_iteration; i++) {
            z_real_tmp = z_real * z_real - z_imaginary * z_imaginary + c_real;
            z_imaginary = 2.f * z_real * z_imaginary + c_imaginary;
            z_real = z_real_tmp;

            // dot product instead of sqrt
            if (z_real * z_real + z_imaginary * z_imaginary > r2) break;

            iterations++;
        }

        return iterations;
    }
}  // namespace MSET
