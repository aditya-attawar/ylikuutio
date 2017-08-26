#ifndef __ASCII_GRID_LOADER_HPP_INCLUDED
#define __ASCII_GRID_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector


namespace loaders
{
    bool load_ASCII_grid(
            const std::string ASCII_grid_file_name,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            const int32_t x_step,
            const int32_t z_step,
            const std::string triangulation_type);
}

#endif