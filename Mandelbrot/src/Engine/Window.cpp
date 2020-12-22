#include "Window.hpp"

namespace EN {

    Window::Window(const char* title, u32 width, u32 height) {
        m_Data.Title = title;
        m_Data.Width = width;
        m_Data.Height = height;
        m_Data.VSync = true;

        if (!glfwInit()) throw "GLFW not initialized";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_NativeWindow = glfwCreateWindow(m_Data.Width, m_Data.Height,
                                          m_Data.Title.c_str(), NULL, NULL);

        if (!m_NativeWindow) {
            std::cout << "Failed to create GLFW Window" << std::endl;

            glfwTerminate();
            throw "Failed to create GLFW m_Window";
        }

        glfwMakeContextCurrent(m_NativeWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "\u001b[38;5;1mFailed to initialize GLAD\u001b[0m"
                      << std::endl;
            throw "Failed to initialize GLAD";
        }

        // Set the Window data reference in GLFW
        // Used later for getting data from callback
        glfwSetWindowUserPointer(m_NativeWindow, &m_Data);

        SetVSync(m_Data.VSync);

        // Set Window Resize callback
        glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window,
                                                     int width, int height) {
            // Cast the stored pointer to WindowData
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;
        });
    }

    Window::~Window() { glfwDestroyWindow(m_NativeWindow); }

    void Window::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_NativeWindow);
    }

    GLFWwindow* Window::GetNativeWindow() { return m_NativeWindow; }

    void Window::SetVSync(bool enable) {
        glfwSwapInterval(enable ? 1 : 0);
        m_Data.VSync = enable;
    }

    bool Window::IsVSync() { return m_Data.VSync; }

    std::string Window::GetTitle() const { return m_Data.Title; }

    void Window::SetTitle(const std::string title) {
        m_Data.Title = title;

        glfwSetWindowTitle(m_NativeWindow, m_Data.Title.c_str());
    }

    u32 Window::GetWidth() const { return m_Data.Width; }

    u32 Window::GetHeight() const { return m_Data.Height; }

}  // namespace EN
