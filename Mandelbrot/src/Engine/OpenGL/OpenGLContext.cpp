#include "OpenGLContext.hpp"

namespace EN {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle) {}

    OpenGLContext::~OpenGLContext() {}

    void OpenGLContext::Init() {
        if (!m_WindowHandle) {
            std::cout << "Failed to create GLFW Window\n";

            glfwTerminate();
            throw "Failed to create GLFW m_Window";
        }

        glfwMakeContextCurrent(m_WindowHandle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD\n";
            throw "Failed to initialize GLAD";
        }
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

}  // namespace EN
