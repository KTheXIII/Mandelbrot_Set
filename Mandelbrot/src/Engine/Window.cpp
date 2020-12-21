#include "Window.hpp"

namespace EN {

    Window::Window(const char* title, u32 width, u32 height) {
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
            std::cout << "Failed to create GLFW Window" << std::endl;

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

    std::string Window::GetTitle() const { return m_WindowData.title; }

    void Window::SetTitle(const std::string title) {
        m_WindowData.title = title;

        glfwSetWindowTitle(m_Window, m_WindowData.title.c_str());
    }

}  // namespace EN
