#pragma once

#include "Core.hpp"

namespace EN {

    /**
     * The image class contains the image color data.
     */
    class Image {
       public:
        /**
         * Create an emtpy image with 0 on width and height
         */
        Image();

        /**
         * Create an image with dimension of width and height.
         *
         * @param[in] width The image width in pixels
         * @param[in] height The image height in pixels
         * @param[in] channels The image color channels (optional), default is 3
         */
        Image(int32_t const& width, int32_t const& height,
              int32_t const& channels = 3);

        virtual ~Image();

        /**
         * Create an image with width, height and undefined color data
         *
         * @param[in] width The width of the image in pixels
         * @param[in] height The height of the image in pixels
         * @param[in] channels The image color channels, (OPTIONAL)
         */
        void Create(int32_t const& width, int32_t const& height,
                    int32_t const& channels = 3);

        /**
         * Load an image from file
         *
         * @param[in] filename The name of file.
         */
        void LoadImage(std::string const& filename);

        /**
         * Get the image width in pixels
         *
         * @return Image width
         */
        inline int32_t GetWidth() const { return m_Width; }

        /**
         * Get the image height in pixels
         *
         * @return Image height
         */
        inline int32_t GetHeight() const { return m_Height; }

        /**
         * Get the image color channels
         *
         * @return Image color channel size
         */
        inline int32_t GetChannels() const { return m_Channels; }

        /**
         * Get image raw size in bytes
         *
         * @return Image size in bytes
         */
        inline int32_t GetSize() const {
            return m_Width * m_Height * m_Channels * sizeof(uint8_t);
        }

        /**
         * Set pixel color using index location with 32-bit hex color
         *
         * @param[in] i Pixel location index
         * @param[in] color Hex color 32-bit
         */
        void SetPixel(int32_t const& i, uint32_t const& color);

        /**
         * Set pixel color using x,y location with 32-bit hex color
         *
         * @param[in] x Pixel x location from the left
         * @param[in] y Pixel y location from the right
         * @param[in] color Hex color 32-bit
         */
        void SetPixel(int32_t const& x, int32_t const& y,
                      uint32_t const& color);

        /**
         * Set the pixel color using x,y location
         *
         * @param[in] x Pixel x location from the left
         * @param[in] y Pixel y location from the right
         * @param[in] r Red channel
         * @param[in] g Green channel
         * @param[in] b Blue channel
         * @param[in] a Alpha channel, default is 0xFF
         */
        void SetPixel(int32_t const& x, int32_t const& y, uint8_t const& r,
                      uint8_t const& g, uint8_t const& b,
                      uint8_t const& a = 0xFF);

        /**
         * Set pixel color using index location with RGB[A] color.
         *
         * @param[in] i Pixel location index
         * @param[in] r Red channel (8-bit)
         * @param[in] g Green channel (8-bit)
         * @param[in] b Blue channel (8-bit)
         * @param[in] a Alpha channel (8-bit) only used if channels is > 3
         */
        inline void SetPixel(int32_t const& i, uint8_t const& r,
                             uint8_t const& g, uint8_t const& b,
                             uint8_t const& a = 0xFF) {
            int32_t index = i * m_Channels;  // Offset for the color channels
            m_Buffer[index++] = r;
            m_Buffer[index++] = g;
            m_Buffer[index++] = b;
            if (m_Channels > 3) m_Buffer[index++] = a;
        }

        /**
         * Get the pixel 32-bit hex color using index location
         *
         * @return 32-bit hex color in RGB
         */
        inline uint32_t GetPixel(int const& i) const {
            if (i > -1 && i < m_Size - m_Channels) {
                u32 color = 0x000000;
                i32 index = i * m_Channels;  // Offset for the color channels
                color = (m_Buffer[index++] << 16);  // Red channel
                color += (m_Buffer[index++] << 8);  // Green channel
                color += (m_Buffer[index++] << 0);  // Blue channel
                return color;
            }

            return 0;
        }

        /***
         * Get the pixel alpha value
         *
         * @return Ranges between 0 to 255(100%), always return 255 if the image
         * is only 3 channels
         */
        inline uint8_t GetPixelAlpha(int const& i) {
            if (i > -1 && i < m_Size - m_Channels && m_Channels > 3)
                return m_Buffer[(i * m_Channels) +
                                3];  // Offset to the alpha channel

            return 255;
        }

        /**
         * Get the image data buffer
         *
         * @return Image data buffer pointer
         */
        inline uint8_t* GetBuffer() const { return m_Buffer; }

       private:
        i32 m_Width;      // Image width in pixels
        i32 m_Height;     // Image height in pixels
        i32 m_Channels;   // Image color channels
        i32 m_Size;       // Image size (width * height * channels)
        u8* m_Buffer;     // Image color data buffer
        bool m_IsFlip;    // Origin at top(false) left or bottom(true) left
        bool m_IsLoaded;  // Check to see if the image was loaded from stb
    };

}  // namespace EN
