#ifndef __FACE_NORMALS_HPP_INCLUDED
#define __FACE_NORMALS_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "triangulation_enums.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ylikuutio
{
    namespace geometry
    {
        bool compute_face_normals(
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec3>& face_normal_vector_vec3,
                const int32_t actual_image_width,
                const int32_t actual_image_height,
                const bool is_bilinear_interpolation_in_use,
                const bool is_southwest_northeast_edges_in_use,
                const bool is_southeast_northwest_edges_in_use);

        glm::vec3 get_face_normal(
                const std::vector<glm::vec3>& face_normal_data,
                const int32_t x,
                const int32_t z,
                const BilinearDirections compass_point_code,
                const int32_t actual_image_width);

        // for bilinear interpolation.
        // These functions exist to avoid need to remember
        // the array order when calling `ylikuutio::geometry::get_face_normal`.
        glm::vec3 s_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width);
        glm::vec3 w_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width);
        glm::vec3 n_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width);
        glm::vec3 e_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width);

        // for southeast-northwest edges.
        glm::vec3 get_face_normal_for_SE_NW(
                const std::vector<glm::vec3>& face_normal_data,
                const int32_t x,
                const int32_t z,
                const SoutheastNorthwestEdgesDirections compass_point_code,
                const int32_t image_width);

        // for southwest-northeast edges.
        glm::vec3 get_face_normal_for_SW_NE(
                const std::vector<glm::vec3>& face_normal_data,
                const int32_t x,
                const int32_t z,
                const SouthwestNortheastEdgesDirections compass_point_code,
                const int32_t image_width);
    }
}

#endif
