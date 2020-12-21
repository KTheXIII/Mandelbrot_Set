#include <chrono>
#include <iostream>

#include "stb/stb_image_write.h"

#include "Engine.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char const* argv[]) {
    EN::Window app("Mandelbrot set");

    // clang-format off
    float vertices[] = {
    //  positions: x,y,z        colors: r,g,b,a,           texture coordinates
        -0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f,    0.0f,  1.0f,
         0.5f,  0.5f,  0.0f,    0.0f, 1.0f, 0.0f, 1.0f,    1.0f,  1.0f,
         0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 1.0f, 1.0f,    1.0f,  0.0f,
        -0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 1.0f, 1.0f,    0.0f,  0.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3,
    };
    // clang-format on

    // Create the layout of the data given
    EN::BufferLayout layout;
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 4);
    layout.Push(GL_FLOAT, 2);

    EN::Shader shader("asset/basic.gl.vert", "asset/basic.gl.frag");

    // Configure the data for the GPU
    EN::ArrayBuffer ab;
    ab.Bind();
    EN::VertexBuffer vb(vertices, sizeof(vertices));
    EN::ElementBuffer eb(indices, 6);

    ab.AddBuffer(vb, layout);

    glfwSetFramebufferSizeCallback(app.GetWindow(), framebuffer_size_callback);

    while (!glfwWindowShouldClose(app.GetWindow())) {
        // inputs
        process_input(app.GetWindow());

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        ab.Bind();  // Bind Array Buffer
        eb.Bind();  // Bind Element/Index Buffer

        glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);

        app.OnUpdate();
    }

    return 0;
}
