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

// How `yli::ontology::Camera` class works:
//
// By default no `Camera` is activated.
// `Universe` knows the coordinates and the angles.
// TODO: in the future, each `Scene` knows the coordinates and the angles.
//
// When the description below does not specifically say otherwise:
// * "active `Scene`" refers to the active `Scene` of the active `World`.
// * "active `Camera`" refers to the active `Camera` of the active `Scene`.
//
// When a `Camera` is activated:
// 1. If there is an active `Camera` in that `Scene` and the `Camera`
//    is not static view `Camera`, then the coordinates and angles are
//    copied from the `Universe` to the `Camera`.
// 2. The newly activated `Camera` is marked as the active `Camera` of
//    its parent `Scene`.
// 3. If parent `Scene` of the activated `Camera` is the active `Scene`,
//    then the coordinates and the angles of the `Camera` are copied
//    to the coordinates and angles of the `Universe`.
//
// When a `Scene` is activated:
// 1. If there is an active `Camera` in the current `Scene` and the `Camera`
//    is not static view `Camera`, then the coordinates and angles are
//    copied from the `Universe` to the `Camera`.
// 2. The `Scene` is marked as the active `Scene` of its parent `World`.
// 3. The parent `World` is marked as the active `World` of the `Universe`.
// 4. If the newly activated `Scene` has an activated `Camera`, then
//    the coordinates and angles of that `Camera` are copied to the `Universe`.
//
// When a `Camera` is deleted:
// 1. If the `Camera` is the active `Camera` in its parent `Scene`, then
//    the active `Camera` of that `Scene` is set to `nullptr`.
//
// When a `Scene` is deleted:
// 1. Every child of `Scene` gets deleted as usual, including the `Camera`s.

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Camera: public yli::ontology::Movable
        {
            public:
                Camera(yli::ontology::Universe* const universe, const yli::ontology::CameraStruct& camera_struct)
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

                void adjust_horizontal_angle(float adjustment);

                const glm::mat4& get_projection_matrix() const;
                const glm::mat4& get_view_matrix() const;
                bool get_is_static_view() const;

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

                bool is_static_view;
        };
    }
}

#endif
