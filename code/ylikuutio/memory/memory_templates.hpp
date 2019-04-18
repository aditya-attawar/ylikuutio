#ifndef __MEMORY_TEMPLATES_HPP_INCLUDED
#define __MEMORY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace memory
    {
        template<class T1, class T2>
            T2 read_nonaligned_32_bit(T1* src_data, std::size_t offset)
            {
                uint8_t* src_data_uint8_t = (uint8_t*) src_data;
                T2 value_32_bit = static_cast<T2>(src_data_uint8_t[offset + 3]);
                value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset + 2]);
                value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset + 1]);
                value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset]);
                return value_32_bit;
            }

        template<class T1>
            void flip_vertically(T1* src_data, std::size_t image_width, std::size_t image_height)
            {
                for (std::size_t y = 0; y < image_height / 2; y++)
                {
                    for (std::size_t x = 0; x < image_width; x++)
                    {
                        std::size_t upper_index = image_width * y + x;
                        std::size_t lower_index = image_width * (image_height - y - 1) + x;
                        T1 temp = src_data[upper_index];
                        src_data[upper_index] = src_data[lower_index];
                        src_data[lower_index] = temp;
                    }
                }
            }
    }
}

#endif
