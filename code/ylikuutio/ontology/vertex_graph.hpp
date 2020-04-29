// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __VERTEX_GRAPH_HPP_INCLUDED
#define __VERTEX_GRAPH_HPP_INCLUDED

#include "code/ylikuutio/graph/graph.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class VertexGraph: public yli::graph::Graph
    {
        public:
            // This constructor creates a graph from vertex data produced eg. by `bool triangulate_quads`.
            VertexGraph(std::vector<glm::vec3>& in_vertices, uint32_t image_width, uint32_t image_height, std::string triangulation_type)
                : yli::graph::Graph()
            {
                // constructor.
            }

            VertexGraph(const VertexGraph&) = delete;            // Delete copy constructor.
            VertexGraph &operator=(const VertexGraph&) = delete; // Delete copy assignment.

            // destructor.
            ~VertexGraph();
    };
}

#endif
