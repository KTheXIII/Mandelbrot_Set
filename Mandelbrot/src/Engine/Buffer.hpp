#pragma once

#include <string>
#include <vector>
#include <type_traits>

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    struct BufferElement {
        u32 type;  // Type of data
        u32 count;
        bool normalized;

        /**
         * Get type data size
         *
         * @param type OpenGL data type
         *
         * @return Size in byte
         */
        static u32 GetSizeOfType(u32 type) {
            switch (type) {
                case GL_FLOAT:
                case GL_UNSIGNED_INT:
                    return 4;
                case GL_UNSIGNED_BYTE:
                    return 1;
            }
        };
    };

    class BufferLayout {
       public:
        BufferLayout() : m_Stride(0){};

        ~BufferLayout(){};

        /**
         * Config the buffer layout.
         *
         * @param type Type of data
         * @param count Data type count, vec3 is 3 and vec4 is 4 etc.
         * @param normalized normalized data, default = false
         */
        void Push(u32 type, u32 count, bool normalized = false);

        inline const std::vector<BufferElement> GetElements() const & {
            return m_Elements;
        }

        inline u32 GetStride() const { return m_Stride; }

       private:
        std::vector<BufferElement> m_Elements;
        u32 m_Stride;
    };

    /**
     * Vertex buffer
     */
    class VertexBuffer {
       public:
        VertexBuffer(const void *data, const u32 &size);

        ~VertexBuffer();

        void Bind() const;

        void Unbind() const;

       private:
        u32 m_BufferID;  // Vertex Buffer Object
    };

    /**
     * Vertex Array Buffer
     */
    class ArrayBuffer {  // TODO: Fix array buffer
       public:
        ArrayBuffer();

        ~ArrayBuffer();

        void Bind() const;

        void Unbind() const;

        void AddBuffer(const VertexBuffer &vb, const BufferLayout &layout);

       private:
        u32 m_BufferID;  // Vertex Array Buffer Object
    };

    /**
     * Element Array Buffer also known as Index Buffer.
     */
    class ElementBuffer {
       public:
        ElementBuffer(const void *data, const u32 &size);
        ~ElementBuffer();

        void Bind() const;

        void Unbind() const;

       private:
        u32 m_BufferID;  // Element Array Buffer Object
    };

}  // namespace EN
