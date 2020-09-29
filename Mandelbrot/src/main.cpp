#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

#include "stb/stb_image_write.h"

#include "Engine/Window.hpp"
#include "Engine/Math.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

std::string load_shader_source(const std::string& file_path) {
    std::ifstream stream(file_path);
    std::stringstream ss;

    if (stream.fail()) {
        std::cout << "Error reading file" << std::endl;
        stream.close();
        return "ERROR";
    }

    if (stream.is_open()) {
        ss << stream.rdbuf();
        stream.close();
    }

    return ss.str();
}

unsigned int compile_shader(unsigned int shader_type,
                            const std::string& source) {
    unsigned int id = glCreateShader(shader_type);
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
        std::cout << "\u001b[31mFailed to compile "
                  << (shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << " shader\u001b[0m" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }

    return id;
};

int main(int argc, char const* argv[]) {
    unsigned int width = 720, height = 480;

    MSET::Window app("Mandelbrot set", width, height);

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
        -0.5f, -0.5f, 0.0f,  // Left
        0.0f,  0.5f,  0.0f,  // Top
        0.5f,  -0.5f, 0.0f   // Right
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

    while (!glfwWindowShouldClose(app.GetWindow())) {
        // inputs
        process_input(app.GetWindow());

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(sp);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(app.GetWindow());
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(sp);

    return 0;
}
