#pragma once

#include "Core/Renderer/RenderingContext.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    class OpenGLContext : public RenderingContext {
       public:
        OpenGLContext(GLFWwindow* windowHandle);
        ~OpenGLContext();

        virtual void Init() override;

        virtual void SwapBuffers() override;

       private:
        GLFWwindow* m_WindowHandle;
    };

}  // namespace EN
