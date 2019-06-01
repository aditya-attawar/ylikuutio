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

#include "ajokki_console_callbacks.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace console
    {
        class Console;
    }

    namespace ontology
    {
        class Entity;
    }
}

namespace ajokki
{
    std::shared_ptr<yli::datatypes::AnyValue> version(
            yli::console::Console* const console,
            yli::ontology::Entity* const,
            const std::vector<std::string>& command_parameters)
    {
        console->print_text("Ajokki 0.0.3 / Ylikuutio 0.0.3");
        return nullptr;
    }

    std::shared_ptr<yli::datatypes::AnyValue> quit(
            yli::console::Console* const,
            yli::ontology::Entity* const,
            const std::vector<std::string>& command_parameters)
    {
        uint32_t exit_program_magic_number = EXIT_PROGRAM_MAGIC_NUMBER;
        return std::make_shared<yli::datatypes::AnyValue>(exit_program_magic_number);
    }

    std::shared_ptr<yli::datatypes::AnyValue> help(
            yli::console::Console* const console,
            yli::ontology::Entity* const,
            const std::vector<std::string>& command_parameters)
    {
        console->print_help();
        return nullptr;
    }
}
