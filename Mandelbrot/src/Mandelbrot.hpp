#pragma once

namespace MSET {
    constexpr int default_iteration = 256;
    constexpr float default_scale = 1.5f;
    constexpr float default_radius = 2.0f;
    constexpr float default_offset_x = -0.25f;
    constexpr float default_offset_y = 0.0f;

    /**
     * Mandelbrot set iterations
     *
     * @param x location
     * @param y location
     * @param max_iteration Number of iterations, default is 256
     * @param offset_x Offset in X
     * @param offset_y Offset in Y
     * @param scale_x Scale in X direction
     * @param scale_y Scale in Y direction
     * @param radius Escape radius
     * @return Number of iteration inside escape radius
     */
    int mandelbrot(const float& x, const float& y,
                   const int& max_iteration = default_iteration,
                   const float& offset_x = default_offset_x,
                   const float& offset_y = default_offset_y,
                   const float& scale_x = default_scale,
                   const float& scale_y = default_scale,
                   const float& radius = default_radius);

}  // namespace MSET
