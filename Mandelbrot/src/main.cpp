#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

std::string load_shader_source(const std::string& path) {
    std::ifstream stream(path);

    std::string line;
    std::stringstream ss;

    if (stream.is_open()) {
        while (getline(stream, line)) {
            ss << line << '\n';
        }
        stream.close();
    }

    return ss.str();
}

unsigned int compile_shader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int results;
    glGetShaderiv(id, GL_COMPILE_STATUS, &results);
    if (results == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compiled "
                  << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }

    return id;
};

int main(int argc, char const* argv[]) {
    GLFWwindow* window;
    int width = 800, height = 600;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable window resize
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "Mandelbrot set", NULL, NULL);

    if (!window) {
        std::cout << "\u001b[38;5;1mFailed to create GLFW window\u001b[0m"
                  << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback); // register the callback for window reszie

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "\u001b[38;5;1mFailed to initialize GLAD\u001b[0m"
                  << std::endl;
        return -1;
    }

    const std::string vertex_shader_source =
        load_shader_source("Mandelbrot/asset/basic.vert");

    const std::string fragment_shader_source =
        load_shader_source("Mandelbrot/asset/basic.frag");

    unsigned int sp = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    unsigned int fs =
        compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glAttachShader(sp, vs);
    glAttachShader(sp, fs);
    glLinkProgram(sp);

    glDeleteShader(vs);
    glDeleteShader(fs);

    float positions[] = {
        -0.5f, -0.5f, 0.0f, // Left
        0.0f,  0.5f,  0.0f, // Top
        0.5f,  -0.5f, 0.0f  // Right
    };

    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        // inputs
        process_input(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(sp);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(sp);

    glfwTerminate();

    return 0;
}
