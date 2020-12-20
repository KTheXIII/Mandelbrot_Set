#include "Window.hpp"

namespace EN {

    Window::Window(const char* title, uint32_t width, uint32_t height) {
        m_WindowData.title = title;
        m_WindowData.width = width;
        m_WindowData.height = height;

        if (!glfwInit()) throw "GLFW not initialized";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_WindowData.width, m_WindowData.height,
                                    "Mandelbrot set", NULL, NULL);

        if (!m_Window) {
            std::cout << "\u001b[38;5;1mFailed to create GLFW Window\u001b[0m"
                      << std::endl;
            glfwTerminate();
            throw "Failed to create GLFW m_Window";
        }

        SetVSync(true);

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "\u001b[38;5;1mFailed to initialize GLAD\u001b[0m"
                      << std::endl;
            throw "Failed to initialize GLAD";
        }
    }

    Window::~Window() { glfwDestroyWindow(m_Window); }

    void Window::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    GLFWwindow* Window::GetWindow() { return m_Window; }

    void Window::SetVSync(bool enable) {
        glfwSwapInterval(enable ? 1 : 0);
        m_VSync = enable;
    }

    bool Window::IsVSync() { return m_VSync; }

}  // namespace EN
