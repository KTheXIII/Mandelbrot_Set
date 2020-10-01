#include "Shader.hpp"

namespace EN {
    Shader::Shader() { m_ProgramID = CreateShader(basic_vs, basic_fs); }

    Shader::Shader(const std::string& file_path) {}

    Shader::Shader(const std::string& vertex_file_path,
                   const std::string& fragment_file_path)
        : m_ProgramID(0) {
        ShaderSource source = {LoadShaderFile(vertex_file_path),
                               LoadShaderFile(fragment_file_path)};

        if (source.vertex.compare("ERROR") == 0) {
            source.vertex = basic_vs;
        }

        if (source.fragment.compare("ERROR") == 0) {
            source.fragment = basic_fs;
        }

        m_ProgramID = CreateShader(source.vertex, source.fragment);
    }

    Shader::~Shader() { glDeleteProgram(m_ProgramID); }

    void Shader::Bind() const { glUseProgram(m_ProgramID); }

    void Shader::UnBind() const { glUseProgram(0); }

    unsigned int Shader::CreateShader(const std::string& vertex_source,
                                      const std::string& fragment_source) {
        unsigned int program = glCreateProgram();

        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_source);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_source);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    unsigned int Shader::CompileShader(unsigned int shader_type,
                                       const std::string& source) {
        unsigned int id = glCreateShader(shader_type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int results;
        glGetShaderiv(id, GL_COMPILE_STATUS, &results);
        if (results == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "\n\u001b[31mFailed to compile "
                      << (shader_type == GL_VERTEX_SHADER ? "Vertex"
                                                          : "Fragment")
                      << " shader\u001b[0m" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);

            return 0;
        }

        return id;
    };

    std::string Shader::LoadShaderFile(const std::string& file_path) {
        std::ifstream stream(file_path);
        std::stringstream ss;

        if (stream.fail()) {
            std::cout << "Error reading shader file" << std::endl;
            stream.close();
            return "ERROR";
        }

        if (stream.is_open()) {
            ss << stream.rdbuf();
            stream.close();
        }

        return ss.str();
    }
}  // namespace EN
