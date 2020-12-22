#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <iostream>

#include "Engine.hpp"

#include "stb/stb_image_write.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

    EN::Shader shader("asset/410.basic.gl.vert", "asset/410.basic.gl.frag");
    EN::Texture texture("asset/basic.gl.png");
    texture.Bind();

    // Configure the data for the GPU
    EN::ArrayBuffer ab;
    EN::VertexBuffer vb(vertices, sizeof(vertices));
    EN::ElementBuffer eb(indices, 6);

    ab.AddBuffer(vb, layout);

    // Clean up
    ab.Unbind();
    vb.Unbind();
    eb.Unbind();

    glfwSetFramebufferSizeCallback(app.GetNativeWindow(),
                                   framebuffer_size_callback);

    glm::mat4 model(1.f);  // Use this for transforms

    // Setup camera
    glm::mat4 view(1.f);        // camera/view
    glm::mat4 projection(1.f);  // projection

    // clang-format off
    view = glm::lookAt(
        glm::vec3(0.f, 0.f, -2.f), // Position
        glm::vec3(0.f, 0.f, 0.f), // Target
        glm::vec3(0.f, 1.f, 0.f)  // Up
    );
    // clang-format on

    // projection = glm::perspective(
    //    ((float)M_PI) / 4.f, (float)app.GetWidth() / (float)app.GetHeight(),
    //    0.1f, 100.f);

    float half_width = (float)app.GetWidth() / 2.f;
    float half_height = (float)app.GetHeight() / 2.f;

    float aspect_ratio = (float)app.GetWidth() / (float)app.GetHeight();

    while (!glfwWindowShouldClose(app.GetNativeWindow())) {
        // inputs
        process_input(app.GetNativeWindow());

        half_width = (float)app.GetWidth() / 2.f;
        half_height = (float)app.GetHeight() / 2.f;
        projection = glm::ortho(-half_width, half_width, -half_height,
                                half_height, 0.1f, 100.f);

        model = glm::mat4(1.0f);
        model = glm::scale(
            model, glm::vec3(200.f * (sin((float)glfwGetTime()) + 1.5f)));
        model = glm::rotate(model, (float)glfwGetTime(),
                            glm::vec3(0.0f, 0.0f, 1.0f));

        // Render
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform4fv("u_model", glm::value_ptr(model));
        shader.SetUniform4fv("u_view", glm::value_ptr(view));
        shader.SetUniform4fv("u_projection", glm::value_ptr(projection));

        ab.Bind();  // Bind Array Buffer
        eb.Bind();  // Bind Element/Index Buffer

        glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);

        app.OnUpdate();
    }

    return 0;
}
