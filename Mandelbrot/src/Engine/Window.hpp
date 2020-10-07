#pragma once
#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {
    constexpr uint32_t DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 480;

    struct WindowProp {
        std::string title;
        uint32_t width, height;

        WindowProp(const std::string& title = "Default",
                   uint32_t width = DEFAULT_WIDTH,
                   uint32_t height = DEFAULT_HEIGHT)
            : title(title), width(width), height(height) {}
    };

    class Window {
       public:
        Window(std::string title, uint32_t width = DEFAULT_WIDTH,
               uint32_t height = DEFAULT_HEIGHT);

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
