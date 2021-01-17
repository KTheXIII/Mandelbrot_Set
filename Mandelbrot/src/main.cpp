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

int main(int argc, char const* argv[]) {
    EN::Window app("Mandelbrot set");
    bool vsync = true;
    app.SetVSync(vsync);

    // GLFWimage images[1];
    // images[0].pixels = stbi_load("asset/icon.gl.png", &images[0].width,
    //                             &images[0].height, 0, 4);
    // glfwSetWindowIcon(app.GetNativeWindow(), 1, images);
    // stbi_image_free(images[0].pixels);

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

    std::string vertex_filename = "410.basic.gl.vert";
    std::string frag_filename = "410.mandelbrot.gl.frag";

    EN::Shader shader("asset/" + vertex_filename, "asset/" + frag_filename);
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

    int32_t r_current = 0, r_last = 0;
    double mouse_x, mouse_y;

    double offset_x = 0., offset_y = 0.;
    double scale = 1.;
    double speed = 1.;

    double last_time = 0, current_time = 0;
    double frametime = 0;

    auto update = [&](GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        r_last = r_current;
        r_current = glfwGetKey(app.GetNativeWindow(), GLFW_KEY_R);

        if (r_current == GLFW_PRESS && r_last == GLFW_RELEASE) {
            std::cout << "Reloading shader...\n";
            shader.Reload();
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            offset_y += speed * frametime * std::pow(2., scale) * .5;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            offset_y -= speed * frametime * std::pow(2., scale) * .5;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            offset_x += speed * frametime * std::pow(2., scale) * .5;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            offset_x -= speed * frametime * std::pow(2., scale) * .5;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            scale -= speed * frametime * .5;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            scale += speed * frametime * .5;
        }

        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        half_width = (float)app.GetWidth() / 2.f;
        half_height = (float)app.GetHeight() / 2.f;
    };

    auto render = [&]() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        ImGui::Text("Frametime: %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::Text("Fragment Shader: %s", frag_filename.c_str());
        ImGui::Text("Location: %.4f, %.4f", offset_x, offset_y);
        ImGui::Text("Scale: 2^%.2f", scale);

        ImGui::End();

        // Render
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();

        shader.SetUniform1f("u_time", (float)glfwGetTime());
        shader.SetUniform4fv("u_model", glm::value_ptr(model));
        shader.SetUniform4fv("u_view", glm::value_ptr(view));
        shader.SetUniform4fv("u_projection", glm::value_ptr(projection));
        shader.SetUniform2f("u_resolution", app.GetWidth(), app.GetHeight());
        shader.SetUniform2f("u_mouse", (float)mouse_x, (float)mouse_y);

        shader.SetUniform1f("u_scale", scale);
        shader.SetUniform2f("u_offset", offset_x, offset_y);

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
    };

    while (!glfwWindowShouldClose(app.GetNativeWindow())) {
        last_time = current_time;
        current_time = glfwGetTime();
        frametime = current_time - last_time;

        update(app.GetNativeWindow());
        render();

        app.OnUpdate();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
