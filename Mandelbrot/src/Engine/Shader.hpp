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
        unsigned int m_ProgramID;  // Shader Program Object

        unsigned int CreateShader(const std::string& vertex_source,
                                  const std::string& fragment_source);

        unsigned int CompileShader(unsigned int shader_type,
                                   const std::string& source);

        std::string LoadShaderFile(const std::string& file_path);
    };

}  // namespace EN
