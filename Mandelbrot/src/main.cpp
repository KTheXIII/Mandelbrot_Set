#include <chrono>
#include <iostream>

#include "stb/stb_image_write.h"

#include "Engine/Engine.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char const *argv[]) {
    EN::Window app("Mandelbrot set");

    // clang-format off
    float vertices[] = {
        // positions,             colors,                 texture coordinates
        -0.5f,  0.5f,  0.0f,      1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
         0.5f,  0.5f,  0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
         0.5f, -0.5f,  0.0f,      0.0f, 0.0f, 1.0f,       1.0f, 0.0f,
        -0.5f, -0.5f,  0.0f,      1.0f, 0.0f, 1.0f,       0.0f, 0.0f,
    };

    u32 indices[] = {
        0, 1, 2,
        0, 2, 3,
    };
    // clang-format on
    EN::BufferLayout layout;
    layout.Push(GL_FLOAT, 3);  // Position
    layout.Push(GL_FLOAT, 3);  // Color
    layout.Push(GL_FLOAT, 2);  // Texture coordinate

    EN::Shader s("asset/basic.gl.vert", "asset/basic.gl.frag");
    s.Bind();

    EN::VertexBuffer vb(vertices, sizeof(vertices));
    EN::ElementBuffer eb(indices, sizeof(indices));
    EN::ArrayBuffer ab;
    ab.AddBuffer(vb, layout);

    // TODO: FIX ARRAY BUFFER
    // TODO: FIX so that we can specify what data we want to send it

    vb.Unbind();
    eb.Unbind();
    ab.Unbind();

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
