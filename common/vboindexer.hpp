#ifndef VBOINDEXER_HPP
#define VBOINDEXER_HPP

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h>
#endif

namespace model
{
    void indexVBO(
            std::vector<glm::vec3> &in_vertices,
            std::vector<glm::vec2> &in_uvs,
            std::vector<glm::vec3> &in_normals,

            std::vector<GLuint> &out_indices,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_uvs,
            std::vector<glm::vec3> &out_normals
            );

    void indexVBO_TBN(
            std::vector<glm::vec3> &in_vertices,
            std::vector<glm::vec2> &in_uvs,
            std::vector<glm::vec3> &in_normals,
            std::vector<glm::vec3> &in_tangents,
            std::vector<glm::vec3> &in_bitangents,

            std::vector<GLuint> &out_indices,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_uvs,
            std::vector<glm::vec3> &out_normals,
            std::vector<glm::vec3> &out_tangents,
            std::vector<glm::vec3> &out_bitangents
            );
}

#endif
