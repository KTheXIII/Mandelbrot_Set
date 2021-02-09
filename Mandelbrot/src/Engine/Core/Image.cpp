#include "Image.hpp"

#include "stb/stb_image.h"

namespace EN {
    Image::Image()
        : m_Width(0),
          m_Height(0),
          m_Channels(0),
          m_IsFlip(0),
          m_Size(0),
          m_IsLoaded(0) {
        m_Buffer = nullptr;
    }

    Image::Image(int32_t const& width, int32_t const& height,
                 int32_t const& channels)
        : m_Width(width),
          m_Height(height),
          m_Channels(channels),
          m_IsFlip(0),
          m_IsLoaded(0) {
        m_Size = m_Width * m_Height * m_Channels;
        m_Buffer = new u8[m_Size];
    }

    Image::~Image() {
        if (!m_IsLoaded)
            delete[] m_Buffer;
        else
            delete m_Buffer;
    }

    void Image::Create(int32_t const& width, int32_t const& height,
                       int32_t const& channels) {
        m_Width = width;
        m_Height = height;
        m_Channels = channels;
        m_Size = m_Width * m_Height * m_Channels;

        if (m_Buffer) delete[] m_Buffer;
        m_Buffer = new u8[m_Size];
    }

    void Image::LoadImage(std::string const& filename,
                          bool const& flip) {
        m_IsFlip = flip;
        m_IsLoaded = true;
        stbi_set_flip_vertically_on_load(m_IsFlip);
        m_Buffer =
            stbi_load(filename.c_str(), &m_Width, &m_Height, &m_Channels, 3);
    }

    void Image::SetPixel(int32_t const& i, uint32_t const& color) {
        u8 red = (u8)(color >> 16);   // Get the red channel
        u8 green = (u8)(color >> 8);  // Get the green channel
        u8 blue = (u8)(color >> 0);   // Get the blue channel

        SetPixel(i, red, green, blue);
    }

    void Image::SetPixel(int32_t const& x, int32_t const& y,
                         uint32_t const& color) {
        u8 red = (u8)(color >> 16);   // Get the red channel
        u8 green = (u8)(color >> 8);  // Get the green channel
        u8 blue = (u8)(color >> 0);   // Get the blue channel

        SetPixel(y * m_Width + x, red, green, blue);
    }

    void Image::SetPixel(int32_t const& x, int32_t const& y, uint8_t const& r,
                         uint8_t const& g, uint8_t const& b, uint8_t const& a) {
        SetPixel(y * m_Width + x, r, g, b, a);
    }

}  // namespace EN