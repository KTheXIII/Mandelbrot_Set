#include "Texture.hpp"

namespace EN {

    Texture::Texture(const char* filename)
        : m_BufferID(0),
          m_Filename(filename),
          m_LocalBuffer(nullptr),
          m_Width(0),
          m_Height(0),
          m_Channels(0) {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer =
            stbi_load(filename, &m_Width, &m_Height, &m_Channels, 4);

        glGenTextures(1, &m_BufferID);
        glBindTexture(GL_TEXTURE_2D, m_BufferID);

        // TEMPORARY
        // TODO: Abstract this away
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (m_LocalBuffer) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(m_LocalBuffer);
        } else {
            std::cout << "Failed to load texture\n";
        }

        Unbind();
    }

    Texture::~Texture() { glDeleteTextures(1, &m_BufferID); }

    void Texture::Bind(const uint32_t& slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_BufferID);
    }

    void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

}  // namespace EN