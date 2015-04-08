#include <string.h> // for memcmp
#include <stdint.h> // uint32_t etc.
#include <vector>
#include <map>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h>
#endif

#include "vboindexer.hpp"

// Returns true iif v1 can be considered equal to v2
bool is_near(float v1, float v2)
{
    return (fabs(v1 - v2) < 0.01f);
}

// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool getSimilarVertexIndex(
        glm::vec3 &in_vertex,
        glm::vec2 &in_uv,
        glm::vec3 &in_normal,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_UVs,
        std::vector<glm::vec3> &out_normals,
        GLuint &result)
{
    // Lame linear search
    for (uint32_t i = 0; i < out_vertices.size(); i++)
    {
        if (is_near(in_vertex.x, out_vertices[i].x) &&
                is_near(in_vertex.y, out_vertices[i].y) &&
                is_near(in_vertex.z, out_vertices[i].z) &&
                is_near(in_uv.x, out_UVs[i].x) &&
                is_near(in_uv.y, out_UVs[i].y) &&
                is_near(in_normal.x, out_normals [i].x) &&
                is_near(in_normal.y, out_normals [i].y) &&
                is_near(in_normal.z, out_normals [i].z))
        {
            result = i;
            return true;
        }
    }
    // No other vertex could be used instead.
    // Looks like we'll have to add it to the VBO.
    return false;
}

namespace model
{
    void indexVBO_slow(
            std::vector<glm::vec3> &in_vertices,
            std::vector<glm::vec2> &in_UVs,
            std::vector<glm::vec3> &in_normals,

            std::vector<GLuint> &out_indices,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals)
    {
        // For each input vertex
        for (unsigned int i = 0; i < in_vertices.size(); i++)
        {
            // Try to find a similar vertex in out_XXXX
            GLuint index;
            bool found = getSimilarVertexIndex(in_vertices[i], in_UVs[i], in_normals[i], out_vertices, out_UVs, out_normals, index);

            if (found)
            {
                // A similar vertex is already in the VBO, use it instead !
                out_indices.push_back(index);
            }
            else
            {
                // If not, it needs to be added in the output data.
                out_vertices.push_back(in_vertices[i]);
                out_UVs.push_back(in_UVs[i]);
                out_normals.push_back(in_normals[i]);
                out_indices.push_back((GLuint) out_vertices.size() - 1);
            }
        }
    }

    struct PackedVertex
    {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        bool operator < (const PackedVertex that) const
        {
            return (memcmp((void*) this, (void*) &that, sizeof(PackedVertex)) > 0);
        };
    };

    bool getSimilarVertexIndex_fast(
            PackedVertex &packed,
            std::map<PackedVertex, GLuint> &VertexToOutIndex,
            GLuint &result)
    {
        std::map<PackedVertex, GLuint>::iterator it = VertexToOutIndex.find(packed);
        if (it == VertexToOutIndex.end())
        {
            return false;
        }
        else
        {
            result = it->second;
            return true;
        }
    }

    void indexVBO(
            std::vector<glm::vec3> &in_vertices,
            std::vector<glm::vec2> &in_UVs,
            std::vector<glm::vec3> &in_normals,

            std::vector<GLuint> &out_indices,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals)
    {
        std::map<PackedVertex, GLuint> VertexToOutIndex;

        // For each input vertex
        for (uint32_t i = 0; i < in_vertices.size(); i++)
        {
            PackedVertex packed = { in_vertices[i], in_UVs[i], in_normals[i] };

            // Try to find a similar vertex in out_XXXX
            GLuint index;
            bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

            if (found)
            {
                // A similar vertex is already in the VBO, use it instead !
                out_indices.push_back(index);
            }
            else
            {
                // If not, it needs to be added in the output data.
                out_vertices.push_back(in_vertices[i]);
                out_UVs.push_back(in_UVs[i]);
                out_normals.push_back(in_normals[i]);
                GLuint newindex = (GLuint) out_vertices.size() - 1;
                out_indices.push_back(newindex);
                VertexToOutIndex[ packed ] = newindex;
            }
        }
    }

    void indexVBO_TBN(
            std::vector<glm::vec3> &in_vertices,
            std::vector<glm::vec2> &in_UVs,
            std::vector<glm::vec3> &in_normals,
            std::vector<glm::vec3> &in_tangents,
            std::vector<glm::vec3> &in_bitangents,
            std::vector<GLuint> &out_indices,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            std::vector<glm::vec3> &out_tangents,
            std::vector<glm::vec3> &out_bitangents)
    {
        // For each input vertex
        for (unsigned int i = 0; i < in_vertices.size(); i++)
        {
            // Try to find a similar vertex in out_XXXX
            GLuint index;
            bool found = getSimilarVertexIndex(in_vertices[i], in_UVs[i], in_normals[i], out_vertices, out_UVs, out_normals, index);

            if (found)
            {
                // A similar vertex is already in the VBO, use it instead !
                out_indices.push_back(index);

                // Average the tangents and the bitangents
                out_tangents[index] += in_tangents[i];
                out_bitangents[index] += in_bitangents[i];
            }
            else
            {
                // If not, it needs to be added in the output data.
                out_vertices.push_back(in_vertices[i]);
                out_UVs.push_back(in_UVs[i]);
                out_normals.push_back(in_normals[i]);
                out_tangents.push_back(in_tangents[i]);
                out_bitangents.push_back(in_bitangents[i]);
                out_indices.push_back((GLuint) out_vertices.size() - 1);
            }
        }
    }
}
