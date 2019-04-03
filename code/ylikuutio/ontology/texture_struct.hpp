#ifndef __TEXTURE_STRUCT_HPP_INCLUDED
#define __TEXTURE_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t

typedef struct TextureStruct
{
    TextureStruct()
    {
        // constructor.
    }

    std::size_t texture_width;
    std::size_t texture_height;
} TextureStruct;

#endif
