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

#include "movable.hpp"
#include "brain.hpp"
#include "movable_variable_activation.hpp"
#include "movable_variable_read.hpp"
#include "variable_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
// `Movable` is a mixin class, not intended to be instantiated.

#include <cmath>    // NAN, std::isnan, std::pow

namespace yli::ontology
{
    void Movable::bind_to_brain()
    {
        // requirements:
        // `this->brain` must not be `nullptr`.
        yli::ontology::Brain* const brain = this->brain;

        if (brain == nullptr)
        {
            std::cerr << "ERROR: `Movable::bind_to_brain`: `brain` is `nullptr`!\n";
            return;
        }

        // get `apprenticeID` from `Brain` and set pointer to this `Movable`.
        this->brain->master_of_movables.bind_apprentice(this);
    }

    void Movable::unbind_from_brain()
    {
        if (this->brain != nullptr)
        {
            this->brain->master_of_movables.unbind_apprentice(this->apprenticeID);
        }
    }

    void Movable::bind_to_new_brain(yli::ontology::Brain* const new_brain)
    {
        // This method sets pointer to this `Movable` to `nullptr`, sets `brain` according to the input,
        // and requests a new `apprenticeID` from the new `Brain`.

        this->unbind_from_brain(); // unbind from the current `Brain` if there is such.

        this->brain = new_brain;
        this->bind_to_brain();
    }

    Movable::~Movable()
    {
        // destructor.

        this->unbind_from_brain();
    }

    yli::ontology::Entity* Movable::get_parent() const
    {
        return this->child.get_parent();
    }

    const glm::vec3& Movable::get_cartesian_coordinates() const
    {
        return this->cartesian_coordinates;
    }

    void Movable::set_cartesian_coordinates(const glm::vec3& cartesian_coordinates)
    {
        this->cartesian_coordinates = cartesian_coordinates;
    }

    float Movable::get_yaw() const
    {
        return this->yaw;
    }

    void Movable::set_yaw(const float yaw)
    {
        this->yaw = yaw;
    }

    float Movable::get_pitch() const
    {
        return this->pitch;
    }

    void Movable::set_pitch(const float pitch)
    {
        this->pitch = pitch;
    }

    // Public callbacks (to be called from AI scripts written in YliLisp).

    void Movable::set_dest(yli::ontology::Movable* const movable, const float x, const float y, const float z)
    {
        // Set target towards which to move.
        movable->cartesian_coordinates = glm::vec3(x, y, z);
    }

    float Movable::get_x(const yli::ontology::Movable* const movable)
    {
        // Get x coordinate of `movable`.
        return movable->cartesian_coordinates.x;
    }

    float Movable::get_y(const yli::ontology::Movable* const movable)
    {
        // Get y coordinate of `movable`.
        return movable->cartesian_coordinates.y;
    }

    float Movable::get_z(const yli::ontology::Movable* const movable)
    {
        // Get z coordinate of `movable`.
        return movable->cartesian_coordinates.z;
    }

    float Movable::get_dest_x(const yli::ontology::Movable* const movable)
    {
        // Get x destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates.x;
    }

    float Movable::get_dest_y(const yli::ontology::Movable* const movable)
    {
        // Get y destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates.y;
    }

    float Movable::get_dest_z(const yli::ontology::Movable* const movable)
    {
        // Get z destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates.z;
    }

    // Public callbacks end here.

    void Movable::create_coordinate_and_angle_variables()
    {
        float float_x = this->cartesian_coordinates.x;
        float float_y = this->cartesian_coordinates.y;
        float float_z = this->cartesian_coordinates.z;

        yli::ontology::VariableStruct cartesian_coordinates_variable_struct(std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(float_x, float_y, float_z)));
        cartesian_coordinates_variable_struct.local_name = "cartesian_coordinates";
        cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
        cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
        cartesian_coordinates_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(cartesian_coordinates_variable_struct);` ...\n";
        this->create_variable(cartesian_coordinates_variable_struct);

        yli::ontology::VariableStruct x_variable_struct(std::make_shared<yli::data::AnyValue>(float_x));
        x_variable_struct.local_name = "x";
        x_variable_struct.activate_callback = &yli::ontology::activate_x;
        x_variable_struct.read_callback = &yli::ontology::read_x;
        x_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(x_variable_struct);` ...\n";
        this->create_variable(x_variable_struct);

        yli::ontology::VariableStruct y_variable_struct(std::make_shared<yli::data::AnyValue>(float_y));
        y_variable_struct.local_name = "y";
        y_variable_struct.activate_callback = &yli::ontology::activate_y;
        y_variable_struct.read_callback = &yli::ontology::read_y;
        y_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(y_variable_struct);` ...\n";
        this->create_variable(y_variable_struct);

        yli::ontology::VariableStruct z_variable_struct(std::make_shared<yli::data::AnyValue>(float_z));
        z_variable_struct.local_name = "z";
        z_variable_struct.activate_callback = &yli::ontology::activate_z;
        z_variable_struct.read_callback = &yli::ontology::read_z;
        z_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(z_variable_struct);` ...\n";
        this->create_variable(z_variable_struct);

        yli::ontology::VariableStruct yaw_variable_struct(std::make_shared<yli::data::AnyValue>(this->yaw));
        yaw_variable_struct.local_name = "yaw";
        yaw_variable_struct.activate_callback = &yli::ontology::activate_yaw;
        yaw_variable_struct.read_callback = &yli::ontology::read_yaw;
        yaw_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(yaw_variable_struct);` ...\n";
        this->create_variable(yaw_variable_struct);

        yli::ontology::VariableStruct pitch_variable_struct(std::make_shared<yli::data::AnyValue>(this->pitch));
        pitch_variable_struct.local_name = "pitch";
        pitch_variable_struct.activate_callback = &yli::ontology::activate_pitch;
        pitch_variable_struct.read_callback = &yli::ontology::read_pitch;
        pitch_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(pitch_variable_struct);` ...\n";
        this->create_variable(pitch_variable_struct);
    }
}
