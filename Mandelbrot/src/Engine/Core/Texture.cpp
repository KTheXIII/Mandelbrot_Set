#include "Texture.hpp"

#include "glad/glad.h"

#include "stb/stb_image.h"

namespace EN {
    Texture::Texture(int32_t const& slot_size) {
        m_MaxSlot = slot_size % MAX_TEXTURE_SLOT;
        m_BufferIDs = new u32[m_MaxSlot];
        glGenTextures(m_MaxSlot, m_BufferIDs);
    }

    Texture::~Texture() {
        glDeleteTextures(m_MaxSlot, m_BufferIDs);
        delete[] m_BufferIDs;
    }

    void Texture::Rereate(int32_t const& size) {
        // Clean up the default buffers
        glDeleteTextures(m_MaxSlot, m_BufferIDs);
        delete[] m_BufferIDs;

        // Create new buffers
        m_MaxSlot = size % MAX_TEXTURE_SLOT;
        m_BufferIDs = new u32[m_MaxSlot];
        glGenTextures(m_MaxSlot, m_BufferIDs);
    }

    void Texture::Bind(uint32_t const& slot, uint32_t const& index) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_BufferIDs[index]);
    }

    void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    void Texture::Load(Image const& image) {
        // TEMPORARY
        // TODO: Abstract this away
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image.GetWidth(),
                     image.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     image.GetBuffer());

        glGenerateMipmap(GL_TEXTURE_2D);
    }

}  // namespace EN