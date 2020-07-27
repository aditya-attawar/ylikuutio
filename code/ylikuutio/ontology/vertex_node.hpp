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

#ifndef __VERTEX_NODE_HPP_INCLUDED
#define __VERTEX_NODE_HPP_INCLUDED

#include "code/ylikuutio/graph/node.hpp"
#include "code/ylikuutio/graph/node_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::ontology
{
    class VertexNode: public yli::graph::Node
    {
        public:
            VertexNode(glm::vec3 coordinate_vector, const yli::graph::NodeStruct& node_struct)
                : yli::graph::Node(node_struct)
            {
                // constructor.
                this->coordinate_vector = coordinate_vector;
            }

            VertexNode(const VertexNode&) = delete;            // Delete copy constructor.
            VertexNode &operator=(const VertexNode&) = delete; // Delete copy assignment.

            // destructor.
            ~VertexNode();

        private:
            glm::vec3 coordinate_vector;
    };
}

#endif
