#pragma once
#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    struct ShaderSource {
        std::string VS;
        std::string FS;
    };

    /**
     * Shader, compile shader program, bind and unbind.
     *
     * The shader needs to bind before use.
     */
    class Shader {
       public:
        /**
         * Create a shader using Basic shader program.
         *
         * The program require position data (XYZ), color data (RBGA) and uv
         * data.
         */
        Shader();

        /**
         * Create shader form shader program
         *
         * @param vertex_file_path Vertex shader file path
         * @param fragment_file_path Fragment shader file path
         */
        Shader(const char* vertex_file_path, const char* fragment_file_path);

        Shader(const std::string& vertex_file_path,
               const std::string& fragment_file_path);

        ~Shader();

        /**
         * Bind the shader
         */
        void Bind() const;

        /**
         * Unbind the shader
         */
        void Unbind() const;

        /**
         * Get shader program ID
         */
        uint32_t GetID() const;

        /**
         * Set one uniform value
         */
        void SetUniform1(const char* name, const float& value);
        void SetUniform1(const char* name, const int32_t& value);

        /**
         * Set float uniform with 2 value
         *
         * @discussion
         * The shader needs to be bind before we can set the uniform
         *
         * @param[in] name The name of the uniform
         * @param[in] v0 First value
         * @param[in] v1 Second value
         */
        void SetUniform2(const char* name, const float& v0, const float& v1);

        void SetUniform2(const char* name, const int32_t& v0,
                         const int32_t& v1);

        void SetUniform2fv(const char* name, const float* vector,
                           const uint32_t& count = 1);

        /**
         * Set float uniform with 3 value
         *
         * @discussion
         * The shader needs to be bind before we can set the uniform
         *
         * @param[in] name The name of the uniform
         * @param[in] v0 First value
         * @param[in] v1 Second value
         * @param[in] v2 Third value
         */
        void SetUniform3f(const char* name, const float& v0, const float& v1,
                          const float& v2);

        /**
         * Set float uniform with 4 value
         *
         * @discussion
         * The shader needs to be bind before we can set the uniform
         *
         * @param[in] name The name of the uniform
         * @param[in] v0 First value
         * @param[in] v1 Second value
         * @param[in] v2 Third value
         * @param[in] v3 Fourth value
         */
        void SetUniform4f(const char* name, const float& v0, const float& v1,
                          const float& v2, const float& v3);

        /**
         * Set the mat4 uniform
         *
         * @discussion
         * The shader needs to be bind before we can set the uniform
         *
         * @param[in] name The name of the uniform
         * @param[in] value The value pointer
         * @param[in] count Default = 1, useful if the uniform is an array
         * @param[in] transpose Default = false, Specifies whether to transpose
         * the matrix
         */
        void SetUniform4fv(const char* name, const float* value,
                           const uint32_t& count = 1,
                           const bool& transpose = false);

        /**
         * Reload and Recompile shader program
         */
        void Reload();

       private:
        u32 m_ProgramID;      // Shader Program
        std::string m_VPath;  // Vertex Shader source path
        std::string m_FPath;  // Fragment Shader source path

        /**
         * Create shader calls the compiler shader
         *
         * @discussion Compile the given shader program
         */
        u32 CreateShader(const char* vertex_source,
                         const char* fragment_source);

        /**
         * Compile the shader program
         *
         * @param[in] shader_type OpenGL shader type
         * @param[in] source Shader source code
         *
         * @return Shader program
         */
        u32 CompileShader(uint32_t shader_type, const char* source);

        /**
         * Load shader file.
         *
         * @discussion
         *
         * This attempts to read the file if it exist and return the
         * file content
         *
         * @return File contents if it exist else it'll return `ERROR` text.
         */
        std::string LoadShaderFile(const std::string& file_path);

        /**
         * Get Uniform location
         *
         * @param[in] name The name of the uniform
         *
         * @return Uniform location
         */
        u32 GetUniformLocation(const char* name);
    };

    // Basic Vertex Shader program
    const static std::string BASIC_VS =
        "#version 410 core\n"
        "layout(location = 0) in vec3 a_position;"
        "layout(location = 1) in vec4 a_color;"
        "layout(location = 2) in vec2 a_uv;"
        "out vec4 io_color;"
        "out vec2 io_uv;"
        "uniform mat4 u_model;"
        "uniform mat4 u_view;"
        "uniform mat4 u_projection;"
        "void main() {"
        "io_color = a_color;"
        "io_uv = a_uv;"
        "gl_Position = u_projection * u_view * u_model * vec4(a_position, "
        "1.0f);"
        "}";

    // Basic Fragment Shader program
    const static std::string BASIC_FS =
        "#version 410 core\n"
        "#extension GL_ARB_separate_shader_objects : enable\n"
        "layout(location = 0) out vec4 color;"
        "in vec4 io_color;"
        "in vec2 io_uv;"
        "uniform vec4 u_color;"
        "uniform sampler2D u_texture;"
        "void main() {"
        "color = io_color;"
        "}";

}  // namespace EN
