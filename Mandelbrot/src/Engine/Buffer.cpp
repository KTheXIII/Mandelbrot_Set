#include "Buffer.hpp"

namespace EN {
    VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &m_BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); }

    void VertexBuffer::UnBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    ArrayBuffer::ArrayBuffer(unsigned int size) {
        glGenVertexArrays(1, &m_BufferID);
        glBindVertexArray(m_BufferID);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    }

    ArrayBuffer::~ArrayBuffer() { glDeleteVertexArrays(1, &m_BufferID); }

    void ArrayBuffer::Bind() { glBindVertexArray(m_BufferID); }

    void ArrayBuffer::UnBind() { glBindVertexArray(0); }

    IndexBuffer::IndexBuffer() {}

    IndexBuffer::~IndexBuffer() {}

    void IndexBuffer::Bind() {}

    void IndexBuffer::UnBind() {}
}  // namespace EN
