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

#ifndef __TEXT3D_HPP_INCLUDED
#define __TEXT3D_HPP_INCLUDED

#include "movable.hpp"
#include "glyph_object_creation.hpp"
#include "vector_font.hpp"
#include "text3D_struct.hpp"
#include "object_struct.hpp"
#include "movable_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Universe;
        class Object;

        class Text3D: public yli::ontology::Movable
        {
            public:
                void bind_Object(yli::ontology::Object* const object);
                void unbind_Object(const std::size_t childID);

                // this method deletes all glyph Objects of this `Text3D`,
                // sets pointer to this `Text3D` to `nullptr`,
                // sets `parent` according to the input (the new `VectorFont`),
                // requests a new `childID` from the new `VectorFont`,
                // and creates all glyph Objects of this `Text3D` with the font data.
                // Note: different fonts may provide glyphs for different Unicodes!
                void bind_to_new_parent(yli::ontology::VectorFont* const new_vector_font_pointer);

                // constructor.
                // TODO: `Text3D` constructor also creates each `Object`,
                // and binds each to its corresponding `Glyph` for rendering hierarchy,
                // and also binds each to this `Text3D` for ontological hierarchy.
                Text3D(yli::ontology::Universe* const universe, const yli::ontology::Text3DStruct& text3D_struct)
                    : Movable(universe, yli::ontology::MovableStruct(
                                text3D_struct.brain,
                                text3D_struct.cartesian_coordinates,
                                text3D_struct.spherical_coordinates,
                                text3D_struct.horizontal_angle,
                                text3D_struct.vertical_angle))
                {
                    // constructor.
                    this->rotate_angle = NAN;
                    this->text_string  = text3D_struct.text_string;
                    this->parent       = text3D_struct.parent;

                    this->number_of_objects = 0;

                    // get childID from `VectorFont` and set pointer to this `Text3D`.
                    this->bind_to_parent();

                    std::cout << "Creating the glyph Objects for the string \"" << this->text_string << "\"\n";

                    // Let's create each glyph `Object` in a loop.

                    yli::ontology::create_glyph_objects(this->text_string, this);

                    // `yli::ontology::Entity` member variables begin here.
                    this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
                    this->type_string = "yli::ontology::Text3D*";
                    this->can_be_erased = true;
                }

                Text3D(const Text3D&) = delete;            // Delete copy constructor.
                Text3D &operator=(const Text3D&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Text3D();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                friend class Object;
                friend void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* text3D);
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                std::string text_string;

                yli::ontology::VectorFont* parent; // pointer to the `VectorFont`.

                glm::vec3 original_scale_vector;   // original scale vector.
                float rotate_angle;                // rotate angle.
                glm::vec3 rotate_vector;           // rotate vector.
                glm::vec3 translate_vector;        // translate vector.

                std::vector<yli::ontology::Object*> object_pointer_vector;
                std::queue<std::size_t> free_objectID_queue;
                std::size_t number_of_objects;
        };
    }
}

#endif
