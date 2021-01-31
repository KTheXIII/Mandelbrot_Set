#pragma once

#include "Core.hpp"
#include "Renderer/RenderingContext.hpp"

#include "OpenGL/OpenGLContext.hpp"

#include "glad/glad.h"

namespace EN {
    constexpr char DEFAULT_TITLE[] = "Application";
    constexpr u32 DEFAULT_WIDTH = 1280, DEFAULT_HEIGHT = 720;

    // Temporary fix for getting the GLSL version
    constexpr char SHADER_VERSION[] = "#version 410";

    /**
     * Create a Window
     */
    class Window {
       public:
        /**
         * Create window with default name and size
         */
        Window();

        /**
         * Create a Window object
         *
         * @discussion
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
        inline GLFWwindow* GetNativeWindow() const { return m_GLFWWindow; }

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
        inline bool IsVSync() const { return m_Data.VSync; }

        /**
         * Get window title
         *
         * @return Window title
         */
        inline std::string GetTitle() const { return m_Data.Title; }

        /**
         * Set the window title
         *
         * @param[in] title Text for the window
         */
        inline void SetTitle(const std::string& title) {
            m_Data.Title = title;
            glfwSetWindowTitle(m_GLFWWindow, m_Data.Title.c_str());
        }

        /**
         * Get window width
         *
         * @return Window width
         */
        inline uint32_t GetWidth() const { return m_Data.Width; };

        /**
         * Get window height
         *
         * @return Window height
         */
        inline uint32_t GetHeight() const { return m_Data.Height; };

        /**
         * Get if the Window should close
         */
        inline bool ShouldClose() const { return m_Data.Running; };

        /**
         * Stop the application
         */
        inline void Close() { m_Data.Running = false; };

        /**
         * Set the window size minimum and maximum
         *
         * @param[in] min_width Minimum width
         * @param[in] min_height Minimum height
         * @param[in] max_width Maximum width, defaults to no limit
         * @param[in] max_height Maximum height, defaults to no limit
         */
        void SetSizeLimit(const int& min_width, const int& min_height,
                          const int& max_width = -1,
                          const int& max_height = -1);

        void SetSize(const int& width, const int& height);

       private:
        GLFWwindow* m_GLFWWindow;     // GLFW Window context
        RenderingContext* m_Context;  // Rendering Context

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
