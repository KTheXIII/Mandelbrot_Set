#pragma once

namespace MSET {

    class VertexBuffer {
       public:
        VertexBuffer();

        ~VertexBuffer();

        void Bind();

        void UnBind();

       private:
        unsigned int m_BufferID;  // Vertex Buffer Object
    };

    class ArrayBuffer {
       public:
        ArrayBuffer();

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

}  // namespace MSET
