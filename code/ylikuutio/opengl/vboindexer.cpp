#include "vboindexer.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <map>      // std::map
#include <vector>   // std::vector

// Returns true iif v1 can be considered equal to v2
bool is_near(float v1, float v2)
{
    return (fabs(v1 - v2) < 0.01f);
}

// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool getSimilarVertexIndex(
        const glm::vec3& in_vertex,
        const glm::vec2& in_uv,
        const glm::vec3& in_normal,
        std::vector<glm::vec3>& out_vertices,
        std::vector<glm::vec2>& out_UVs,
        std::vector<glm::vec3>& out_normals,
        GLuint &result)
{
    // Lame linear search
    for (std::size_t i = 0; i < out_vertices.size(); i++)
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

namespace yli
{
    namespace opengl
    {
        struct PackedVertex
        {
            glm::vec3 position;
            glm::vec2 uv;
            glm::vec3 normal;
            bool operator < (const PackedVertex that) const
            {
                return (std::memcmp((void*) this, (void*) &that, sizeof(PackedVertex)) > 0);
            };
        };

        bool getSimilarVertexIndex_fast(
                const PackedVertex& packed,
                const std::map<PackedVertex, GLuint>& VertexToOutIndex,
                GLuint& result)
        {
            const std::map<PackedVertex, GLuint>::const_iterator it = VertexToOutIndex.find(packed);
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
                const std::vector<glm::vec3>& in_vertices,
                const std::vector<glm::vec2>& in_UVs,
                const std::vector<glm::vec3>& in_normals,
                std::vector<GLuint>& out_indices,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals)
        {
            std::map<PackedVertex, GLuint> VertexToOutIndex;

            // For each input vertex
            for (std::size_t i = 0; i < in_vertices.size() && i < in_UVs.size() && i < in_normals.size(); i++)
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
                    VertexToOutIndex[packed] = newindex;
                }
            }
        }
    }
}