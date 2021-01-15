#pragma once

#include "Core.hpp"
#include "Renderer/RenderingContext.hpp"

#include "OpenGL/OpenGLContext.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {
    constexpr u32 DEFAULT_WIDTH = 1280, DEFAULT_HEIGHT = 800;

    // Temporary fix for getting the GLSL version
    constexpr char SHADER_VERSION[] = "#version 410";

    /**
     * Window Properties
     *
     * Will be used later for creating window
     */
    struct WindowProps {
        std::string title;
        u32 width, height;

        WindowProps(const char* title = "Default",
                    const uint32_t& width = DEFAULT_WIDTH,
                    const uint32_t& height = DEFAULT_HEIGHT)
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
        Window(const char* title, const uint32_t& width = DEFAULT_WIDTH,
               const uint32_t& height = DEFAULT_HEIGHT);

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
         * Get VSync setting
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

        inline bool ShouldClose() const { return m_Data.Running; }

       private:
        GLFWwindow* m_NativeWindow;  // GLFW Window context
        RenderingContext* m_Context;

        /**
         * Window Data container
         *
         * This will be the container for getting data from callbacks
         */
        struct WindowData {
            std::string Title;
            u32 Width, Height;
            bool VSync;
            bool Running;
        };

        WindowData m_Data;  // This is set in GLFW user pointer
    };
}  // namespace EN
