#ifndef __TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED
#define __TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace geometry
    {
        typedef struct TriangulateQuadsStruct
        {
            TriangulateQuadsStruct()
                : image_width(-1), image_height(-1), should_ylikuutio_use_real_texture_coordinates(true), x_step(1), z_step(1), sphere_radius(NAN)
            {
                // constructor.
            }
            int32_t image_width;
            int32_t image_height;
            int32_t x_step;
            int32_t z_step;
            std::string triangulation_type;
            bool should_ylikuutio_use_real_texture_coordinates;
            double sphere_radius;
            yli::geometry::SphericalTerrainStruct spherical_terrain_struct;
        } TriangulateQuadsStruct;
    }
}

#endif
