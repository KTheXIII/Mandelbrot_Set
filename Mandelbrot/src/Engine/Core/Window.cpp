#include "Window.hpp"

namespace EN {

    Window::Window() : Window(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

    Window::Window(const char* title, const uint32_t& width,
                   const uint32_t& height) {
        m_Data.Title = title;
        m_Data.Width = width;
        m_Data.Height = height;
        m_Data.VSync = true;
        m_Data.Running = true;

        if (!glfwInit()) throw "GLFW not initialized";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_GLFWWindow = glfwCreateWindow(m_Data.Width, m_Data.Height,
                                        m_Data.Title.c_str(), NULL, NULL);

        m_Context = new OpenGLContext(m_GLFWWindow);
        m_Context->Init();

        // Set the Window data reference in GLFW
        // Used later for getting data from callback
        glfwSetWindowUserPointer(m_GLFWWindow, &m_Data);

        SetVSync(m_Data.VSync);

        // Set Window Resize callback
        glfwSetWindowSizeCallback(
            m_GLFWWindow, [](GLFWwindow* window, int width, int height) {
                // Get the WindowData pointer from GLFW
                auto& data =
                    *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                data.Width = width;
                data.Height = height;
            });

        // Set Framebuffer size when it is resized
        glfwSetFramebufferSizeCallback(
            m_GLFWWindow, [](GLFWwindow* window, int width, int height) {
                glViewport(0, 0, width, height);
            });

        // Set the window close event call
        glfwSetWindowCloseCallback(m_GLFWWindow, [](GLFWwindow* window) {
            // Get the WindowData pointer from GLFW
            auto& data =
                *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            data.Running = false;
        });
    }

    Window::~Window() {
        glfwDestroyWindow(m_GLFWWindow);
        glfwTerminate();
    }

    void Window::OnUpdate() {
        // Swap buffers and poll IO events (key pressed/released, mouse moved
        // etc.)
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void Window::SetVSync(bool enable) {
        glfwSwapInterval(enable ? 1 : 0);
        m_Data.VSync = enable;
    }

    void Window::SetSizeLimit(const int& min_width, const int& min_height,
                              const int& max_width, const int& max_height) {
        glfwSetWindowSizeLimits(m_GLFWWindow, min_width, min_height, max_width,
                                max_height);
    }

    void Window::SetSize(const int& width, const int& height) {
        glfwSetWindowSize(m_GLFWWindow, width, height);
    }

}  // namespace EN
