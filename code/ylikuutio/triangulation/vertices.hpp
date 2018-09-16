#ifndef __VERTICES_HPP_INCLUDED
#define __VERTICES_HPP_INCLUDED

#include "triangulate_quads_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        void output_triangle_vertices(
                const std::vector<glm::vec3>& temp_vertices,
                const std::vector<glm::vec2>& temp_UVs,
                const std::vector<glm::vec3>& temp_normals,
                const GLuint vertex_index[3],
                const GLuint uv_index[3],
                const GLuint normal_index[3],
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals);

        bool define_vertices_UVs_and_normals(
                const yli::geometry::TriangulateQuadsStruct triangulate_quads_struct,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_UVs,
                std::vector<glm::vec3>& temp_normals,
                GLuint vertex_index[3],
                GLuint uv_index[3],
                GLuint normal_index[3],
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                const std::size_t actual_image_width,
                const std::size_t actual_image_height,
                const bool is_bilinear_interpolation_in_use,
                const bool is_southwest_northeast_edges_in_use,
                const bool is_southeast_northwest_edges_in_use);
    }
}

#endif
