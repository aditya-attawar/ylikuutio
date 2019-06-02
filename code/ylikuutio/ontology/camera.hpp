// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __CAMERA_HPP_INCLUDED
#define __CAMERA_HPP_INCLUDED

#include "movable.hpp"
#include "universe.hpp"
#include "camera_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Camera: public yli::ontology::Movable
        {
            public:
                Camera(yli::ontology::Universe* const universe, const CameraStruct& camera_struct)
                    : Movable(universe, camera_struct.cartesian_coordinates)
                {
                    // constructor.

                    this->horizontal_angle  = camera_struct.horizontal_angle;
                    this->vertical_angle    = camera_struct.vertical_angle;
                    this->is_static_view    = camera_struct.is_static_view;

                    // variables related to the projection.
                    this->projection_matrix = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->view_matrix       = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->parent            = camera_struct.parent;

                    // Get `childID` from the `Scene` and set pointer to this `Camera`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Camera*";
                }

                Camera(const Camera&) = delete;            // Delete copy constructor.
                Camera &operator=(const Camera&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Camera();

                yli::ontology::Entity* get_parent() const override;

                const glm::vec3& get_direction() const;
                const glm::vec3& get_up() const;
                const glm::vec3& get_right() const;
                void adjust_horizontal_angle(float adjustment);

                const glm::mat4& get_projection_matrix() const;
                const glm::mat4& get_view_matrix() const;
                float get_horizontal_angle() const;
                float get_vertical_angle() const;

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                friend class Universe;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                bool compute_and_update_matrices_from_inputs();

                // variables related to location and orientation.

                yli::ontology::Scene* parent;

                // variables related to the projection.
                glm::mat4 projection_matrix;
                glm::mat4 view_matrix;
                double horizontal_angle;
                double vertical_angle;

                bool is_static_view;
        };
    }
}

#endif
