#include "Texture.hpp"

#include "glad/glad.h"

#include "stb/stb_image.h"

namespace EN {
    Texture::Texture()
        : m_BufferID(0),
          m_Filename(""),
          m_LocalBuffer(nullptr),
          m_Width(0),
          m_Height(0),
          m_Channels(0) {
        glGenTextures(1, &m_BufferID);
    }

    Texture::Texture(const char* filename)
        : m_BufferID(0),
          m_Filename(filename),
          m_LocalBuffer(nullptr),
          m_Width(0),
          m_Height(0),
          m_Channels(0) {
        glGenTextures(1, &m_BufferID);
        glBindTexture(GL_TEXTURE_2D, m_BufferID);

        Load();
    }

    Texture::~Texture() { glDeleteTextures(1, &m_BufferID); }

    void Texture::Bind(const uint32_t& slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_BufferID);
    }

    void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    void Texture::LoadTexture(const char* filename) {
        m_Filename = filename;
        glBindTexture(GL_TEXTURE_2D, m_BufferID);

        Load();
    }

    void Texture::LoadTexture(std::string const& filename) {
        LoadTexture(filename.c_str());
    }

    void Texture::Load(const Image& image) {
        Bind();
        m_Width = image.GetWidth();
        m_Height = image.GetHeight();
        m_Channels = image.GetChannels();

        // TEMPORARY
        // TODO: Abstract this away
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, image.GetBuffer());

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture::Load() {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer =
            stbi_load(m_Filename.c_str(), &m_Width, &m_Height, &m_Channels, 4);

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

}  // namespace EN