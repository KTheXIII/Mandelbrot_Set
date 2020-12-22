#pragma once

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {
    constexpr u32 DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 480;

    /**
     * Window Properties
     *
     * Will be used later for creating window
     */
    struct WindowProps {
        std::string title;
        u32 width, height;

        WindowProps(const char* title = "Default", u32 width = DEFAULT_WIDTH,
                    u32 height = DEFAULT_HEIGHT)
            : title(title), width(width), height(height) {}
    };

    /**
     * Create a Window
     */
    class Window {
       public:
        /**
         * Create a Window object
         *
         * @discussion
         *
         * This will be change later to use WindowProps for the data properties.
         *
         * @param[in] title The window title
         * @param[in] width Window width, defaults to DEFAULT_WIDTH
         * @param[in] height Window height, defaults to DEFAULT_HEIGHT
         */
        Window(const char* title, u32 width = DEFAULT_WIDTH,
               u32 height = DEFAULT_HEIGHT);

        ~Window();

        /**
         * Needs to be called every loop
         *
         * Swap the buffers and poll the IO events.
         */
        void OnUpdate();

        /**
         * Get GLFW window context
         *
         * @return GLFWwindow context
         */
        GLFWwindow* GetNativeWindow();

        /**
         * Set VSync
         *
         * @param[in] enable True for on and False for off
         */
        void SetVSync(bool enable);

        /**
         * Get If VSync is on
         *
         * @return VSync status
         */
        bool IsVSync() const;

        /**
         * Get window title
         *
         * @return Window title
         */
        std::string GetTitle() const;

        /**
         * Set the window title
         *
         * @param[in] title String
         */
        void SetTitle(const std::string& title);

        /**
         * Get window width
         *
         * @return Window width
         */
        uint32_t GetWidth() const;

        /**
         * Get window height
         *
         * @return Window height
         */
        uint32_t GetHeight() const;

       private:
        GLFWwindow* m_NativeWindow;  // GLFW Window context

        /**
         * Window Data container
         */
        struct WindowData {
            std::string Title;
            u32 Width, Height;
            bool VSync;
        };

        WindowData m_Data;
    };
}  // namespace EN
