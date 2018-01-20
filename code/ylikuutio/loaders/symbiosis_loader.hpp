#ifndef __SYMBIOSIS_LOADER_HPP_INCLUDED
#define __SYMBIOSIS_LOADER_HPP_INCLUDED

#include "symbiosis_loader_struct.hpp"

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
#include <vector>   // std::vector

namespace loaders
{
    bool load_symbiosis(
            SymbiosisLoaderStruct& symbiosis_loader_struct,
            std::vector<std::vector<glm::vec3>>& out_vertices,
            std::vector<std::vector<glm::vec2>>& out_UVs,
            std::vector<std::vector<glm::vec3>>& out_normals,
            std::vector<std::vector<GLuint>>& indices,
            std::vector<std::vector<glm::vec3>>& indexed_vertices,
            std::vector<std::vector<glm::vec2>>& indexed_UVs,
            std::vector<std::vector<glm::vec3>>& indexed_normals);
}

#endif
