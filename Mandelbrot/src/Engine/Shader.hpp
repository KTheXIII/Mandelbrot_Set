#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

        Shader(const std::string& file_path);

        Shader(const std::string& vertex_file_path,
               const std::string& fragment_file_path);

        ~Shader();

        void Bind() const;

        void UnBind() const;

       private:
        unsigned int m_ProgramID;  // Shader Program

        unsigned int CreateShader(const std::string& vertex_source,
                                  const std::string& fragment_source);

        unsigned int CompileShader(unsigned int shader_type,
                                   const std::string& source);

        std::string LoadShaderFile(const std::string& file_path);
    };

    static std::string basic_vs =
        "#version 410 core\n"
        "#extension GL_ARB_separate_shader_objects : enable\n"
        "layout(location = 0) in vec4 position;\n"
        "void main() {"
        "gl_Position = position;"
        "}";

    static std::string basic_fs =
        "#version 410 core\n"
        "#extension GL_ARB_separate_shader_objects : enable\n"
        "layout(location = 0) out vec4 color;"
        "void main() {"
        "    color = vec4(1.0, 0.0, 1.0, 1.0);"
        "}";

}  // namespace EN
