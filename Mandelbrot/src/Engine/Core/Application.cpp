#include "Application.hpp"

namespace EN {
    Application::Application() { m_Window = std::make_unique<Window>(); }

    Application::~Application() {}

    void Application::Start() {
        Init();
        Run();
    };

    void Application::Start(int argc, char const* argv[]) {
        SetArgs(argc, argv);
        Start();
    }

    void Application::Run() {
        while (m_Window->ShouldClose()) {
            Update();
            Render();

            m_Window->OnUpdate();
        }
    }

}  // namespace EN