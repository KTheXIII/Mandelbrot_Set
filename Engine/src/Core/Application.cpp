#include "Application.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(new Window());
    }

    Application::~Application() {}

    void Application::Run() {
        while (m_Window->ShouldClose()) {
            glClearColor(255. / 255., 66. / 255., 98. / 255., 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();
        }
    }

}  // namespace EN
