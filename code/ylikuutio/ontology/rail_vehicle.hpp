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

#ifndef __RAIL_VEHICLE_HPP_INCLUDED
#define __RAIL_VEHICLE_HPP_INCLUDED

#include "vehicle.hpp"
#include "object_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli
{
    namespace ontology
    {
        class Universe;

        class RailVehicle: public yli::ontology::Vehicle
        {
            public:
                // constructor.
                RailVehicle(yli::ontology::Universe* const universe, const yli::ontology::ObjectStruct& object_struct)
                    : Vehicle(universe, object_struct)
                {
                    // constructor.

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::RailVehicle*";
                    this->can_be_erased = true;
                }

                RailVehicle(const RailVehicle&) = delete;            // Delete copy constructor.
                RailVehicle &operator=(const RailVehicle&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~RailVehicle();
        };
    }
}

#endif
