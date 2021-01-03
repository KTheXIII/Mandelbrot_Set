#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <iostream>

#include "Engine.hpp"

#include "imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "stb/stb_image_write.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// TODO: Create a renderer
// TODO: Userinterface for generating image

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char const* argv[]) {
    EN::Window app("Mandelbrot set");

    //GLFWimage images[1];
    //images[0].pixels = stbi_load("asset/icon.gl.png", &images[0].width,
    //                             &images[0].height, 0, 4);
    //glfwSetWindowIcon(app.GetNativeWindow(), 1, images);
    //stbi_image_free(images[0].pixels);

    // clang-format off

    // Quad
    float vertices[] = {
    //  positions: x,y,z        colors: r,g,b,a            texture coordinates
        -1.0f,  1.0f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f,    0.0f,  1.0f,
         1.0f,  1.0f,  0.0f,    0.0f, 1.0f, 0.0f, 1.0f,    1.0f,  1.0f,
         1.0f, -1.0f,  0.0f,    0.0f, 0.0f, 1.0f, 1.0f,    1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,    1.0f, 0.0f, 1.0f, 1.0f,    0.0f,  0.0f,
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

    EN::Shader shader("asset/410.basic.gl.vert", "asset/410.star_field.gl.frag");
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
    //view = glm::lookAt(
    //    glm::vec3(0.f, 0.f, 10.f), // Position
    //    glm::vec3(0.f, 0.f, 0.f), // Target
    //    glm::vec3(0.f, 1.f, 0.f)  // Up
    //);
    // clang-format on

    // projection = glm::perspective(
    //   ((float)M_PI) / 4.f, (float)app.GetWidth() / (float)app.GetHeight(),
    //   0.1f, 1000.f);

    float half_width = (float)app.GetWidth() / 2.f;
    float half_height = (float)app.GetHeight() / 2.f;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
    io.ConfigFlags |=
        ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform
                                           // Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(app.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init(EN::SHADER_VERSION);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool check_box = false;
    float scale = .9f;

    int32_t e_current = 0, e_last = 0;

    while (!glfwWindowShouldClose(app.GetNativeWindow())) {
        // inputs
        process_input(app.GetNativeWindow());

        e_last = e_current;
        e_current = glfwGetKey(app.GetNativeWindow(), GLFW_KEY_R);

        if (e_current == GLFW_PRESS && e_last == GLFW_RELEASE) {
            shader.Reload();
        }

        double mouse_x, mouse_y;
        glfwGetCursorPos(app.GetNativeWindow(), &mouse_x, &mouse_y);

        mouse_x = (double)app.GetWidth() / 2 - mouse_x;
        mouse_y = (double)app.GetHeight() / 2 - mouse_y;

        half_width = (float)app.GetWidth() / 2.f;
        half_height = (float)app.GetHeight() / 2.f;
        // projection = glm::ortho(-half_width, half_width, -half_height,
        //                        half_height, 0.1f, 100.f);

        // model = glm::mat4(1.0f);
        // model = glm::scale(model, glm::vec3(250.f));
        // model = glm::scale(model, glm::vec3((app.GetWidth() > app.GetHeight()
        //                                        ? app.GetWidth()
        //                                        : app.GetHeight()) /
        //                                   2));

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        ImGui::Text("Frametime: %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();

        // Render
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform1f("u_time", glfwGetTime());
        shader.SetUniform4fv("u_model", glm::value_ptr(model));
        shader.SetUniform4fv("u_view", glm::value_ptr(view));
        shader.SetUniform4fv("u_projection", glm::value_ptr(projection));
        shader.SetUniform2f("u_resolution", app.GetWidth(), app.GetHeight());
        shader.SetUniform2f("u_mouse", mouse_x, mouse_y);

        ab.Bind();  // Bind Array Buffer
        eb.Bind();  // Bind Element/Index Buffer

        glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);

        // Rendering ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        app.OnUpdate();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
