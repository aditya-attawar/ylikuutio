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
#include "scene.hpp"
#include "font2D.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/file/file_writer.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#include "SDL.h"

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
#include <cstddef>       // std::size_t
#include <inttypes.h>    // PRId32, PRId64, PRIu32, PRIu64, PRIx32, PRIx64
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace ontology
    {
        class Species;

        void Universe::bind_world(yli::ontology::World* const world)
        {
            // get `childID` from `Universe` and set pointer to `world`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::World*>(
                    world,
                    this->world_pointer_vector,
                    this->free_worldID_queue,
                    this->number_of_worlds);
        }

        void Universe::bind_font2D(yli::ontology::Font2D* const font2D)
        {
            // get `childID` from `Universe` and set pointer to `font2D`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Font2D*>(
                    font2D,
                    this->font2D_pointer_vector,
                    this->free_font2D_ID_queue,
                    this->number_of_font2Ds);
        }

        Universe::~Universe()
        {
            // destructor.
            std::cout << "This universe will be destroyed.\n";

            // destroy all worlds of this universe.
            std::cout << "All worlds of this universe will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::World*>(this->world_pointer_vector, this->number_of_worlds);

            delete this->console_pointer;
            delete this->active_font2D;

            SDL_Quit();
        }

        void Universe::do_physics()
        {
            this->compute_and_update_matrices_from_inputs();
        }

        void Universe::render()
        {
            this->prerender();

            if (this->active_world != nullptr)
            {
                // render this `Universe` by calling `render()` function of the active `World`.
                this->active_world->render();
            }

            yli::opengl::disable_depth_test();

            // Render the `Console` (including current input).
            this->console_pointer->render();

            // render `Font2D`s of this `Universe` by calling `render()` function of each `Font2D`.
            yli::ontology::render_children<yli::ontology::Font2D*>(this->font2D_pointer_vector);

            yli::opengl::enable_depth_test();

            // Swap buffers.
            SDL_GL_SwapWindow(this->get_window());

            this->postrender();
        }

        void Universe::set_active_world(yli::ontology::World* const world)
        {
            this->active_world = world;

            if (this->active_world != nullptr && this->active_world->get_active_scene() != nullptr)
            {
                this->turbo_factor = this->active_world->get_active_scene()->get_turbo_factor();
                this->twin_turbo_factor = this->active_world->get_active_scene()->get_twin_turbo_factor();
                this->terrain_species = this->active_world->get_active_scene()->get_terrain_species();
            }
        }

        void Universe::set_active_scene(yli::ontology::Scene* const scene)
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
                this->terrain_species = this->active_world->get_active_scene()->get_terrain_species();
            }
        }

        std::size_t Universe::get_number_of_worlds() const
        {
            return this->number_of_worlds;
        }

        yli::ontology::World* Universe::get_active_world() const
        {
            return this->active_world;
        }

        yli::ontology::Entity* Universe::get_parent() const
        {
            // `Universe` has no parent.
            return nullptr;
        }

        std::size_t Universe::get_number_of_children() const
        {
            return this->number_of_worlds;
        }

        std::size_t Universe::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->world_pointer_vector);
        }

        void Universe::create_context()
        {
            this->context = std::make_shared<SDL_GLContext>(SDL_GL_CreateContext(this->window));
        }

        void Universe::make_context_current()
        {
            if (this->context != nullptr)
            {
                yli::opengl::make_context_current(this->window, *this->context);
            }
        }

        SDL_Window* Universe::get_window() const
        {
            return this->window;
        }

        std::size_t Universe::get_window_width() const
        {
            return this->window_width;
        }

        std::size_t Universe::get_window_height() const
        {
            return this->window_height;
        }

        std::size_t Universe::get_text_size() const
        {
            return this->text_size;
        }

        std::size_t Universe::get_font_size() const
        {
            return this->font_size;
        }

        float Universe::compute_delta_time()
        {
            // `std::numeric_limits<std::size_t>::max()` means that `last_time_before_reading_keyboard` is not defined.
            if (this->last_time_before_reading_keyboard == std::numeric_limits<uint32_t>::max())
            {
                // `glfwGetTime()` is called here only once, the first time this function is called.
                this->last_time_before_reading_keyboard = SDL_GetTicks();
            }

            this->current_time_before_reading_keyboard = SDL_GetTicks();

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

        std::size_t Universe::get_max_FPS() const
        {
            return this->max_FPS;
        }

        void Universe::set(std::string& setting_name, std::shared_ptr<yli::datatypes::AnyValue> setting_any_value)
        {
            this->setting_master->set(setting_name, setting_any_value);
        }

        yli::config::Setting* Universe::get(std::string key) const
        {
            return this->setting_master->get(key);
        }

        bool Universe::is_entity(const std::string& name) const
        {
            return this->entity_map.count(name) == 1;
        }

        yli::ontology::Entity* Universe::get_entity(const std::string& name) const
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

        void Universe::add_entity(const std::string& name, yli::ontology::Entity* const entity)
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
                if (this->entity_map[name]->get_can_be_erased())
                {
                    this->entity_map.erase(name);
                }
            }
        }

        yli::ontology::EntityFactory* Universe::get_entity_factory() const
        {
            if (this->entity_factory == nullptr)
            {
                return nullptr;
            }

            return this->entity_factory.get();
        }

        // Public callbacks.

        std::shared_ptr<yli::datatypes::AnyValue> Universe::activate(
                yli::console::Console* const console,
                yli::ontology::Entity* const universe_entity,
                const std::vector<std::string>& command_parameters)
        {
            // This function can be used to activate a `World` or a `Scene`.
            // A `World` can be activated always, assuming that the `universe_entity` is a `Universe`.
            // A `Scene` can be activated only if there is an active `Scene`.

            if (console == nullptr || universe_entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::config::SettingMaster* setting_master = universe->get_setting_master();

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

                yli::ontology::Entity* entity = universe->entity_map[name];
                yli::ontology::World* const world = dynamic_cast<yli::ontology::World*>(entity);
                yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(entity);

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
                    yli::ontology::World* const world_parent_of_scene = scene->get_world_parent();

                    if (world_parent_of_scene != nullptr)
                    {
                        universe->set_active_world(world_parent_of_scene);
                        universe->set_active_scene(scene);
                    }
                }
            }
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> Universe::delete_entity(
                yli::console::Console* const console,
                yli::ontology::Entity* const universe_entity,
                const std::vector<std::string>& command_parameters)
        {
            if (console == nullptr || universe_entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::config::SettingMaster* setting_master = universe->get_setting_master();

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

                yli::ontology::Entity* entity = universe->entity_map[name];

                if (entity == nullptr)
                {
                    universe->entity_map.erase(name);
                    return nullptr;
                }

                if (entity->get_can_be_erased())
                {
                    universe->entity_map.erase(name);
                    delete entity;
                }
            }
            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> Universe::info(
                yli::console::Console* const console,
                yli::ontology::Entity* const universe_entity,
                const std::vector<std::string>& command_parameters)
        {
            if (console == nullptr || universe_entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (command_parameters.size() == 0)
            {
                // No command parameters.
                // Print names of named entities.
                yli::map::print_keys_to_console(&universe->entity_map, console);
            }
            else if (command_parameters.size() == 1)
            {
                std::string name = command_parameters[0];

                if (universe->entity_map.count(name) != 1)
                {
                    return nullptr;
                }

                yli::ontology::Entity* entity = universe->entity_map[name];

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

                if (entity->get_parent() == nullptr)
                {
                    console->print_text("parent's address: nullptr");
                }
                else
                {
                    uint64_t parents_memory_address = reinterpret_cast<uint64_t>((void*) entity->get_parent());
                    char parents_memory_address_char_array[256];
                    snprintf(parents_memory_address_char_array, sizeof(parents_memory_address_char_array), "0x%" PRIx64, static_cast<uint64_t>(parents_memory_address));

                    std::string parent_info = "parent's address: ";
                    parent_info += std::string(parents_memory_address_char_array);
                    console->print_text(parent_info);
                }

                std::size_t number_of_children = entity->get_number_of_children();
                char number_of_children_char_array[256];
                snprintf(number_of_children_char_array, sizeof(number_of_children_char_array), "%lu", number_of_children);

                std::string children_info = "number of children: ";
                children_info += std::string(number_of_children_char_array);
                console->print_text(children_info);

                std::size_t number_of_descendants = entity->get_number_of_descendants();
                char number_of_descendants_char_array[256];
                snprintf(number_of_descendants_char_array, sizeof(number_of_descendants_char_array), "%lu", number_of_descendants);

                std::string descendants_info = "number of descendants: ";
                descendants_info += std::string(number_of_descendants_char_array);
                console->print_text(descendants_info);
            }

            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> Universe::bind(
                yli::console::Console* const console,
                yli::ontology::Entity* const universe_entity,
                const std::vector<std::string>& command_parameters)
        {
            if (console == nullptr || universe_entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (command_parameters.size() == 2)
            {
                std::string child_entity_name = command_parameters[0];

                if (universe->entity_map.count(child_entity_name) != 1)
                {
                    return nullptr;
                }

                yli::ontology::Entity* child_entity = universe->entity_map[child_entity_name];

                if (child_entity == nullptr)
                {
                    return nullptr;
                }

                std::string parent_entity_name = command_parameters[1];

                if (universe->entity_map.count(parent_entity_name) != 1)
                {
                    return nullptr;
                }

                yli::ontology::Entity* parent_entity = universe->entity_map[parent_entity_name];

                if (parent_entity == nullptr)
                {
                    return nullptr;
                }

                child_entity->bind_to_new_parent(parent_entity);
            }

            return nullptr;
        }

        std::shared_ptr<yli::datatypes::AnyValue> Universe::screenshot(
                yli::console::Console* const console,
                yli::ontology::Entity* const universe_entity,
                const std::vector<std::string>& command_parameters)
        {
            if (console == nullptr || universe_entity == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

            if (universe == nullptr)
            {
                return nullptr;
            }

            if (!yli::opengl::has_ext_framebuffer_object())
            {
                return nullptr;
            }

            if (command_parameters.size() == 1)
            {
                const std::string filename = command_parameters[0];

                // http://www.mathematik.uni-dortmund.de/~goeddeke/gpgpu/tutorial.html

                const std::size_t texture_width = universe->window_width;
                const std::size_t texture_height = universe->window_height;;

                // create FBO (off-screen framebuffer object):
                GLuint fb = 0;
                glGenFramebuffers(1, &fb);

                // bind offscreen buffer.
                glBindFramebuffer(GL_FRAMEBUFFER, fb);

                // create texture.
                GLuint tex;
                glGenTextures(1, &tex);
                glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex);

                // define texture.
                glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, texture_width, texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, 0);

                // poor filtering.
                glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_REPEAT);

                // attach texture.
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE_ARB, tex, 0);

                universe->render(); // render to framebuffer.

                // transfer data from GPU texture to CPU array.
                const std::size_t number_color_channels = 3;
                const std::size_t number_of_texels = texture_width * texture_height;
                const std::size_t number_of_elements = number_color_channels * number_of_texels;
                uint8_t* const result_array = new uint8_t[number_of_elements];

                glReadBuffer(GL_COLOR_ATTACHMENT0);
                glReadPixels(0, 0, texture_width, texture_height, GL_RGB, GL_UNSIGNED_BYTE, result_array);

                const std::vector<uint8_t> result_vector(result_array, result_array + number_of_elements);

                yli::file::binary_write(result_vector, filename);

                delete[] result_array;
                glDeleteFramebuffers(1, &fb);

                // bind onscreen buffer.
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

            }

            return nullptr;
        }

        // Public callbacks end here.

        yli::ontology::Font2D* Universe::get_active_font2D() const
        {
            return this->active_font2D;
        }

        void Universe::set_active_font2D(yli::ontology::Font2D* const font2D)
        {
            this->active_font2D = font2D;
        }

        yli::console::Console* Universe::get_console() const
        {
            return this->console_pointer;
        }

        void Universe::set_console(yli::console::Console* console)
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

        yli::ontology::Species* Universe::get_terrain_species() const
        {
            return this->terrain_species;
        }

        void Universe::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            this->terrain_species = terrain_species;
        }

        glm::mat4& Universe::get_projection_matrix()
        {
            return this->current_camera_projection_matrix;
        }

        void Universe::set_projection_matrix(glm::mat4& projection_matrix)
        {
            this->current_camera_projection_matrix = projection_matrix;
        }

        glm::mat4& Universe::get_view_matrix()
        {
            return this->current_camera_view_matrix;
        }

        void Universe::set_view_matrix(glm::mat4& view_matrix)
        {
            this->current_camera_view_matrix = view_matrix;
        }

        float Universe::get_aspect_ratio() const
        {
            return this->aspect_ratio;
        }

        GLfloat Universe::get_initialFoV() const
        {
            return this->initialFoV;
        }

        bool Universe::compute_and_update_matrices_from_inputs()
        {
            if (!this->is_flight_mode_in_use)
            {
                // accelerate and fall.

                this->fall_speed += this->gravity;
                this->current_camera_cartesian_coordinates.y -= this->fall_speed;

                // adjust position according to the ground.

                if (this->terrain_species != nullptr)
                {
                    float ground_y = yli::ontology::get_floor_level(
                            this->terrain_species,
                            this->current_camera_cartesian_coordinates);

                    if (!std::isnan(ground_y) && this->current_camera_cartesian_coordinates.y < ground_y)
                    {
                        this->current_camera_cartesian_coordinates.y = ground_y;
                        this->fall_speed = 0.0f;
                    }
                }
            }

            if (this->testing_spherical_terrain_in_use)
            {
                // compute spherical coordinates.
                this->current_camera_spherical_coordinates.rho = sqrt(
                        (this->current_camera_cartesian_coordinates.x * this->current_camera_cartesian_coordinates.x) +
                        (this->current_camera_cartesian_coordinates.y * this->current_camera_cartesian_coordinates.y) +
                        (this->current_camera_cartesian_coordinates.z * this->current_camera_cartesian_coordinates.z));
                this->current_camera_spherical_coordinates.theta = RADIANS_TO_DEGREES(atan2(sqrt(
                                (this->current_camera_cartesian_coordinates.x * this->current_camera_cartesian_coordinates.x) +
                                (this->current_camera_cartesian_coordinates.y * this->current_camera_cartesian_coordinates.y)),
                            this->current_camera_cartesian_coordinates.z));
                this->current_camera_spherical_coordinates.phi = RADIANS_TO_DEGREES(atan2(
                            this->current_camera_cartesian_coordinates.y,
                            this->current_camera_cartesian_coordinates.x));
            }

            glm::vec3 camera_cartesian_coordinates;
            camera_cartesian_coordinates.x = this->current_camera_cartesian_coordinates.x;
            camera_cartesian_coordinates.y = this->current_camera_cartesian_coordinates.y;
            camera_cartesian_coordinates.z = this->current_camera_cartesian_coordinates.z;
            camera_cartesian_coordinates.y += 2.0f;

            // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
            this->current_camera_projection_matrix = glm::perspective(
                    DEGREES_TO_RADIANS(this->initialFoV),
                    this->aspect_ratio,
                    this->znear,
                    this->zfar);

            // Camera matrix
            this->current_camera_view_matrix = glm::lookAt(
                    camera_cartesian_coordinates,                                  // Camera is here
                    camera_cartesian_coordinates + this->current_camera_direction, // and looks here : at the same position, plus "current_camera_direction"
                    this->current_camera_up                                        // Head is up (set to 0,-1,0 to look upside-down)
                    );

            return true;
        }
    }
}
