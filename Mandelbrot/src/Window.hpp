#pragma once
#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace MSET {
    struct WindowProp {
        std::string title;
        unsigned int width, height;

        WindowProp(const std::string& title = "Default",
                   unsigned int width = 720, unsigned int height = 480)
            : title(title), width(width), height(height) {}
    };

    class Window {
      public:
        Window(std::string title, unsigned int width, unsigned int height);

        ~Window();

        GLFWwindow* GetWindow();

      private:
        GLFWwindow* window;

        WindowProp prop;
    };
} // namespace MSET
