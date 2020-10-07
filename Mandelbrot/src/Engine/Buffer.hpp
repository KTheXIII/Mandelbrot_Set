#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    class VertexBuffer {
       public:
        VertexBuffer(const void* data, uint32_t size);

        ~VertexBuffer();

        void Bind() const;

        void UnBind() const;

       private:
        uint32_t m_BufferID;  // Vertex Buffer Object
    };

    class ArrayBuffer {  // TODO: Fix array buffer
       public:
        ArrayBuffer(uint32_t size);

        ~ArrayBuffer();

        void Bind() const;

        void UnBind() const;

       private:
        uint32_t m_BufferID;  // Vertex Array Buffer Object
    };

    class IndexBuffer {
       public:
        IndexBuffer();

        ~IndexBuffer();

        void Bind() const;

        void UnBind() const;

       private:
        uint32_t m_BufferID;  // Index Buffer Object
    };

}  // namespace EN
