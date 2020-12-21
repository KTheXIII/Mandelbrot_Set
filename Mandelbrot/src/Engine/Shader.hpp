#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    struct ShaderSource {
        std::string vertex;
        std::string fragment;
    };

    class Shader {
       public:
        Shader();

        /**
         * NOT IMPLEMENTED
         */
        Shader(const char* file_path);

        /**
         * Create shader form shader program
         *
         * @param vertex_file_path Vertex shader file path
         * @param fragment_file_path Fragment shader file path
         */
        Shader(const char* vertex_file_path, const char* fragment_file_path);

        ~Shader();

        void Bind() const;

        void Unbind() const;

        uint32_t GetID() const;

       private:
        uint32_t m_ProgramID;  // Shader Program

        uint32_t CreateShader(const char* vertex_source,
                              const char* fragment_source);

        uint32_t CompileShader(uint32_t shader_type, const char* source);

        std::string LoadShaderFile(const char* file_path);
    };

    static std::string basic_vs =
        "#version 410 core\n"
        "layout(location = 0) in vec3 a_position;"
        "layout(location = 1) in vec3 a_color;"
        "layout(location = 2) in vec2 a_uv;"
        "out vec4 io_color;"
        "out vec2 io_uv;"
        "uniform mat4 u_transform;"
        "void main() {"
        "io_color = vec4(a_color, 1.0);"
        "io_uv = a_uv;"
        "gl_Position =vec4(a_position, 1.0f);"
        "}";

    static std::string basic_fs =
        "#version 410 core\n"
        "layout(location = 0) out vec4 color;"
        "in vec4 io_color;"
        "in vec2 io_uv;"
        "uniform vec4 u_color;"
        "uniform sampler2D u_texture;"
        "void main() {"
        "color = vec4(1.0f, 0.0f, 1.0f, 1.0f);"
        "}";

}  // namespace EN
