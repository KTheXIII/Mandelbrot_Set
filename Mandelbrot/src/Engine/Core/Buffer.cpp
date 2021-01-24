#include "Buffer.hpp"

namespace EN {

    // Buffer Layout

    void BufferLayout::Push(uint32_t type, uint32_t count, bool normalized) {
        u8 nm = normalized ? GL_TRUE : GL_FALSE;
        m_Elements.push_back({type, count, nm});
        m_Stride += count * BufferElement::GetSizeOfType(type);
    }

    // Vertex Buffer

    VertexBuffer::VertexBuffer() { glGenBuffers(1, &m_BufferID); }

    VertexBuffer::VertexBuffer(const void* data, const uint32_t& size) {
        glGenBuffers(1, &m_BufferID);
        LoadData(data, size);
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }

    void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void VertexBuffer::LoadData(const void* data, const uint32_t& size) {
        Bind();
        glBufferData(
            GL_ARRAY_BUFFER, size, data,
            GL_STATIC_DRAW);  // Set the VBO buffer data
                              // STAIC_DRAW is because we set i once and the
                              // data is not changing We want to use other type
                              // if we want to stream the data
    }

    // Array Buffer

    ArrayBuffer::ArrayBuffer() { glGenVertexArrays(1, &m_BufferID); }

    ArrayBuffer::~ArrayBuffer() { glDeleteVertexArrays(1, &m_BufferID); }

    void ArrayBuffer::Bind() const { glBindVertexArray(m_BufferID); }

    void ArrayBuffer::Unbind() const { glBindVertexArray(0); }

    void ArrayBuffer::AddBuffer(const VertexBuffer& vbuffer,
                                const BufferLayout& layout) {
        Bind();
        vbuffer.Bind();
        const auto& elements = layout.GetElements();
        u32 offset = 0;
        for (u32 i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];

            // Vertex Attribute mapped to the location
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type,
                                  element.normalized, layout.GetStride(),
                                  (const void*)offset);
            offset +=
                element.count * BufferElement::GetSizeOfType(element.type);
        }
    }

    // Element/Index Buffer

    ElementBuffer::ElementBuffer() { glGenBuffers(1, &m_BufferID); }

    ElementBuffer::ElementBuffer(const void* data, const uint32_t& count)
        : m_Count(count) {
        glGenBuffers(1, &m_BufferID);
        LoadData(data, count);
    }

    ElementBuffer::~ElementBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void ElementBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    }

    void ElementBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t ElementBuffer::GetCount() const { return m_Count; }

    void ElementBuffer::LoadData(const void* data, const uint32_t& count) {
        m_Count = count;
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(u32), data,
                     GL_STATIC_DRAW);
    }

    // Framebuffer

    Framebuffer::Framebuffer() {}

    Framebuffer::~Framebuffer() {}

    void Framebuffer::Bind() const {}

    void Framebuffer::Unbind() const {}

}  // namespace EN
