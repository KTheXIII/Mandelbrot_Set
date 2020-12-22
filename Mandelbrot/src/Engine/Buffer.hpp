#pragma once

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace EN {

    /**
     * BufferElement
     *
     * Description on what element in the buffer is
     */
    struct BufferElement {
        u32 type;       // Type of data
        u32 count;      // How many data it expect, example: vec3 is 3 count
        u8 normalized;  // If the data is normalized, i.e between 0 and 1

        /**
         * Get type data size
         *
         * @param type OpenGL data type
         *
         * @return Size in byte
         */
        inline static u32 GetSizeOfType(u32 type) {
            switch (type) {
                case GL_FLOAT:
                case GL_UNSIGNED_INT:
                default:
                    return 4;
                case GL_UNSIGNED_BYTE:
                    return 1;
            }
        };
    };

    /**
     * BufferLayout or Vertex Buffer Layout
     *
     * Define how the buffer look like. Used in ArrayBuffer.
     */
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

        inline const std::vector<BufferElement> GetElements() const& {
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
        /**
         * Create Vertex Buffer Object
         *
         * @param data Vertices data
         * @param size Size of the data
         */
        VertexBuffer(const void* data, const u32& size);

        ~VertexBuffer();

        /**
         * Bind the Vertex Buffer Object
         */
        void Bind() const;

        /**
         * Unbind the Vertex Buffer Object
         */
        void Unbind() const;

       private:
        u32 m_BufferID;  // Vertex Buffer Object
    };

    /**
     * Vertex Array Object Buffer.
     *
     * @discussion
     *
     * The Array Buffer is used with Element Buffer to bind the data.
     */
    class ArrayBuffer {
       public:
        /**
         * Create Vertex Array Object Buffer
         */
        ArrayBuffer();

        ~ArrayBuffer();

        /**
         * Bind the Vertex Array Object
         */
        void Bind() const;

        /**
         * Unbind the Vertex Array Object
         */
        void Unbind() const;

        void AddBuffer(const VertexBuffer& vbuffer, const BufferLayout& layout);

       private:
        u32 m_BufferID;  // Vertex Array Buffer Object
    };

    /**
     * Element Array Buffer also known as Index Buffer.
     *
     * @discussion
     *
     * The Element Buffer is used for getting the element count and binding the
     * element. This is used with Array Buffer for drawing.
     */
    class ElementBuffer {
       public:
        /**
         * Create Element Buffer Object
         *
         * @param data Element data
         * @param count Data count
         */
        ElementBuffer(const void* data, const u32& count);

        ~ElementBuffer();

        /**
         * Bind the Element Buffer Object
         */
        void Bind() const;

        /**
         * Unbind the element Buffer Object
         */
        void Unbind() const;

        u32 GetCount() const;

       private:
        u32 m_BufferID;  // Element Array Buffer Object
        u32 m_Count;
    };

}  // namespace EN
