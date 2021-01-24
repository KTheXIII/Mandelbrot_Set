#pragma once

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "stb/stb_image.h"

namespace EN {

    // TODO: Texture filter, have the ability to select different filter.

    /**
     * Texture
     *
     * Create texture from image file
     */
    class Texture {
       public:
        /**
         * Creates empty Texture Buffer Object with no data
         */
        Texture();

        /**
         * Create a texture
         *
         * @param[in] filename Image file filename
         */
        Texture(const char* filename);

        ~Texture();

        void Bind(const uint32_t& slot = 0) const;

        void Unbind() const;

        void LoadTexture(const char* filename);

       private:
        u32 m_BufferID;
        std::string m_Filename;
        i32 m_Width, m_Height, m_Channels;
        u8* m_LocalBuffer;

        void Load();
    };

}  // namespace EN
