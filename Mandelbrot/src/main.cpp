#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

#include "stb/stb_image_write.h"

#include "Engine/Engine.hpp"

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

int main(int argc, char const* argv[]) {
    EN::Window app("Mandelbrot set");

    const std::string vertex_shader_source =
        load_shader_source("Mandelbrot/asset/basic.vert");

    const std::string fragment_shader_source =
        load_shader_source("Mandelbrot/asset/basic.frag");

    EN::Shader s("Mandelbrot/asset/basic.vert", "Mandelbrot/asset/basic.frag");
    s.Bind();

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

        s.Bind();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(app.GetWindow());
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    return 0;
}
