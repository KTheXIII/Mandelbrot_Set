#include "Window.hpp"

namespace EN {

    Window::Window(const char* title, const uint32_t& width,
                   const uint32_t& height) {
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

        m_Context = new OpenGLContext(m_NativeWindow);
        m_Context->Init();

        // Set the Window data reference in GLFW
        // Used later for getting data from callback
        glfwSetWindowUserPointer(m_NativeWindow, &m_Data);

        SetVSync(m_Data.VSync);

        // Set Window Resize callback
        glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window,
                                                     int width, int height) {
            // Get the WindowData pointer from GLFW
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;
        });

        // Getting the shader version
        // std::string version = (char*)glGetString(GL_VERSION);
        // std::cout << version << "\n";
    }

    Window::~Window() {
        glfwDestroyWindow(m_NativeWindow);
        glfwTerminate();
    }

    void Window::OnUpdate() {
        // Swap buffers and poll IO events (key pressed/released, mouse moved
        // etc.)
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    GLFWwindow* Window::GetNativeWindow() { return m_NativeWindow; }

    void Window::SetVSync(bool enable) {
        glfwSwapInterval(enable ? 1 : 0);
        m_Data.VSync = enable;
    }

    bool Window::IsVSync() const { return m_Data.VSync; }

    std::string Window::GetTitle() const { return m_Data.Title; }

    void Window::SetTitle(const std::string& title) {
        m_Data.Title = title;

        glfwSetWindowTitle(m_NativeWindow, m_Data.Title.c_str());
    }

    uint32_t Window::GetWidth() const { return m_Data.Width; }

    uint32_t Window::GetHeight() const { return m_Data.Height; }

}  // namespace EN
