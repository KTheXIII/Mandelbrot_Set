#include "Texture.hpp"

#include "glad/glad.h"

#include "stb/stb_image.h"

namespace EN {
    Texture::Texture() : m_BufferID(0) { glGenTextures(1, &m_BufferID); }

    Texture::~Texture() { glDeleteTextures(1, &m_BufferID); }

    void Texture::Bind(uint32_t const& slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_BufferID);
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