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

#ifndef __SHADER_STRUCT_HPP_INCLUDED
#define __SHADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Scene;

        typedef struct ShaderStruct
        {
            ShaderStruct()
                : parent(nullptr),
                is_gpgpu_shader(false)
            {
                // constructor.
            }

            std::string vertex_shader;    // filename of vertex shader.
            std::string fragment_shader;  // filename of fragment shader.
            yli::ontology::Scene* parent; // pointer to the `Scene`.
            bool is_gpgpu_shader;         // TODO: GPGPU `Shader`s are not rendered on screen but their result textures can be used by `Material`s.
        } ShaderStruct;
    }
}

#endif
