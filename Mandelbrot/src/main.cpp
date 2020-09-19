#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <string.h>
#include <vector>

#include "stb/stb_image_write.h"

constexpr float default_scale = 1.5f;
constexpr float default_radius = 2.f;

int mandelbrot(const float& x, const float& y, const int& max_iteration,
               const float& scale_x = default_scale,
               const float& scale_y = default_scale,
               const float& offset_x = -.25f, const float& offset_y = 0.f,
               const float& radius = default_radius) {
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
        if (z_real * z_real + z_imaginary * z_imaginary > r2)
            break;

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

int main(int argc, char const* argv[]) {
    GLFWwindow* window;
    int width = 800, height = 600;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, "Mandelbrot set", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
