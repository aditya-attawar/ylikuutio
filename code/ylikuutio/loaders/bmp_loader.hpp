#ifndef __BMP_LOADER_HPP_INCLUDED
#define __BMP_LOADER_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace loaders
{
    uint8_t* load_BMP_file(
            const std::string image_path,
            int32_t& image_width,
            int32_t& image_height,
            int32_t& image_size);
}

#endif
