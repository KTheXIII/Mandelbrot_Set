#pragma once

namespace MSET {
    constexpr float default_scale = 1.5f;
    constexpr float default_radius = 2.0f;
    constexpr float default_offset_x = -0.25f;
    constexpr float default_offset_y = 0.0f;

    int mandelbrot(const float& x, const float& y, const int& max_iteration,
                   const float& scale_x = default_scale,
                   const float& scale_y = default_scale,
                   const float& offset_x = default_offset_x,
                   const float& offset_y = default_offset_y,
                   const float& radius = default_radius);

} // namespace MSET
