#include "Window.hpp"

namespace MSET {

    Window::Window(std::string title, unsigned int width, unsigned int height) {
        prop.title = title;
        prop.width = width;
        prop.height = height;

        if (!glfwInit())
            throw "GLFW not initialized";

        glfwWindowHint(GLFW_RESIZABLE,
                       GLFW_TRUE); // Disable window resize
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(prop.width, prop.height, "Mandelbrot set",
                                  NULL, NULL);

        if (!window) {
            std::cout << "\u001b[38;5;1mFailed to create GLFW window\u001b[0m"
                      << std::endl;
            glfwTerminate();
            throw "Failed to create GLFW window";
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "\u001b[38;5;1mFailed to initialize GLAD\u001b[0m"
                      << std::endl;
            throw "Failed to initialize GLAD";
        }
    }

    Window::~Window() { glfwDestroyWindow(window); }

    GLFWwindow* Window::GetWindow() { return window; }
} // namespace MSET