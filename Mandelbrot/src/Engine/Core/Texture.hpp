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
         *
         * @param[in] size The amount of texture slots to be created
         */
        Texture(int32_t const& size = 1);

        ~Texture();

        /**
         * Recreate the texture with new max slot value
         *
         * @param[in] size The amount of texture slot to be created
         */
        void Rereate(int32_t const& size = 1);

        /**
         * Bind the texture object
         *
         * @param[in] slot The slot be bind to
         * @param[in] index The texture buffer object index
         */
        void Bind(uint32_t const& slot = 0, uint32_t const& index = 0) const;

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
        u32* m_BufferIDs;  // Texture Buffer Object IDs
        i32 m_MaxSlot;     // Texture buffer max slots
    };

}  // namespace EN
