#include <chrono>
#include <iostream>

#include "stb/stb_image_write.h"

#include "Engine/Engine.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char const* argv[]) {
    EN::Window app("Mandelbrot set");

    float positions[] = {
        -0.5f, -0.5f, 0.0f,  // Left
        0.0f,  0.5f,  0.0f,  // Top
        0.5f,  -0.5f, 0.0f   // Right
    };

    EN::Shader s("Mandelbrot/asset/basic.vert", "Mandelbrot/asset/basic.frag");
    s.Bind();

    EN::VertexBuffer vb(positions, sizeof(positions));
    EN::ArrayBuffer ab(3);

    vb.UnBind();
    ab.UnBind();

    glfwSetFramebufferSizeCallback(app.GetWindow(), framebuffer_size_callback);

    while (!glfwWindowShouldClose(app.GetWindow())) {
        // inputs
        process_input(app.GetWindow());

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        s.Bind();
        ab.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        app.OnUpdate();
    }

    return 0;
}
