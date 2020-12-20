#pragma once

#include <string>
#include <iostream>

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {
    constexpr u32 DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 480;

    struct WindowProp {
        std::string title;
        u32 width, height;

        WindowProp(const char* title = "Default", u32 width = DEFAULT_WIDTH,
                   u32 height = DEFAULT_HEIGHT)
            : title(title), width(width), height(height) {}
    };

    class Window {
       public:
        Window(const char* title, u32 width = DEFAULT_WIDTH,
               u32 height = DEFAULT_HEIGHT);

        ~Window();

        void OnUpdate();

        GLFWwindow* GetWindow();

        void SetVSync(bool enable);

        bool IsVSync();

       private:
        bool m_VSync;
        GLFWwindow* m_Window;

        WindowProp m_WindowData;
    };
}  // namespace EN
