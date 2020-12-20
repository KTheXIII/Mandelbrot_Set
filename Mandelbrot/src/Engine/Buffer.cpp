#include "Buffer.hpp"

namespace EN {

    void BufferLayout::Push(u32 type, u32 count, bool normalized) {
        m_Elements.push_back({type, count, normalized});
        m_Stride += count * BufferElement::GetSizeOfType(type);
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     */

    VertexBuffer::VertexBuffer(const void *data, const u32 &size) {
        glGenBuffers(1, &m_BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }

    void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     */

    ArrayBuffer::ArrayBuffer() { glGenVertexArrays(1, &m_BufferID); }

    ArrayBuffer::~ArrayBuffer() { glDeleteVertexArrays(1, &m_BufferID); }

    void ArrayBuffer::Bind() const { glBindVertexArray(m_BufferID); }

    void ArrayBuffer::Unbind() const { glBindVertexArray(0); }

    void ArrayBuffer::AddBuffer(const VertexBuffer &vb,
                                const BufferLayout &layout) {
        Bind();
        vb.Bind();
        const auto &elements = layout.GetElements();
        u32 offset = 0;
        for (u32 i = 0; i < elements.size(); i++) {
            const auto &element = elements[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type,
                                  element.normalized, layout.GetStride(),
                                  (const void *)offset);
            offset +=
                element.count * BufferElement::GetSizeOfType(element.type);
        }
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     */

    ElementBuffer::ElementBuffer(const void *data, const u32 &size) {
        glGenBuffers(1, &m_BufferID);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    ElementBuffer::~ElementBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void ElementBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    }

    void ElementBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}  // namespace EN
