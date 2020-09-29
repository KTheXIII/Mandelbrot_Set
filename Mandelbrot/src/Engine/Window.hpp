#pragma once
#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {
    constexpr unsigned int DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 480;

    struct WindowProp {
        std::string title;
        unsigned int width, height;

        WindowProp(const std::string& title = "Default",
                   unsigned int width = DEFAULT_WIDTH,
                   unsigned int height = DEFAULT_HEIGHT)
            : title(title), width(width), height(height) {}
    };

    class Window {
       public:
        Window(std::string title, unsigned int width = DEFAULT_WIDTH,
               unsigned int height = DEFAULT_HEIGHT);

        ~Window();

        GLFWwindow* GetWindow();

        void SetVSync(bool enable);

        bool IsVSync();

       private:
        bool m_VSync;
        GLFWwindow* window;

        WindowProp prop;
    };
}  // namespace EN
