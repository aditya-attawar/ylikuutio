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

#include "holobiont.hpp"
#include "entity.hpp"
#include "symbiosis.hpp"
#include "biont.hpp"
#include "holobiont_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli::ontology
{
    Holobiont::~Holobiont()
    {
        // destructor.
        std::cout << "`Holobiont` with childID " << std::dec << this->childID << " will be destroyed.\n";
    }

    void Holobiont::render()
    {
        // render this `Holobiont`.

        if (this->should_be_rendered)
        {
            this->prerender();

            // render this `Holobiont` by calling `render()` function of each `Biont`.
            yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_bionts.child_pointer_vector);

            this->postrender();
        }
    }

    void Holobiont::create_bionts()
    {
        // requirements:
        // `this->symbiosis_parent` must not be `nullptr`.

        yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(this->child.get_parent());

        if (symbiosis == nullptr)
        {
            std::cerr << "ERROR: `Holobiont::create_bionts`: `symbiosis` is `nullptr`!\n";
            return;
        }

        std::cout << "Creating bionts for Holobiont located at 0x" << std::hex << (uint64_t) this << std::dec << " ...\n";

        // Create `Biont` entities so that they bind to this `Holobiont`.
        const std::size_t correct_number_of_bionts = symbiosis->get_number_of_ofbx_meshes();
        std::cout << "Number of bionts to be created: " << correct_number_of_bionts << "\n";

        for (std::size_t biontID = 0; biontID < correct_number_of_bionts; biontID++)
        {
            if (!symbiosis->has_texture(biontID))
            {
                std::cerr << "ERROR: `Holobiont::create_bionts`: There is no texture for biont with biontID " << biontID << "\n";
                continue;
            }

            yli::ontology::BiontStruct biont_struct;
            biont_struct.biontID               = biontID;
            biont_struct.holobiont_parent      = this;
            biont_struct.symbiont_species      = symbiosis->get_symbiont_species(biontID);
            biont_struct.initial_rotate_vectors = this->initial_rotate_vectors;
            biont_struct.initial_rotate_angles  = this->initial_rotate_angles;
            biont_struct.original_scale_vector = this->original_scale_vector;
            biont_struct.cartesian_coordinates = this->cartesian_coordinates;

            std::cout << "Creating biont with biontID " << biontID << " ...\n";

            new yli::ontology::Biont(this->universe, biont_struct, &this->parent_of_bionts);
        }
    }

    void Holobiont::update_x(float x)
    {
        this->cartesian_coordinates.x = x;
        this->model_matrix[3][0] = x;

        for (yli::ontology::Entity* biont_entity : this->parent_of_bionts.child_pointer_vector)
        {
            yli::ontology::Biont* biont = static_cast<yli::ontology::Biont*>(biont_entity);

            if (biont != nullptr)
            {
                biont->cartesian_coordinates.x = x;
                biont->model_matrix[3][0] = x;
            }
        }
    }

    void Holobiont::update_y(float y)
    {
        this->cartesian_coordinates.y = y;
        this->model_matrix[3][1] = y;

        for (yli::ontology::Entity* biont_entity : this->parent_of_bionts.child_pointer_vector)
        {
            yli::ontology::Biont* biont = static_cast<yli::ontology::Biont*>(biont_entity);

            if (biont != nullptr)
            {
                biont->cartesian_coordinates.y = y;
                biont->model_matrix[3][1] = y;
            }
        }
    }

    void Holobiont::update_z(float z)
    {
        this->cartesian_coordinates.z = z;
        this->model_matrix[3][2] = z;

        for (yli::ontology::Entity* biont_entity : this->parent_of_bionts.child_pointer_vector)
        {
            yli::ontology::Biont* biont = static_cast<yli::ontology::Biont*>(biont_entity);

            if (biont != nullptr)
            {
                biont->cartesian_coordinates.z = z;
                biont->model_matrix[3][2] = z;
            }
        }
    }

    std::size_t Holobiont::get_number_of_children() const
    {
        return this->parent_of_bionts.get_number_of_children();
    }

    std::size_t Holobiont::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_bionts.child_pointer_vector);
    }

    // Public callbacks.

    std::shared_ptr<yli::data::AnyValue> Holobiont::create_holobiont_with_parent_name_x_y_z(
            yli::ontology::Symbiosis* const parent,
            std::shared_ptr<std::string> holobiont_name,
            std::shared_ptr<std::string> x,
            std::shared_ptr<std::string> y,
            std::shared_ptr<std::string> z)
    {
        if (parent == nullptr || holobiont_name == nullptr || x == nullptr || y == nullptr || z == nullptr)
        {
            return nullptr;
        }

        yli::ontology::EntityFactory* const entity_factory = parent->get_entity_factory();

        if (entity_factory == nullptr)
        {
            return nullptr;
        }

        yli::data::AnyValue x_any_value("float", *x);
        yli::data::AnyValue y_any_value("float", *y);
        yli::data::AnyValue z_any_value("float", *z);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z`: invalid value for `x`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z`: invalid value for `y`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z`: invalid value for `z`!\n";
            return nullptr;
        }

        float float_x = std::get<float>(x_any_value.data);
        float float_y = std::get<float>(y_any_value.data);
        float float_z = std::get<float>(z_any_value.data);

        yli::ontology::HolobiontStruct holobiont_struct;
        holobiont_struct.cartesian_coordinates = glm::vec3(float_x, float_y, float_z);
        holobiont_struct.symbiosis_parent = parent;
        holobiont_struct.local_name = *holobiont_name;
        entity_factory->create_holobiont(holobiont_struct);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch(
            yli::ontology::Symbiosis* const parent,
            std::shared_ptr<std::string> holobiont_name,
            std::shared_ptr<std::string> x,
            std::shared_ptr<std::string> y,
            std::shared_ptr<std::string> z,
            std::shared_ptr<std::string> yaw,
            std::shared_ptr<std::string> pitch)
    {
        if (parent == nullptr || holobiont_name == nullptr || x == nullptr || y == nullptr || z == nullptr || yaw == nullptr || pitch == nullptr)
        {
            return nullptr;
        }

        yli::ontology::EntityFactory* const entity_factory = parent->get_entity_factory();

        if (entity_factory == nullptr)
        {
            return nullptr;
        }

        yli::data::AnyValue x_any_value("float", *x);
        yli::data::AnyValue y_any_value("float", *y);
        yli::data::AnyValue z_any_value("float", *z);
        yli::data::AnyValue yaw_any_value("float", *yaw);
        yli::data::AnyValue pitch_any_value("float", *pitch);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `x`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `y`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `z`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(yaw_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `yaw`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(pitch_any_value.data))
        {
            std::cerr << "ERROR: `Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch`: invalid value for `pitch`!\n";
            return nullptr;
        }

        float float_x = std::get<float>(x_any_value.data);
        float float_y = std::get<float>(y_any_value.data);
        float float_z = std::get<float>(z_any_value.data);
        float float_yaw = std::get<float>(yaw_any_value.data);
        float float_pitch = std::get<float>(pitch_any_value.data);

        yli::ontology::HolobiontStruct holobiont_struct;
        holobiont_struct.cartesian_coordinates = glm::vec3(float_x, float_y, float_z);
        holobiont_struct.yaw = float_yaw;
        holobiont_struct.pitch = float_pitch;
        holobiont_struct.symbiosis_parent = parent;
        holobiont_struct.local_name = *holobiont_name;
        entity_factory->create_holobiont(holobiont_struct);
        return nullptr;
    }

    // Public callbacks end here.
}
