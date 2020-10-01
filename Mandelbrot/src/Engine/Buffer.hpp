#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    class VertexBuffer {
       public:
        VertexBuffer(const void* data, unsigned int size);

        ~VertexBuffer();

        void Bind();

        void UnBind();

       private:
        unsigned int m_BufferID;  // Vertex Buffer Object
    };

    class ArrayBuffer {  // TODO: Fix array buffer
       public:
        ArrayBuffer(unsigned int size);

        ~ArrayBuffer();

        void Bind();

        void UnBind();

       private:
        unsigned int m_BufferID;  // Vertex Array Buffer Object
    };

    class IndexBuffer {
       public:
        IndexBuffer();

        ~IndexBuffer();

        void Bind();

        void UnBind();

       private:
        unsigned int m_BufferID;  // Index Buffer Object
    };

}  // namespace EN
