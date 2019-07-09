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

#ifndef __ENTITY_HPP_INCLUDED
#define __ENTITY_HPP_INCLUDED

#include "pre_render_callback.hpp"
#include "post_render_callback.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }

    namespace ontology
    {
        class Universe;

        class Entity
        {
            public:
                virtual void bind_to_new_parent(yli::ontology::Entity* const new_entity_parent);

                // constructor.
                Entity(yli::ontology::Universe* const universe);

                Entity(const Entity&) = delete;            // Delete copy constructor.
                Entity &operator=(const Entity&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Entity();

                std::size_t get_childID() const;
                std::string get_type() const;

                bool get_can_be_erased() const;

                yli::ontology::Universe* get_universe() const;
                yli::config::SettingMaster* get_setting_master() const;
                void set_setting_master(yli::config::SettingMaster* const setting_master);

                virtual yli::ontology::Entity* get_parent() const = 0;
                virtual std::size_t get_number_of_children() const = 0;
                virtual std::size_t get_number_of_descendants() const = 0;

                void set_name(const std::string& name);

                bool should_be_rendered;

                friend yli::ontology::Universe;

            protected:
                void prerender() const;
                void postrender() const;

                yli::ontology::Universe* universe;                          // pointer to the `Universe`.
                std::shared_ptr<yli::config::SettingMaster> setting_master; // pointer to the `SettingMaster`.
                std::vector<void*> child_vector_pointers_vector;
                std::size_t entityID;
                std::size_t childID; // TODO: add checks for `std::numeric_limits<std::size_t>::max();` (invalid value).

                std::string type_string;

                std::string name;    // name of this `Entity`.

                bool can_be_erased;

                PreRenderCallback prerender_callback;
                PostRenderCallback postrender_callback;

            private:
                void bind_to_universe();
        };
    }
}
#endif
