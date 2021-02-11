#include <cmath>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <thread>

#include "Engine.hpp"

#include "imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "stb/stb_image_write.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mandelbrot.hpp"

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
    EN::Texture texture{2};

    EN::ArrayBuffer ab;
    EN::VertexBuffer vb;
    EN::ElementBuffer eb;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    int32_t c_rkey, p_rkey;

    EN::Image image;
    EN::Image image1;

   public:
    App() {
        c_rkey = 0;
        p_rkey = 0;

        auto& window = GetWindow();
        window.SetTitle("Mandelbrot set");

        model = glm::mat4(1.f);
        view = glm::mat4(1.f);
        projection = glm::mat4(1.f);
    };

    ~App(){};

    void Init() override final {
        // Configure the vertex data layout
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 4);
        layout.Push(GL_FLOAT, 2);

        std::string vertex_filename = "410.basic.gl.vert";
        std::string frag_filename = "410.texture.gl.frag";
        shader.Load(m_Content.GetAssetPath(vertex_filename),
                    m_Content.GetAssetPath(frag_filename));

        image.LoadImage(m_Content.GetAssetPath("basic.gl.png"));
        image1.LoadImage(m_Content.GetAssetPath("basic_color.gl.png"));

        shader.Bind();
        texture.Bind(0);
        texture.Load(image);
        shader.SetUniform1("u_texture0", 0);

        texture.Bind(1, 1);
        texture.Load(image1);
        shader.SetUniform1("u_texture1", 1);

        vb.LoadData((const void*)vertices, sizeof(vertices));
        eb.LoadData(indices, 6);
        eb.Bind();

        ab.AddBuffer(vb, layout);

        ab.Unbind();
        vb.Unbind();
        eb.Unbind();
    }

    void Update(EN::Time const& time) override final {
        auto* window = GetWindow().GetNativeWindow();

        p_rkey = c_rkey;
        c_rkey = glfwGetKey(window, GLFW_KEY_R);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            GetWindow().Close();

        if (c_rkey == GLFW_PRESS && p_rkey == GLFW_RELEASE) {
            std::cout << "Reloading shader...\n";
            shader.Reload();
        }
    };

    void Render() override final {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform1("u_time", (float)glfwGetTime());
        shader.SetUniform2("u_resolution", (float)GetWindow().GetWidth(),
                           (float)GetWindow().GetHeight());

        texture.Bind(0);
        texture.Load(image);
        shader.SetUniform1("u_texture0", 0);

        texture.Bind(1, 1);
        texture.Load(image1);
        shader.SetUniform1("u_texture1", 1);

        ab.Bind();  // Bind Array Buffer
        eb.Bind();  // Bind Element/Index Buffer

        glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);
    };
};

int main(int argc, char const* argv[]) {
    auto app = std::make_unique<App>();
    app->Start(argc, argv);

    return 0;
}
