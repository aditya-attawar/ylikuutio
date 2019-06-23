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

#ifndef __ANY_VALUE_ENTITY_HPP_INCLUDED
#define __ANY_VALUE_ENTITY_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <vector>  // std::vector

// `AnyValueEntity` is a child of the `Universe`.

namespace yli
{
    namespace ontology
    {
        class Universe;

        class AnyValueEntity: public yli::datatypes::AnyValue, public yli::ontology::Entity
        {
            public:
                // constructor.
                // use the default copy constructor of `yli::datatypes::AnyValue`.
                AnyValueEntity(yli::ontology::Universe* const universe, const std::shared_ptr<yli::datatypes::AnyValue> any_value_shared_ptr)
                    : yli::datatypes::AnyValue(*any_value_shared_ptr), yli::ontology::Entity(universe)
                {
                    this->parent = universe;

                    // Get `childID` from `Universe` and set pointer to this `AnyValueEntity`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::AnyValueEntity*";
                    this->can_be_erased = true;
                }

                // constructor.
                // use the default copy constructor of `yli::datatypes::AnyValue`.
                AnyValueEntity(yli::ontology::Universe* const universe, const yli::datatypes::AnyValue& any_value)
                    : yli::datatypes::AnyValue(any_value), yli::ontology::Entity(universe)
                {
                    this->parent = universe;

                    // Get `childID` from `Universe` and set pointer to this `AnyValueEntity`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::AnyValueEntity*";
                    this->can_be_erased = true;
                }

                AnyValueEntity(const AnyValueEntity&) = delete;            // Delete copy constructor.
                AnyValueEntity &operator=(const AnyValueEntity&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~AnyValueEntity()
                {
                    // destructor.
                }

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Universe* parent; // pointer to the `Universe`.
        };
    }
}

#endif
