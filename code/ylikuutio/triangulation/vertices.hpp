#ifndef __VERTICES_HPP_INCLUDED
#define __VERTICES_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

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
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    void output_triangle_vertices(
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs,
            std::vector<glm::vec3>& temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals);

    void define_vertices_UVs_and_normals(
            TriangulateQuadsStruct triangulate_quads_struct,
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs,
            std::vector<glm::vec3>& temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            uint32_t actual_image_width,
            uint32_t actual_image_height,
            bool is_bilinear_interpolation_in_use,
            bool is_southwest_northeast_edges_in_use,
            bool is_southeast_northwest_edges_in_use);
}

#endif
