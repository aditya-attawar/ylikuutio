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

#include "entity.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "brain.hpp"
#include "console.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string, std::getline
#include <utility>  // std::pair
#include <vector>   // std::vector

namespace yli::ontology
{
    // Public callbacks.

    // Public `Entity` bind callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::bind(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const child_or_apprentice_entity,
            yli::ontology::Entity* const parent_or_master_entity)
    {
        if (universe == nullptr || child_or_apprentice_entity == nullptr || parent_or_master_entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const child_or_apprentice_movable = dynamic_cast<yli::ontology::Movable*>(child_or_apprentice_entity);
        yli::ontology::Brain* const parent_or_master_brain = dynamic_cast<yli::ontology::Brain*>(parent_or_master_entity);

        if (child_or_apprentice_movable != nullptr && parent_or_master_brain != nullptr)
        {
            child_or_apprentice_movable->bind_to_new_brain(parent_or_master_brain);
        }
        else
        {
            child_or_apprentice_entity->bind_to_new_parent(parent_or_master_entity);
        }

        return nullptr;
    }

    // Public `Entity` create callbacks.

    // Public `Entity` delete callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::delete_entity(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        if (entity->get_can_be_erased())
        {
            yli::ontology::Entity* const parent = entity->get_parent();

            if (parent != nullptr)
            {
                // Erase the local name.
                parent->entity_map.erase(entity->get_local_name());
            }

            // Erase the global name.
            universe->entity_map.erase(entity->get_global_name());
            delete entity;
        }

        return nullptr;
    }

    // Public `Entity` naming callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::set_global_name_for_entity(
            yli::ontology::Entity* const entity,
            std::shared_ptr<std::string> global_name)
    {
        if (entity == nullptr || global_name == nullptr)
        {
            return nullptr;
        }

        entity->set_global_name(*global_name);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::set_local_name_for_entity(
            yli::ontology::Entity* const entity,
            std::shared_ptr<std::string> local_name)
    {
        if (entity == nullptr || local_name == nullptr)
        {
            return nullptr;
        }

        entity->set_local_name(*local_name);

        return nullptr;
    }

    // Public `Entity` activate callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::activate_entity(yli::ontology::Entity* const entity)
    {
        if (entity != nullptr)
        {
            entity->activate();
        }

        return nullptr;
    }

    // Public YliLisp-related callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::eval(
            yli::ontology::Console* const console,
            yli::ontology::Entity* const universe_entity,
            const std::vector<std::string>& command_parameters)
    {
        if (universe_entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        // Command parameters must form a valid AngelScript expression.

        std::string expression;

        for (std::vector<std::string>::const_iterator it = command_parameters.begin(); it != command_parameters.end(); )
        {
            expression += *it;

            if (++it != command_parameters.end())
            {
                expression += " ";
            }
        }

        const std::string result = universe->eval_string(expression);

        if (console != nullptr)
        {
            console->print_text(result);
        }

        return nullptr;
    }

    // Public data printing callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::info0(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (console == nullptr || universe == nullptr)
        {
            return nullptr;
        }

        // Print names of named entities.
        yli::map::print_keys_to_console(universe->entity_map, console);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::info1(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (console == nullptr || universe == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // OK, let's find out information about this `Entity`.

        console->print_text(entity->get_type());

        std::size_t memory_address = reinterpret_cast<std::size_t>((void*) entity);
        std::stringstream memory_address_stringstream;
        memory_address_stringstream << "0x" << std::hex << memory_address;

        std::string entity_info = "memory address:   ";
        entity_info += memory_address_stringstream.str();
        console->print_text(entity_info);

        if (entity->get_parent() == nullptr)
        {
            console->print_text("parent's address: nullptr");
        }
        else
        {
            std::size_t parents_memory_address = reinterpret_cast<std::size_t>((void*) entity->get_parent());
            std::stringstream parents_memory_address_stringstream;
            parents_memory_address_stringstream << "0x" << std::hex << parents_memory_address;

            std::string parent_info = "parent's address: ";
            parent_info += parents_memory_address_stringstream.str();
            console->print_text(parent_info);
        }

        std::size_t number_of_children = entity->get_number_of_all_children();
        std::stringstream number_of_children_stringstream;
        number_of_children_stringstream << number_of_children;

        std::string children_info = "number of children: ";
        children_info += number_of_children_stringstream.str();
        console->print_text(children_info);

        std::size_t number_of_descendants = entity->get_number_of_all_descendants();
        std::stringstream number_of_descendants_stringstream;
        number_of_descendants_stringstream << number_of_descendants;

        std::string descendants_info = "number of descendants: ";
        descendants_info += number_of_descendants_stringstream.str();
        console->print_text(descendants_info);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::print_entities(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (universe == nullptr || console == nullptr)
        {
            return nullptr;
        }

        std::vector<std::pair<std::string, yli::ontology::Entity*>> key_and_value_vector = yli::map::get_keys_and_values(universe->entity_map);

        for (auto& [key, value] : key_and_value_vector)
        {
            std::size_t memory_address = reinterpret_cast<std::size_t>((void*) value);
            std::stringstream memory_address_stringstream;
            memory_address_stringstream << " 0x" << std::hex << memory_address;

            std::string entity_info = key;
            entity_info += memory_address_stringstream.str();
            console->print_text(entity_info);
        }

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::print_parent(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // OK, let's find out the parent of this `Entity`.

        if (entity->get_parent() == nullptr)
        {
            console->print_text("parent's address: nullptr");
        }
        else
        {
            std::size_t parents_memory_address = reinterpret_cast<std::size_t>((void*) entity->get_parent());
            std::stringstream parents_memory_address_stringstream;
            parents_memory_address_stringstream << "0x" << std::hex << parents_memory_address;

            std::string parent_info = "parent's address: ";
            parent_info += parents_memory_address_stringstream.str();
            console->print_text(parent_info);
        }

        return nullptr;
    }

    // Other public callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::screenshot(
            yli::ontology::Universe* const universe,
            std::shared_ptr<std::string> filename)
    {
        if (universe == nullptr || filename == nullptr)
        {
            return nullptr;
        }

        // https://learnopengl.com/Advanced-OpenGL/Framebuffers

        const std::size_t texture_width = universe->framebuffer_width;
        const std::size_t texture_height = universe->framebuffer_height;

        if (!universe->is_framebuffer_initialized)
        {
            // Create an FBO (off-screen framebuffer object).
            glGenFramebuffers(1, &universe->framebuffer);
        }

        // Bind the offscreen buffer.
        glBindFramebuffer(GL_FRAMEBUFFER, universe->framebuffer);

        if (!universe->is_framebuffer_initialized)
        {
            // Create a texture.
            glGenTextures(1, &universe->texture);
            glBindTexture(GL_TEXTURE_2D, universe->texture);

            // Define the texture.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

            yli::opengl::set_filtering_parameters();

            // Attach the texture.
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, universe->texture, 0);

            // Create and bind a render buffer with depth and stencil attachments.
            glGenRenderbuffers(1, &universe->renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, universe->renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, texture_width, texture_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, universe->renderbuffer);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                std::cerr << "ERROR: `Universe::screenshot`: framebuffer is not complete!\n";
            }

            // Set background color for the framebuffer.
            universe->set_opengl_background_color();

            universe->is_framebuffer_initialized = true;
        }

        // Clear the framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Adjust viewport for the framebuffer.
        glViewport(0, 0, texture_width, texture_height);
        universe->render_without_changing_depth_test(); // Render to framebuffer.

        // Transfer data from the GPU texture to a CPU array and save into a file.
        const bool should_ylikuutio_flip_texture = true;
        yli::opengl::save_data_from_gpu_texture_into_file(
                GL_RGB, GL_UNSIGNED_BYTE, texture_width, texture_height, *filename, should_ylikuutio_flip_texture);

        universe->restore_onscreen_rendering();

        return nullptr;
    }

    // Public callbacks end here.
}
