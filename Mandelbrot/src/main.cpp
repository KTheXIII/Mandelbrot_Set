#include <cmath>
#include <chrono>
#include <iostream>
#include <filesystem>

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

namespace fs = std::filesystem;

class App : public EN::Application {
   private:
    EN::BufferLayout layout;

    EN::Shader shader;
    EN::Texture texture;
    EN::ArrayBuffer ab;
    EN::VertexBuffer vb;
    EN::ElementBuffer eb;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

   public:
    App() {
        auto& window = GetWindow();
        window.SetTitle("Mandelbrot set");

        model = glm::mat4(1.f);
        view = glm::mat4(1.f);
        projection = glm::mat4(1.f);
    };

    ~App(){};

    void Init() override {
        // Configure the vertex data layout
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 4);
        layout.Push(GL_FLOAT, 2);

        // TODO: Fix it so path is only get set when in release
        std::string vertex_filename = "410.basic.gl.vert";
        std::string frag_filename = "410.basic.gl.frag";
        shader.LoadData(m_Content.GetPath() + "/asset/" + vertex_filename,
                        m_Content.GetPath() + "/asset/" + frag_filename);

        texture.LoadTexture(m_Content.GetPath() + "/asset/basic.gl.png");
        texture.Bind();

        vb.LoadData((const void*)vertices, sizeof(vertices));
        eb.LoadData(indices, 6);
        eb.Bind();

        ab.AddBuffer(vb, layout);

        ab.Unbind();
        vb.Unbind();
        eb.Unbind();
    }

    void Update() override {
        auto* window = GetWindow().GetNativeWindow();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            GetWindow().Close();
    };

    void Render() override {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform1("u_time", (float)glfwGetTime());

        ab.Bind();  // Bind Array Buffer
        eb.Bind();  // Bind Element/Index Buffer

        glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);
    };
};

int main(int argc, char const* argv[]) {
    auto app = std::make_unique<App>();
    app->SetArgs(argc, argv);
    app->Init();
    app->Run();

    return 0;
}
