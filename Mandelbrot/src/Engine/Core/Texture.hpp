#pragma once

#include "Core.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "stb/stb_image.h"

namespace EN {

    // TODO: Texture filter

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
         * @param[in] path Image file path
         */
        Texture(const char* path);

        ~Texture();

        void Bind(const uint32_t& slot = 0) const;

        void Unbind() const;

       private:
        u32 m_BufferID;
        std::string m_FilePath;
        i32 m_Width, m_Height, m_Channels;
        u8* m_LocalBuffer;
    };

}  // namespace EN
