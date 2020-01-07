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

#ifndef __SCENE_STRUCT_HPP_INCLUDED
#define __SCENE_STRUCT_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class World;

        struct SceneStruct
        {
            SceneStruct()
                : world(nullptr),
                gravity(9.81f / 60.0f),  // default Earth gravity (9.81 m/s^2).
                water_level(0.0f),       // default water level: 0.0 meters.
                is_flight_mode_in_use(true)
            {
                // constructor.
            }

            yli::ontology::World* world; // pointer to `World` object.
            float gravity;               // In Bullet, gravity is a feature of `btDiscreteDynamicsWorld` & `
                                         // `btSoftRigidDynamicsWorld` (`btSoftRigidDynamicsWorld` inherits `btDiscreteDynamicsWorld`).
            float water_level;
            bool is_flight_mode_in_use;
        };
    }
}

#endif