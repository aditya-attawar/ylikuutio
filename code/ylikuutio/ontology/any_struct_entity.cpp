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

#include "any_struct_entity.hpp"
#include "universe.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    AnyStructEntity::~AnyStructEntity()
    {
        // destructor.
        std::cout << "This `AnyStructEntity` will be destroyed.\n";
    }

    yli::ontology::Entity* AnyStructEntity::get_parent() const
    {
        return this->child_of_entity.get_parent();
    }

    std::size_t AnyStructEntity::get_number_of_children() const
    {
        return 0; // `AnyStructEntity` has no children.
    }

    std::size_t AnyStructEntity::get_number_of_descendants() const
    {
        return 0; // `AnyStructEntity` has no children.
    }
}
