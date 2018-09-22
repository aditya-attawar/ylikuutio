#ifndef __UNIVERSE_STRUCT_HPP_INCLUDED
#define __UNIVERSE_STRUCT_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

typedef struct UniverseStruct
{
    UniverseStruct()
        : window_title("Ylikuutio 0.0.1"),
        window_width(1600),
        window_height(900),
        text_size(40),
        font_size(16),
        max_FPS(50000),        // default value max 50000 frames per second.
        speed(5.0f),           // default value 5.0 units / second
        mouse_speed(0.005f),
        gravity(9.81f / 60.0f),
        znear(1.0f),
        zfar(5000.0f), // visibility: 5000 units.
        is_headless(false)
    {
        // constructor.
    }

    std::string window_title;
    int32_t window_width;
    int32_t window_height;
    int32_t text_size;
    int32_t font_size;
    uint32_t max_FPS;
    float speed;
    float mouse_speed;
    float gravity;
    float znear;
    float zfar;
    bool is_headless;
} UniverseStruct;

#endif
