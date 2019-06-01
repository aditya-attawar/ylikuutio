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

#ifndef __CAMERA_STRUCT_HPP_INCLUDED
#define __CAMERA_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

namespace yli
{
    namespace ontology
    {
        class Scene;
    }
}

typedef struct CameraStruct
{
    CameraStruct()
        : cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
        direction(glm::vec3(NAN, NAN, NAN)),
        parent(nullptr),
        horizontal_angle(NAN),
        vertical_angle(NAN)
    {
        // constructor.
    }

    // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
    glm::vec3 cartesian_coordinates; // coordinate vector.

    // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
    glm::vec3 direction;             // direction vector.

    yli::ontology::Scene* parent;    // pointer to the `Scene`.

    double horizontal_angle;         // horizontal angle in radians.
    double vertical_angle;           // vertical angle in radians.
} CameraStruct;

#endif
