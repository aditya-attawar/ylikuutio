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

#include "generic_console_command.hpp"

namespace yli::ontology
{
    GenericConsoleCommand::~GenericConsoleCommand()
    {
        // destructor.
    }

    yli::ontology::Entity* GenericConsoleCommand::get_parent() const
    {
        return this->child_of_console.get_parent();
    }

    std::size_t GenericConsoleCommand::get_number_of_children() const
    {
        return 0; // `GenericConsoleCommand` has no children.
    }

    std::size_t GenericConsoleCommand::get_number_of_descendants() const
    {
        return 0; // `GenericConsoleCommand` has no children.
    }
}