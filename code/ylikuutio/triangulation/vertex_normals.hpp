#ifndef __VERTEX_NORMALS_HPP_INCLUDED
#define __VERTEX_NORMALS_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    void compute_vertex_normals(
            std::vector<glm::vec3>& temp_normals,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            int32_t actual_image_width,
            int32_t actual_image_height,
            bool is_bilinear_interpolation_in_use,
            bool is_southwest_northeast_edges_in_use,
            bool is_southeast_northwest_edges_in_use);
}

#endif
