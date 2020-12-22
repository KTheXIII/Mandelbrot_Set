#pragma once

#include "Core.hpp"

#include "Glad/glad.h"
#include "GLFW/glfw3.h"

#include "stb/stb_image.h"

namespace EN {

    /**
     * Texture
     *
     * Create texture from image file
     */
    class Texture {
       public:
        Texture(const char* path);

        ~Texture();

        void Bind(const u32& slot = 0) const;

        void Unbind() const;

       private:
        u32 m_BufferID;
        std::string m_FilePath;
        i32 m_Width, m_Height, m_Channels;
        u8* m_LocalBuffer;
    };

}  // namespace EN