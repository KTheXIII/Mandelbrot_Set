#pragma once

#include "Core.hpp"
#include "Image.hpp"

namespace EN {
    constexpr i32 MAX_TEXTURE_SLOT = 16;

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

        ~Texture();

        /**
         * Bind the texture object
         *
         * @param[in] slot The slot be bind to
         */
        void Bind(uint32_t const& slot = 0) const;

        /**
         * Unbind the texture object
         */
        void Unbind() const;

        /**
         * Load in the image data onto the texture
         *
         * @param[in] image The reference to the image object
         */
        void Load(Image const& image);

       private:
        u32 m_BufferID;  // Texture Buffer Object IDs
    };

}  // namespace EN
