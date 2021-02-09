#pragma once

#include "Core/Core.hpp"

namespace EN {

    /**
     * Clamp the input value between min and max
     *
     * @param[in] x Input value
     * @param[in] min The minimum value
     * @param[in] max The maximum value
     *
     * @return The clamped value
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value, T>::type>
    T clamp(T x, T min, T max) {
        return x < max ? (x > min ? x : min) : max;
    }

    /**
     * Map the values linearly
     *
     * @param[in] x The value that should be map
     * @param[in] in_min The min value of the input value
     * @param[in] in_max The max value of the input value
     * @param[in] out_min The min value of the desired output value
     * @param[in] out_max The max value of the dersired output value
     *
     * @return Linearly mapped value
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value, T>::type>
    T map(T x, T in_min, T in_max, T out_min, T out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

}  // namespace EN
