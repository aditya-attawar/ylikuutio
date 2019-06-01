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

#ifndef __GLYPH_OBJECT_CREATION_HPP_INCLUDED
#define __GLYPH_OBJECT_CREATION_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Text3D;

        void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* const text3D);
    }
}

#endif
