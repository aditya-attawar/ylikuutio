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

#include "any_value_entity.hpp"
#include "universe.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void AnyValueEntity::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `AnyValueEntity::bind_to_parent`: `universe` is `nullptr`!\n";
                return;
            }

            // Get `childID` from the `Universe` and set pointer to this `AnyValueEntity`.
            universe->bind_any_value_entity(this);
        }

        AnyValueEntity::~AnyValueEntity()
        {
            // destructor.
            std::cout << "This `AnyValueEntity` will be destroyed.\n";

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `AnyValueEntity::~AnyValueEntity`: `universe` is `nullptr`!\n";
                return;
            }

            // set pointer to this `AnyValueEntity` to `nullptr`.
            universe->unbind_any_value_entity(this->childID);
        }

        yli::ontology::Entity* AnyValueEntity::get_parent() const
        {
            // Every `AnyValueEntity` is a child of the `Universe`.
            // The base class needs to be specified due to ambiguity caused by diamond inheritance.
            return this->yli::ontology::Entity::universe;
        }

        std::size_t AnyValueEntity::get_number_of_children() const
        {
            return 0; // `AnyValueEntity` has no children.
        }

        std::size_t AnyValueEntity::get_number_of_descendants() const
        {
            return 0; // `AnyValueEntity` has no children.
        }
    }
}