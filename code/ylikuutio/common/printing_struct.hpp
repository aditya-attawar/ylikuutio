#ifndef __PRINTING_STRUCT_HPP_INCLUDED
#define __PRINTING_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

typedef struct PrintingStruct
{
    PrintingStruct()
        : screen_width(0),
        screen_height(0),
        x(0),
        y(0),
        text_size(0),
        font_size(0)
    {
        // constructor.
    }
    std::size_t screen_width;
    std::size_t screen_height;
    std::size_t x;
    std::size_t y;
    std::size_t text_size;
    std::size_t font_size;
    std::string text;
    std::string font_texture_file_format;
    std::string horizontal_alignment;
    std::string vertical_alignment;
} PrintingStruct;

#endif
