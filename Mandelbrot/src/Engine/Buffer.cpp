#include "Buffer.hpp"

namespace EN {

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
        glGenBuffers(1, &m_BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }

    void VertexBuffer::UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ArrayBuffer::ArrayBuffer(uint32_t size) {
        glGenVertexArrays(1, &m_BufferID);
        glBindVertexArray(m_BufferID);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    }

    ArrayBuffer::~ArrayBuffer() { glDeleteVertexArrays(1, &m_BufferID); }

    void ArrayBuffer::Bind() const { glBindVertexArray(m_BufferID); }

    void ArrayBuffer::UnBind() const { glBindVertexArray(0); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    IndexBuffer::IndexBuffer() {}

    IndexBuffer::~IndexBuffer() {}

    void IndexBuffer::Bind() const {}

    void IndexBuffer::UnBind() const {}

}  // namespace EN
