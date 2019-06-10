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

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace command_line
    {
        class CommandLineMaster
        {
            public:
                CommandLineMaster(const int argc, const char* const argv[]);
                bool is_key(const std::string& key) const;
                std::string get_value(const std::string& key) const;
                void print_keys() const;
                void print_keys_and_values() const;

            private:
                int argc;
                std::vector<std::string> arg_vector;
                std::unordered_map<std::string, std::string> arg_map;
        };
    }
}
