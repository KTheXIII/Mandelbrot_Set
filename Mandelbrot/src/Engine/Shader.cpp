#include "Shader.hpp"

namespace EN {
    Shader::Shader() {
        m_ProgramID = CreateShader(basic_vs.c_str(), basic_fs.c_str());
    }

    Shader::Shader(const char* file_path) {}

    Shader::Shader(const char* vertex_file_path, const char* fragment_file_path)
        : m_ProgramID(0) {
        ShaderSource source = {LoadShaderFile(vertex_file_path),
                               LoadShaderFile(fragment_file_path)};

        if (source.vertex.compare("ERROR") == 0) source.vertex = basic_vs;

        if (source.fragment.compare("ERROR") == 0) source.fragment = basic_fs;

        m_ProgramID =
            CreateShader(source.vertex.c_str(), source.fragment.c_str());
    }

    Shader::~Shader() { glDeleteProgram(m_ProgramID); }

    void Shader::Bind() const { glUseProgram(m_ProgramID); }

    void Shader::Unbind() const { glUseProgram(0); }

    u32 Shader::GetID() const { return m_ProgramID; }

    u32 Shader::CreateShader(const char* vertex_source,
                             const char* fragment_source) {
        u32 program = glCreateProgram();

        u32 vs = CompileShader(GL_VERTEX_SHADER, vertex_source);
        u32 fs = CompileShader(GL_FRAGMENT_SHADER, fragment_source);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    u32 Shader::CompileShader(u32 shader_type, const char* source) {
        u32 id = glCreateShader(shader_type);

        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        i32 results;
        glGetShaderiv(id, GL_COMPILE_STATUS, &results);
        if (results == GL_FALSE) {
            i32 length;
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

    std::string Shader::LoadShaderFile(const char* file_path) {
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
