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
         * Create a texture
         *
         * @param[in] filename Image file filename
         */
        Texture(const char* filename);

        ~Texture();

        void Bind(const uint32_t& slot = 0) const;

        void Unbind() const;

       private:
        u32 m_BufferID;
        std::string m_Filename;
        i32 m_Width, m_Height, m_Channels;
        u8* m_LocalBuffer;
    };

}  // namespace EN
