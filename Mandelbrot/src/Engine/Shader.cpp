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

    uint32_t Shader::GetID() const { return m_ProgramID; }

    void Shader::SetUniform1f(const char* name, const f32& value) {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetUniform2f(const char* name, const f32& v0, const f32& v1) {
        glUniform2f(GetUniformLocation(name), v0, v1);
    }

    void Shader::SetUniform3f(const char* name, const f32& v0, const f32& v1,
                              const f32& v3) {
        glUniform3f(GetUniformLocation(name), v0, v1, v3);
    }

    void Shader::SetUniform4f(const char* name, const f32& v0, const f32& v1,
                              const f32& v3, const f32& v4) {
        glUniform4f(GetUniformLocation(name), v0, v1, v3, v4);
    }

    void Shader::SetUniform4fv(const char* name, const f32* value,
                               const u32& count, const bool& transpose) {
        glUniformMatrix4fv(GetUniformLocation(name), count,
                           (transpose ? GL_TRUE : GL_FALSE), value);
    }

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

    uint32_t Shader::CompileShader(uint32_t shader_type, const char* source) {
        u32 id = glCreateShader(shader_type);

        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        i32 results;
        glGetShaderiv(id, GL_COMPILE_STATUS, &results);

        if (results == GL_FALSE) {
            i32 length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            // Allocate memory for message
            char* message = (char*)malloc(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            std::cout << "\n\u001b[31mFailed to compile "
                      << (shader_type == GL_VERTEX_SHADER ? "Vertex"
                                                          : "Fragment")
                      << " shader\u001b[0m\n";
            std::cout << message << "\n";

            // Clean up
            glDeleteShader(id);
            free(message);

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

    u32 Shader::GetUniformLocation(const char* name) {
        return glGetUniformLocation(m_ProgramID, name);
    }

}  // namespace EN
