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

#ifndef __IMAGE_FILE_LOADER_HPP_INCLUDED
#define __IMAGE_FILE_LOADER_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        std::shared_ptr<std::vector<uint8_t>> load_image_file(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size);
    }
}

#endif