#include "Application.hpp"

namespace EN {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(new Window("Application"));
    }

    Application::~Application() {}

    void Application::Run() {
        while(m_Window->ShouldClose()) {
            Update();
            Render();

            m_Window->OnUpdate();
        }
    }

}  // namespace EN