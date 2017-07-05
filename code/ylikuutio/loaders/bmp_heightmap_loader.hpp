#ifndef __BMP_HEIGHTMAP_LOADER_HPP_INCLUDED
#define __BMP_HEIGHTMAP_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    bool load_BMP_world(
            const std::string image_path,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            int32_t& image_width,
            int32_t& image_height,
            const std::string color_channel,
            const uint32_t x_step,
            const uint32_t z_step,
            const std::string triangulation_type);
}

#endif
