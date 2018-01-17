#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "universe.hpp"
#include "entity.hpp"
#include "world.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <inttypes.h>    // PRId32, PRId64, PRIu32, PRIu64, PRIx32, PRIx64
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace ontology
{
    Universe::~Universe()
    {
        // destructor.
        std::cout << "This universe will be destroyed.\n";

        // destroy all worlds of this universe.
        std::cout << "All worlds of this universe will be destroyed.\n";
        hierarchy::delete_children<ontology::World*>(this->world_pointer_vector, &this->number_of_worlds);

        std::cout << "The setting master of this universe will be destroyed.\n";
        delete this->setting_master;

        std::cout << "The entity factory of this universe will be destroyed.\n";
        delete this->entity_factory;

        glfwTerminate();
    }

    void Universe::bind(ontology::World* world)
    {
        // get `childID` from `Universe` and set pointer to `world`.
        hierarchy::bind_child_to_parent<ontology::World*>(
                world,
                this->world_pointer_vector,
                this->free_worldID_queue,
                &this->number_of_worlds);
    }

    void Universe::render()
    {
        if (this->active_world != nullptr)
        {
            this->prerender();

            if (this->compute_matrices_from_inputs())
            {
                // render this `Universe` by calling `render()` function of the active `World`.
                this->active_world->render();
            }

            this->postrender();
        }
    }

    void Universe::set_active_world(ontology::World* world)
    {
        this->active_world = world;

        if (this->active_world != nullptr && this->active_world->get_active_scene() != nullptr)
        {
            this->turbo_factor = this->active_world->get_active_scene()->get_turbo_factor();
            this->twin_turbo_factor = this->active_world->get_active_scene()->get_twin_turbo_factor();
        }
    }

    void Universe::set_active_scene(ontology::Scene* scene)
    {
        if (this->active_world == nullptr)
        {
            // No active `World`.
            return;
        }

        this->active_world->set_active_scene(scene);

        if (this->active_world->get_active_scene() != nullptr)
        {
            this->turbo_factor = this->active_world->get_active_scene()->get_turbo_factor();
            this->twin_turbo_factor = this->active_world->get_active_scene()->get_twin_turbo_factor();
        }
    }

    int32_t Universe::get_number_of_worlds() const
    {
        return this->number_of_worlds;
    }

    ontology::World* Universe::get_active_world() const
    {
        return this->active_world;
    }

    ontology::Entity* Universe::get_parent() const
    {
        // `Universe` has no parent.
        return nullptr;
    }

    int32_t Universe::get_number_of_children() const
    {
        return this->number_of_worlds;
    }

    int32_t Universe::get_number_of_descendants() const
    {
        return -1;
    }

    void Universe::set_window(GLFWwindow* window)
    {
        this->window = window;
        glfwSetWindowUserPointer(this->window, this);
    }

    GLFWwindow* Universe::get_window() const
    {
        return this->window;
    }

    int32_t Universe::get_window_width() const
    {
        return this->window_width;
    }

    int32_t Universe::get_window_height() const
    {
        return this->window_height;
    }

    int32_t Universe::get_text_size() const
    {
        return this->text_size;
    }

    int32_t Universe::get_font_size() const
    {
        return this->font_size;
    }

    float Universe::compute_delta_time()
    {
        if (std::isnan(this->last_time_before_reading_keyboard))
        {
            // `glfwGetTime()` is called here only once, the first time this function is called.
            this->last_time_before_reading_keyboard = glfwGetTime();
        }

        this->current_time_before_reading_keyboard = glfwGetTime();

        this->delta_time = static_cast<float>(current_time_before_reading_keyboard - last_time_before_reading_keyboard);
        return this->delta_time;
    }

    float Universe::get_delta_time() const
    {
        return this->delta_time;
    }

    void Universe::finalize_delta_time_loop()
    {
        this->last_time_before_reading_keyboard = this->current_time_before_reading_keyboard;
    }

    uint32_t Universe::get_max_FPS() const
    {
        return this->max_FPS;
    }

    void Universe::set(std::string& setting_name, std::shared_ptr<datatypes::AnyValue> setting_any_value)
    {
        this->setting_master->set(setting_name, setting_any_value);
    }

    config::Setting* Universe::get(std::string key) const
    {
        return this->setting_master->get(key);
    }

    bool Universe::is_entity(const std::string& name) const
    {
        return this->entity_map.count(name) == 1;
    }

    ontology::Entity* Universe::get_entity(const std::string& name) const
    {
        if (this->entity_map.count(name) != 1)
        {
            return nullptr;
        }
        return this->entity_map.at(name);
    }

    std::string Universe::get_entity_names() const
    {
        std::string entity_names = "";

        std::vector<std::string> keys;
        keys.reserve(this->entity_map.size());

        for (auto it : this->entity_map)
        {
            if (!entity_names.empty())
            {
                entity_names += " ";
            }
            std::string key = static_cast<std::string>(it.first);
            entity_names += key;
        }

        return entity_names;
    }

    void Universe::add_entity(const std::string& name, ontology::Entity* const entity)
    {
        if (this->entity_map.count(name) == 0)
        {
            this->entity_map[name] = entity;
        }
    }

    void Universe::erase_entity(const std::string& name)
    {
        if (this->entity_map.count(name) == 1)
        {
            this->entity_map.erase(name);
        }
    }

    ontology::EntityFactory* Universe::get_entity_factory() const
    {
        return this->entity_factory;
    }

    // Public callbacks.

    std::shared_ptr<datatypes::AnyValue> Universe::delete_entity(
            console::Console* const console,
            ontology::Entity* const entity,
            std::vector<std::string>& command_parameters)
    {
        if (console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        config::SettingMaster* setting_master = universe->setting_master;

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string name = command_parameters[0];

            if (universe->entity_map.count(name) == 0)
            {
                return nullptr;
            }

            ontology::Entity* entity = universe->entity_map[name];
            universe->entity_map.erase(name);

            if (entity == nullptr)
            {
                return nullptr;
            }

            delete entity;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Universe::activate(
            console::Console* const console,
            ontology::Entity* const universe_entity,
            std::vector<std::string>& command_parameters)
    {
        // This function can be used to activate a `World` or a `Scene`.
        // A `World` can be activated always, assuming that the `entity` is a `Universe`.
        // A `Scene` can be activated only if there is an active `Scene`.

        if (console == nullptr || universe_entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(universe_entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        config::SettingMaster* setting_master = universe->setting_master;

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string name = command_parameters[0];

            if (universe->entity_map.count(name) == 0)
            {
                return nullptr;
            }

            ontology::Entity* entity = universe->entity_map[name];
            ontology::World* world = dynamic_cast<ontology::World*>(entity);
            ontology::Scene* scene = dynamic_cast<ontology::Scene*>(entity);

            if (world == nullptr && scene == nullptr)
            {
                // The named `Entity` is neither a `World` nor a `Scene`.
                return nullptr;
            }

            if (world != nullptr && scene == nullptr)
            {
                // The named `Entity` is a `World`.
                universe->set_active_world(world);
            }
            else if (scene != nullptr && world == nullptr)
            {
                // The named `Entity` is a `Scene`.
                universe->set_active_scene(scene);
            }
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Universe::info(
            console::Console* const console,
            ontology::Entity* const entity,
            std::vector<std::string>& command_parameters)
    {
        if (console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        ontology::Universe* universe = dynamic_cast<ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print names of named entities.
            map::print_keys_to_console(&universe->entity_map, console);
        }
        else if (command_parameters.size() == 1)
        {
            std::string name = command_parameters[0];

            if (universe->entity_map.count(name) != 1)
            {
                return nullptr;
            }

            ontology::Entity* entity = universe->entity_map[name];

            if (entity == nullptr)
            {
                return nullptr;
            }

            // OK, let's find out information about the entity.

            console->print_text(entity->get_type());

            uint64_t memory_address = reinterpret_cast<uint64_t>((void*) entity);
            char memory_address_char_array[256];
            snprintf(memory_address_char_array, sizeof(memory_address_char_array), "0x%" PRIx64, static_cast<uint64_t>(memory_address));

            std::string entity_info = "memory address: ";
            entity_info += std::string(memory_address_char_array);
            console->print_text(entity_info);

            uint64_t parents_memory_address = reinterpret_cast<uint64_t>((void*) entity->get_parent());
            char parents_memory_address_char_array[256];
            snprintf(parents_memory_address_char_array, sizeof(parents_memory_address_char_array), "0x%" PRIx64, static_cast<uint64_t>(parents_memory_address));

            std::string parent_info = "parent's address: ";
            parent_info += std::string(parents_memory_address_char_array);
            console->print_text(parent_info);

            int32_t number_of_children = entity->get_number_of_children();
            char number_of_children_char_array[256];
            snprintf(number_of_children_char_array, sizeof(number_of_children_char_array), "%d", number_of_children);

            std::string children_info = "number of children: ";
            children_info += std::string(number_of_children_char_array);
            console->print_text(children_info);
        }
        return nullptr;
    }

    // Public callbacks end here.

    config::SettingMaster* Universe::get_setting_master() const
    {
        return this->setting_master;
    }

    console::Console* Universe::get_console() const
    {
        return this->console_pointer;
    }

    void Universe::set_console(console::Console* console)
    {
        this->console_pointer = console;
    }

    float Universe::get_planet_radius() const
    {
        return this->planet_radius;
    }

    void Universe::set_planet_radius(float planet_radius)
    {
        this->planet_radius = planet_radius;
    }

    void Universe::set_world_pointer(int32_t childID, ontology::World* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->world_pointer_vector, this->free_worldID_queue, &this->number_of_worlds);
    }

    void Universe::set_terrain_species(ontology::Species* terrain_species)
    {
        this->terrain_species = terrain_species;
    }

    glm::mat4& Universe::get_projection_matrix()
    {
        return this->ProjectionMatrix;
    }

    glm::mat4& Universe::get_view_matrix()
    {
        return this->ViewMatrix;
    }

    bool Universe::compute_matrices_from_inputs()
    {
        if (this->cartesian_coordinates == nullptr)
        {
            return false;
        }

        if (!this->is_flight_mode_in_use)
        {
            this->fall_speed += this->gravity;
            this->cartesian_coordinates->y -= this->fall_speed;
        }

        GLfloat FoV = this->initialFoV;

        // adjust position according to the ground.
        if (!this->is_flight_mode_in_use)
        {
            if (this->terrain_species != nullptr)
            {
                GLfloat ground_y = ontology::get_floor_level(static_cast<ontology::Species*>(this->terrain_species), this->cartesian_coordinates);

                if (!std::isnan(ground_y) && this->cartesian_coordinates->y < ground_y)
                {
                    this->cartesian_coordinates->y = ground_y;
                    this->fall_speed = 0.0f;
                }
            }
        }

        if (this->testing_spherical_terrain_in_use)
        {
            if (this->spherical_coordinates == nullptr)
            {
                return false;
            }

            // compute spherical coordinates.
            this->spherical_coordinates->rho = sqrt((this->cartesian_coordinates->x * this->cartesian_coordinates->x) + (this->cartesian_coordinates->y * this->cartesian_coordinates->y) + (this->cartesian_coordinates->z * this->cartesian_coordinates->z));
            this->spherical_coordinates->theta = RADIANS_TO_DEGREES(atan2(sqrt((this->cartesian_coordinates->x * this->cartesian_coordinates->x) + (this->cartesian_coordinates->y * this->cartesian_coordinates->y)), this->cartesian_coordinates->z));
            this->spherical_coordinates->phi = RADIANS_TO_DEGREES(atan2(this->cartesian_coordinates->y, this->cartesian_coordinates->x));
        }

        glm::vec3 camera_cartesian_coordinates;
        camera_cartesian_coordinates.x = this->cartesian_coordinates->x;
        camera_cartesian_coordinates.y = this->cartesian_coordinates->y;
        camera_cartesian_coordinates.z = this->cartesian_coordinates->z;
        camera_cartesian_coordinates.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        this->ProjectionMatrix = glm::perspective(DEGREES_TO_RADIANS(FoV), aspect_ratio, 0.001f, 5000.0f + 2.0f * static_cast<GLfloat>(this->planet_radius));
        // Camera matrix
        this->ViewMatrix = glm::lookAt(
                camera_cartesian_coordinates,                   // Camera is here
                camera_cartesian_coordinates + this->direction, // and looks here : at the same position, plus "direction"
                this->up                                        // Head is up (set to 0,-1,0 to look upside-down)
                );

        return true;
    }
}
