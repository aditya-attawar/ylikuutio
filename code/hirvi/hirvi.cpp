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

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "hirvi_console_callbacks.hpp"
#include "code/ajokki/ajokki_helsinki_east_downtown_scene.hpp"
#include "code/ajokki/ajokki_joensuu_center_west_scene.hpp"
#include "code/app/app_background_colors.hpp"
#include "code/app/app_keyboard_callbacks.hpp"
#include "code/app/app_debug.hpp"
#include "code/app/app_console.hpp"
#include "code/app/app_movement.hpp"
#include "code/app/app_location_and_orientation.hpp"
#include "code/app/app_wireframe.hpp"
#include "code/app/app_console_callbacks.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/console/console_command_callback.hpp"
#include "code/ylikuutio/console/console_callback_object.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/text2D.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/time/time.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#define SDL_main main

#include "SDL.h"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // abs, cos, NAN, remainder, sin, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <iomanip>       // std::setfill, std::setprecision, std::setw
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector

int main(const int argc, const char* const argv[])
{
    yli::command_line::CommandLineMaster command_line_master(argc, argv);

    if (command_line_master.is_key("version"))
    {
        std::cout << "Hirvi " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version << "\n";
        return 0;
    }

    command_line_master.print_keys_and_values();

    if (!command_line_master.get_are_arguments_valid())
    {
        // Some of the arguments do not comply with the Ylikuutio argument syntax.
        std::cerr << "ERROR: Invalid syntax used in command line parameters.\n";
        return 1;
    }

    const std::vector<std::string> valid_keys { "help", "version", "window_width", "window_height" };

    const std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);

    if (!command_line_master.check_keys(valid_keys))
    {
        std::cerr << "ERROR: 1 or more invalid command line parameters given.\n";

        const std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);

        for (std::vector<std::string>::const_iterator it = invalid_keys.begin(); it != invalid_keys.end(); it++)
        {
            std::cerr << "Invalid key: " << *it << "\n";
        }

        return 1;
    }

    int input_method_in_use = yli::input::KEYBOARD;

    // keypress callbacks.
    std::vector<yli::callback_system::KeyAndCallbackStruct> action_mode_keypress_callback_engines = std::vector<yli::callback_system::KeyAndCallbackStruct>();
    std::vector<yli::callback_system::KeyAndCallbackStruct> action_mode_continuous_keypress_callback_engines = std::vector<yli::callback_system::KeyAndCallbackStruct>();

    // This vector points to current keypress callback engines vector.
    std::vector<yli::callback_system::KeyAndCallbackStruct>* current_keypress_callback_engine_vector_pointer = &action_mode_keypress_callback_engines;

    // keyrelease callbacks.
    std::vector<yli::callback_system::KeyAndCallbackStruct> action_mode_keyrelease_callback_engines = std::vector<yli::callback_system::KeyAndCallbackStruct>();

    // This vector points to current keyrelease callback engines vector.
    std::vector<yli::callback_system::KeyAndCallbackStruct>* current_keyrelease_callback_engine_vector_pointer = &action_mode_keyrelease_callback_engines;

    // Create the `Universe`, store it in `my_universe`.
    std::cout << "Creating yli::ontology::Entity* my_universe_entity ...\n";
    yli::ontology::UniverseStruct universe_struct;
    std::stringstream window_title_stringstream;
    window_title_stringstream << "Hirvi " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version;
    universe_struct.window_title = window_title_stringstream.str();

    if (command_line_master.is_key("window_width") &&
            yli::string::check_if_unsigned_integer_string(command_line_master.get_value("window_width")))
    {
        const std::string window_width = command_line_master.get_value("window_width");
        std::size_t index = 0;
        universe_struct.window_width = yli::string::extract_uint32_t_value_from_string(window_width, index, nullptr, nullptr);
    }

    if (command_line_master.is_key("window_height") &&
            yli::string::check_if_unsigned_integer_string(command_line_master.get_value("window_height")))
    {
        const std::string window_height = command_line_master.get_value("window_height");
        std::size_t index = 0;
        universe_struct.window_height = yli::string::extract_uint32_t_value_from_string(window_height, index, nullptr, nullptr);
    }

    universe_struct.current_keypress_callback_engine_vector_pointer_pointer = &current_keypress_callback_engine_vector_pointer;
    universe_struct.current_keyrelease_callback_engine_vector_pointer_pointer = &current_keyrelease_callback_engine_vector_pointer;
    yli::ontology::Universe* const my_universe = new yli::ontology::Universe(universe_struct);
    my_universe->set_name("universe");

    yli::ontology::EntityFactory* const entity_factory = my_universe->get_entity_factory();

    yli::audio::AudioMaster* audio_master = my_universe->get_audio_master();

    const float earth_radius = 6371.0f; // in kilometres

    yli::config::SettingStruct planet_radius_setting_struct(std::make_shared<yli::common::AnyValue>(earth_radius));
    planet_radius_setting_struct.name = "planet_radius";
    planet_radius_setting_struct.setting_master = my_universe->get_setting_master();
    planet_radius_setting_struct.activate_callback = &yli::config::SettingMaster::activate_planet_radius; // planet radius may be for a planet or a moon.
    planet_radius_setting_struct.should_ylikuutio_call_activate_callback_now = true;
    new yli::config::Setting(planet_radius_setting_struct);

    std::cout << "Creating yli::callback_system::CallbackEngine* cleanup_callback_engine ...\n";
    yli::callback_system::CallbackEngine cleanup_callback_engine = yli::callback_system::CallbackEngine();
    new yli::callback_system::CallbackObject(nullptr, &cleanup_callback_engine);

    if (my_universe->get_window() == nullptr)
    {
        std::cerr << "Failed to open SDL window.\n";
        cleanup_callback_engine.execute();
        return -1;
    }

    my_universe->create_context();

    // Initialize GLEW.
    if (!yli::opengl::init_glew())
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    yli::input::disable_cursor();
    yli::input::enable_relative_mouse_mode();

    // Enable depth test.
    yli::opengl::enable_depth_test();
    // Accept fragment if it is closer to the camera than the former one.
    yli::opengl::set_depth_func_to_less();

    // Cull triangles whose normal is not towards the camera.
    yli::opengl::cull_triangles();

    std::cout << "Setting up console ...\n";
    app::set_console(my_universe->get_setting_master(), 15, 0, 0, 39);

    // Create the `World`.

    std::cout << "Creating yli::ontology::Entity* earth_world_entity ...\n";
    yli::ontology::Entity* const earth_world_entity = entity_factory->create_World();
    std::cout << "Creating yli::ontology::World* earth_world ...\n";
    yli::ontology::World* const earth_world = dynamic_cast<yli::ontology::World*>(earth_world_entity);

    if (earth_world == nullptr)
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    std::cout << "Setting earth_world as the active world ...\n";
    my_universe->set_active_world(earth_world);

    // Create the `Scene`s.
    // The `Scene`s will be created in the following order:
    // 1. Helsinki
    // 2. Joensuu

    // Helsinki `Scene` begins here.

    std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity and its contents ...\n";
    yli::ontology::Entity* const helsinki_east_downtown_scene_entity = ajokki::create_helsinki_east_downtown_scene(entity_factory, earth_world);

    if (helsinki_east_downtown_scene_entity == nullptr)
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    std::cout << "Creating yli::ontology::Scene* helsinki_east_downtown_scene ...\n";
    yli::ontology::Scene* const helsinki_east_downtown_scene = dynamic_cast<yli::ontology::Scene*>(helsinki_east_downtown_scene_entity);

    my_universe->is_flight_mode_in_use = true;

    if (helsinki_east_downtown_scene == nullptr)
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    // Set `helsinki_east_downtown_scene` to be the currently active `Scene` in `earth_world`.
    std::cout << "Setting helsinki_east_downtown_scene as the active scene ...\n";
    earth_world->set_active_scene(helsinki_east_downtown_scene);

    // Helsinki `Scene` ends here.

    // Joensuu `Scene` begins here.

    std::cout << "Creating yli::ontology::Scene* joensuu_center_west_scene and its contents ...\n";
    if (ajokki::create_joensuu_center_west_scene(entity_factory, earth_world) == nullptr)
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    // Joensuu `Scene` ends here.

    my_universe->turbo_factor = 100.0f;
    my_universe->twin_turbo_factor = 500.0f;

    // Initialize our little text library with the Holstein font.
    const char* const char_g_font_texture_filename = "Holstein.bmp";
    const char* const char_g_font_texture_file_format = "bmp";

    std::cout << "Creating yli::ontology::Entity* my_font2D_entity ...\n";
    yli::ontology::Entity* const my_font2D_entity = entity_factory->create_Font2D(
            my_universe->get_window_width(),
            my_universe->get_window_height(),
            char_g_font_texture_filename,
            char_g_font_texture_file_format);
    std::cout << "Creating yli::ontology::Font2D* my_font2D ...\n";
    yli::ontology::Font2D* const my_font2D = dynamic_cast<yli::ontology::Font2D*>(my_font2D_entity);

    if (my_font2D == nullptr)
    {
        std::cerr << "Failed to create Font2D.\n";
        cleanup_callback_engine.execute();
        return -1;
    }

    std::cout << "Font2D created successfully.\n";
    my_font2D->set_name("my_font2D");

    my_universe->set_active_font2D(my_font2D);
    yli::console::Console* const my_console = my_universe->get_console();
    my_console->print_text("Welcome! Please write \"help\" for more");
    my_console->print_text("information.");

    /*********************************************************************
     *  Callback engines for action mode keyreleases begin here.         *
     *********************************************************************/

    std::cout << "Defining action mode keyrelease callback engines.\n";

    // Callback code for left Control release: release first turbo.
    yli::callback_system::CallbackEngine* const release_first_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const release_first_turbo_callback_object = new yli::callback_system::CallbackObject(
            &app::release_first_turbo,
            release_first_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, release_first_turbo_callback_object);

    // Callback code for right Control release: release second turbo.
    yli::callback_system::CallbackEngine* const release_second_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const release_second_turbo_callback_object = new yli::callback_system::CallbackObject(
            &app::release_second_turbo,
            release_second_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, release_second_turbo_callback_object);

    // Callback code for I release: enable_toggle invert mouse.
    yli::callback_system::CallbackEngine* const enable_toggle_invert_mouse_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const enable_toggle_invert_mouse_callback_object = new yli::callback_system::CallbackObject(
            &app::enable_toggle_invert_mouse,
            enable_toggle_invert_mouse_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, enable_toggle_invert_mouse_callback_object);

    // Callback code for F release: enable_toggle flight mode.
    yli::callback_system::CallbackEngine* const enable_toggle_flight_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const enable_toggle_flight_mode_callback_object = new yli::callback_system::CallbackObject(
            &app::enable_toggle_flight_mode,
            enable_toggle_flight_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, enable_toggle_flight_mode_callback_object);

    // Callback code for F1 release: enable toggle help mode.
    yli::callback_system::CallbackEngine* const enable_toggle_help_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const enable_toggle_help_mode_callback_object = new yli::callback_system::CallbackObject(
            &app::enable_toggle_help_mode,
            enable_toggle_help_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, enable_toggle_help_mode_callback_object);

    /*********************************************************************
     *  Callback engines for action mode keypresses begin here.          *
     *********************************************************************/

    std::cout << "Defining action mode keypress callback engines.\n";

    // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
    yli::callback_system::CallbackEngine* const enter_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enter_console, enter_console_callback_engine, my_console);

    // Callback code for esc: exit program.
    yli::callback_system::CallbackEngine* const exit_program_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::callback_system::CallbackObject(&app::exit_program, exit_program_callback_engine);

    // Callback code for left Control: first turbo.
    yli::callback_system::CallbackEngine* const first_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const first_turbo_callback_object = new yli::callback_system::CallbackObject(
            &app::first_turbo,
            first_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, first_turbo_callback_object);

    // Callback code for right Control: second turbo.
    yli::callback_system::CallbackEngine* const second_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const second_turbo_callback_object = new yli::callback_system::CallbackObject(
            &app::second_turbo,
            second_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, second_turbo_callback_object);

    // Callback code for key up: move forward.
    yli::callback_system::CallbackEngine* const move_forward_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const move_forward_callback_object = new yli::callback_system::CallbackObject(
            &app::move_forward,
            move_forward_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, move_forward_callback_object);

    // Callback code for key down: move backward.
    yli::callback_system::CallbackEngine* const move_backward_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const move_backward_callback_object = new yli::callback_system::CallbackObject(
            &app::move_backward,
            move_backward_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, move_backward_callback_object);

    // Callback code for key left: strafe left.
    yli::callback_system::CallbackEngine* const strafe_left_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const strafe_left_callback_object = new yli::callback_system::CallbackObject(
            &app::strafe_left,
            strafe_left_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, strafe_left_callback_object);

    // Callback code for key right: strafe right.
    yli::callback_system::CallbackEngine* const strafe_right_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const strafe_right_callback_object = new yli::callback_system::CallbackObject(
            &app::strafe_right,
            strafe_right_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, strafe_right_callback_object);

    // Callback code for space: ascent.
    yli::callback_system::CallbackEngine* const ascent_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const ascent_callback_object = new yli::callback_system::CallbackObject(
            &app::ascent,
            ascent_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, ascent_callback_object);

    // Callback code for enter: descent.
    yli::callback_system::CallbackEngine* const descent_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const descent_callback_object = new yli::callback_system::CallbackObject(
            &app::descent,
            descent_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, descent_callback_object);

    // Callback code for I: toggle invert mouse.
    yli::callback_system::CallbackEngine* const toggle_invert_mouse_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const toggle_invert_mouse_callback_object = new yli::callback_system::CallbackObject(
            &app::toggle_invert_mouse,
            toggle_invert_mouse_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, toggle_invert_mouse_callback_object);

    // Callback code for F: toggle flight mode.
    yli::callback_system::CallbackEngine* const toggle_flight_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const toggle_flight_mode_callback_object = new yli::callback_system::CallbackObject(
            &app::toggle_flight_mode,
            toggle_flight_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, toggle_flight_mode_callback_object);

    // Callback code for F1: toggle help mode.
    yli::callback_system::CallbackEngine* const toggle_help_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* const toggle_help_mode_callback_object = new yli::callback_system::CallbackObject(
            &app::toggle_help_mode,
            toggle_help_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::common::AnyValue>(my_universe), false, toggle_help_mode_callback_object);

    /*********************************************************************
     *  Callback engines for console keyreleases begin here.             *
     *********************************************************************/

    std::cout << "Defining console keyrelease callback engines.\n";

    // Callback code for left Control release.
    yli::callback_system::CallbackEngine* const release_left_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_left_control_in_console, release_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control release.
    yli::callback_system::CallbackEngine* const release_right_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_right_control_in_console, release_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt release.
    yli::callback_system::CallbackEngine* const release_left_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_left_alt_in_console, release_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt release.
    yli::callback_system::CallbackEngine* const release_right_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_right_alt_in_console, release_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift release.
    yli::callback_system::CallbackEngine* const release_left_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_left_shift_in_console, release_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift release.
    yli::callback_system::CallbackEngine* const release_right_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_right_shift_in_console, release_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up release: enable move to previous input.
    yli::callback_system::CallbackEngine* const enable_move_to_previous_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_move_to_previous_input, enable_move_to_previous_input_callback_engine, my_console);

    // Callback code for key down release: enable move to next input.
    yli::callback_system::CallbackEngine* const enable_move_to_next_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_move_to_next_input, enable_move_to_next_input_callback_engine, my_console);

    // Callback code for backspace release: enable backspace.
    yli::callback_system::CallbackEngine* const enable_backspace_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_backspace, enable_backspace_callback_engine, my_console);

    // Callback code for enter release: enable Enter key.
    yli::callback_system::CallbackEngine* const enable_enter_key_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_enter_key, enable_enter_key_callback_engine, my_console);

    // Callback code for C release: enable Control-C.
    yli::callback_system::CallbackEngine* const enable_ctrl_c_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_ctrl_c, enable_ctrl_c_callback_engine, my_console);

    // Callback code for W release: enable Control-W.
    yli::callback_system::CallbackEngine* const enable_ctrl_w_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_ctrl_w, enable_ctrl_w_callback_engine, my_console);

    // Callback code for PgUp release: enable PgUp.
    yli::callback_system::CallbackEngine* const enable_page_up_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_page_up, enable_page_up_callback_engine, my_console);

    // Callback code for PgDn release: enable PgDn.
    yli::callback_system::CallbackEngine* const enable_page_down_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_page_down, enable_page_down_callback_engine, my_console);

    // Callback code for Home release: enable Home.
    yli::callback_system::CallbackEngine* const enable_home_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_home, enable_home_callback_engine, my_console);

    // Callback code for End release: enable End.
    yli::callback_system::CallbackEngine* const enable_end_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_end, enable_end_callback_engine, my_console);

    /*********************************************************************
     *  Callback engines for console keypresses begin here.              *
     *********************************************************************/

    std::cout << "Defining console keypress callback engines.\n";

    // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
    yli::callback_system::CallbackEngine* const exit_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::exit_console, exit_console_callback_engine, my_console);

    // Callback code for left Control press.
    yli::callback_system::CallbackEngine* const press_left_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_left_control_in_console, press_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control press.
    yli::callback_system::CallbackEngine* const press_right_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_right_control_in_console, press_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt press.
    yli::callback_system::CallbackEngine* const press_left_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_left_alt_in_console, press_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt press.
    yli::callback_system::CallbackEngine* const press_right_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_right_alt_in_console, press_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift press.
    yli::callback_system::CallbackEngine* const press_left_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_left_shift_in_console, press_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift press.
    yli::callback_system::CallbackEngine* const press_right_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_right_shift_in_console, press_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up: move to previous input.
    yli::callback_system::CallbackEngine* const move_to_previous_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::move_to_previous_input, move_to_previous_input_callback_engine, my_console);

    // Callback code for key down: move to next input.
    yli::callback_system::CallbackEngine* const move_to_next_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::move_to_next_input, move_to_next_input_callback_engine, my_console);

    // Callback code for backspace: delete character left of cursor from current input in console.
    yli::callback_system::CallbackEngine* const backspace_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::backspace, backspace_callback_engine, my_console);

    // Callback code for Enter key.
    yli::callback_system::CallbackEngine* const enter_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enter_key, enter_callback_engine, my_console);

    // Callback code for C: Control-C.
    yli::callback_system::CallbackEngine* const ctrl_c_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::ctrl_c, ctrl_c_callback_engine, my_console);

    // Callback code for W: Control-W.
    yli::callback_system::CallbackEngine* const ctrl_w_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::ctrl_w, ctrl_w_callback_engine, my_console);

    // Callback code for PgUp.
    yli::callback_system::CallbackEngine* const page_up_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::page_up, page_up_callback_engine, my_console);

    // Callback code for PgDn.
    yli::callback_system::CallbackEngine* const page_down_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::page_down, page_down_callback_engine, my_console);

    // Callback code for Home.
    yli::callback_system::CallbackEngine* const home_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::home, home_callback_engine, my_console);

    // Callback code for End.
    yli::callback_system::CallbackEngine* const end_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::end, end_callback_engine, my_console);

    // Keyrelease callbacks for action mode.
    // Key releases are checked in the order of this struct.
    action_mode_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, release_first_turbo_callback_engine });
    action_mode_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, release_second_turbo_callback_engine });
    action_mode_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_I, enable_toggle_invert_mouse_callback_engine });
    action_mode_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_F, enable_toggle_flight_mode_callback_engine });
    action_mode_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_F1, enable_toggle_help_mode_callback_engine });

    // Keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_GRAVE, enter_console_callback_engine });
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_ESCAPE, exit_program_callback_engine });
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, first_turbo_callback_engine });
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, second_turbo_callback_engine });
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_I, toggle_invert_mouse_callback_engine });
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_F, toggle_flight_mode_callback_engine });
    action_mode_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_F1, toggle_help_mode_callback_engine });

    // Continuous keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_continuous_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_UP, move_forward_callback_engine });
    action_mode_continuous_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_DOWN, move_backward_callback_engine });
    action_mode_continuous_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LEFT, strafe_left_callback_engine });
    action_mode_continuous_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RIGHT, strafe_right_callback_engine });
    action_mode_continuous_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_SPACE, ascent_callback_engine });
    action_mode_continuous_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RETURN, descent_callback_engine });

    // Keyrelease callbacks for console.
    // Key releases are checked in the order of this struct.
    std::vector<yli::callback_system::KeyAndCallbackStruct> console_keyrelease_callback_engines = std::vector<yli::callback_system::KeyAndCallbackStruct>();
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, release_left_control_in_console_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, release_right_control_in_console_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LALT, release_left_alt_in_console_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RALT, release_right_alt_in_console_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LSHIFT, release_left_shift_in_console_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RSHIFT, release_right_shift_in_console_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_UP, enable_move_to_previous_input_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_DOWN, enable_move_to_next_input_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_BACKSPACE, enable_backspace_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RETURN, enable_enter_key_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_C, enable_ctrl_c_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_W, enable_ctrl_w_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_PAGEUP, enable_page_up_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_PAGEDOWN, enable_page_down_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_HOME, enable_home_callback_engine });
    console_keyrelease_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_END, enable_end_callback_engine });
    my_console->set_my_keyrelease_callback_engine_vector_pointer(&console_keyrelease_callback_engines);

    // Keypress callbacks for console.
    // Keypresses are checked in the order of this struct.
    std::vector<yli::callback_system::KeyAndCallbackStruct> console_keypress_callback_engines = std::vector<yli::callback_system::KeyAndCallbackStruct>();
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_GRAVE, exit_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, press_left_control_in_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, press_right_control_in_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LALT, press_left_alt_in_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RALT, press_right_alt_in_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_LSHIFT, press_left_shift_in_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RSHIFT, press_right_shift_in_console_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_UP, move_to_previous_input_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_DOWN, move_to_next_input_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_BACKSPACE, backspace_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_RETURN, enter_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_C, ctrl_c_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_W, ctrl_w_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_PAGEUP, page_up_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_PAGEDOWN, page_down_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_HOME, home_callback_engine });
    console_keypress_callback_engines.push_back(yli::callback_system::KeyAndCallbackStruct { SDL_SCANCODE_END, end_callback_engine });
    my_console->set_my_keypress_callback_engine_vector_pointer(&console_keypress_callback_engines);

    /*********************************************************************
     * Callback engines for console commands begin here.                 *
     * These define what commands there are available in the console     *
     * and what each command does.                                       *
     *********************************************************************/

    std::cout << "Defining console command callback engines.\n";

    // Config callbacks.
    my_console->add_command_callback("set", &yli::config::SettingMaster::set_and_print);
    my_console->add_command_callback("get", &yli::config::SettingMaster::get_and_print);

    // `Entity` handling callbacks.
    my_console->add_command_callback("activate", &yli::ontology::Universe::activate);
    my_console->add_command_callback("delete", &yli::ontology::Universe::delete_entity);
    my_console->add_command_callback("info", &yli::ontology::Universe::info);
    my_console->add_command_callback("bind", &yli::ontology::Universe::bind);
    my_console->add_command_callback("AnyValueEntity", &yli::ontology::Universe::create_AnyValue);
    my_console->add_command_callback("AnyStructEntity", &yli::ontology::Universe::create_AnyStruct);

    // Exit program callbacks.
    my_console->add_command_callback("bye", &app::quit);
    my_console->add_command_callback("chau", &app::quit);
    my_console->add_command_callback("ciao", &app::quit);
    my_console->add_command_callback("heippa", &app::quit);
    my_console->add_command_callback("quit", &app::quit);
    my_console->add_command_callback("sayonara", &app::quit);

    // Other callbacks.
    my_console->add_command_callback("eval", &yli::ontology::Universe::eval);
    my_console->add_command_callback("help", &app::help);
    my_console->add_command_callback("version", &hirvi::version);
    my_console->add_command_callback("clear", &yli::console::Console::clear);
    my_console->add_command_callback("screenshot", &yli::ontology::Universe::screenshot);

    // For speed computation.
    double last_time_to_display_FPS = yli::time::get_time();
    double last_time_for_display_sync = yli::time::get_time();
    int32_t number_of_frames = 0;

    bool has_mouse_focus = true;

    audio_master->add_to_playlist("Hirvi_playlist", "414257__sss-samples__chipland-loop-120-bpm-a-major.wav");
    audio_master->add_to_playlist("Hirvi_playlist", "414270__greek555__sample-97-bpm.wav");
    // audio_master->add_to_playlist("Hirvi_playlist", "419588__greek555__dreaming-of-me.ogg");
    // audio_master->add_to_playlist("Hirvi_playlist", "416882__greek555__blue-play.ogg");
    // audio_master->add_to_playlist("Hirvi_playlist", "395487__frankum__tecno-pop-base-and-guitar-2.ogg");
    audio_master->play_playlist("Hirvi_playlist");

    SDL_Event sdl_event;
    std::string ms_frame_text;

    // Print angles and cartesian coordinates on bottom left corner.
    yli::ontology::TextStruct angles_and_coordinates_text_struct;
    angles_and_coordinates_text_struct.font2D_parent = my_font2D;
    angles_and_coordinates_text_struct.screen_width = my_universe->get_window_width();
    angles_and_coordinates_text_struct.screen_height = my_universe->get_window_height();
    angles_and_coordinates_text_struct.x = 0;
    angles_and_coordinates_text_struct.y = 0;
    angles_and_coordinates_text_struct.text_size = my_universe->get_text_size();
    angles_and_coordinates_text_struct.font_size = my_universe->get_font_size();
    angles_and_coordinates_text_struct.font_texture_file_format = "bmp";
    angles_and_coordinates_text_struct.horizontal_alignment = "left";
    angles_and_coordinates_text_struct.vertical_alignment = "bottom";
    yli::ontology::Text2D* angles_and_coordinates_text2D = new yli::ontology::Text2D(my_universe, angles_and_coordinates_text_struct);

    // Print spherical coordinates on second line from the bottom left.
    yli::ontology::TextStruct spherical_coordinates_text_struct;
    spherical_coordinates_text_struct.font2D_parent = my_font2D;
    spherical_coordinates_text_struct.screen_width = my_universe->get_window_width();
    spherical_coordinates_text_struct.screen_height = my_universe->get_window_height();
    spherical_coordinates_text_struct.x = 0;
    spherical_coordinates_text_struct.y = 2 * my_universe->get_text_size();
    spherical_coordinates_text_struct.text_size = my_universe->get_text_size();
    spherical_coordinates_text_struct.font_size = my_universe->get_font_size();
    spherical_coordinates_text_struct.horizontal_alignment = "left";
    spherical_coordinates_text_struct.vertical_alignment = "bottom";
    yli::ontology::Text2D* spherical_coordinates_text2D = new yli::ontology::Text2D(my_universe, spherical_coordinates_text_struct);

    // Print time data on top left corner.
    yli::ontology::TextStruct time_text_struct;
    time_text_struct.font2D_parent = my_font2D;
    time_text_struct.screen_width = my_universe->get_window_width();
    time_text_struct.screen_height = my_universe->get_window_height();
    time_text_struct.x = 0;
    time_text_struct.y = my_universe->get_window_height();
    time_text_struct.text_size = my_universe->get_text_size();
    time_text_struct.font_size = my_universe->get_font_size();
    time_text_struct.font_texture_file_format = "bmp";
    time_text_struct.horizontal_alignment = "left";
    time_text_struct.vertical_alignment = "top";
    yli::ontology::Text2D* time_text2D = new yli::ontology::Text2D(my_universe, time_text_struct);

    // Print help text.
    yli::ontology::TextStruct help_text_struct;
    help_text_struct.font2D_parent = my_font2D;
    help_text_struct.screen_width = my_universe->get_window_width();
    help_text_struct.screen_height = my_universe->get_window_height();
    help_text_struct.x = 0;
    help_text_struct.y = my_universe->get_window_height() - (3 * my_universe->get_text_size());
    help_text_struct.text_size = my_universe->get_text_size();
    help_text_struct.font_size = my_universe->get_font_size();
    help_text_struct.font_texture_file_format = "bmp";
    help_text_struct.horizontal_alignment = "left";
    help_text_struct.vertical_alignment = "top";
    yli::ontology::Text2D* help_text2D = new yli::ontology::Text2D(my_universe, help_text_struct);

    // Print frame rate data on top right corner.
    yli::ontology::TextStruct frame_rate_text_struct;
    frame_rate_text_struct.font2D_parent = my_font2D;
    frame_rate_text_struct.screen_width = my_universe->get_window_width();
    frame_rate_text_struct.screen_height = my_universe->get_window_height();
    frame_rate_text_struct.x = my_universe->get_window_width();;
    frame_rate_text_struct.y = my_universe->get_window_height();
    frame_rate_text_struct.text_size = my_universe->get_text_size();
    frame_rate_text_struct.font_size = my_universe->get_font_size();
    frame_rate_text_struct.font_texture_file_format = "bmp";
    frame_rate_text_struct.horizontal_alignment = "right";
    frame_rate_text_struct.vertical_alignment = "top";
    yli::ontology::Text2D* frame_rate_text2D = new yli::ontology::Text2D(my_universe, frame_rate_text_struct);

    std::cout << "Setting up background colors ...\n";
    app::set_background_colors(my_universe->get_setting_master(), 0.0f, 0.0f, 1.0f, 0.0f);
    std::cout << "Setting up wireframe state ...\n";
    app::set_wireframe(my_universe->get_setting_master(), false);
    std::cout << "Setting up movement ...\n";
    app::set_movement(my_universe->get_setting_master());
    std::cout << "Setting up location and orientation ...\n";
    app::set_location_and_orientation(my_universe->get_setting_master());
    std::cout << "Setting up debug variables ...\n";
    app::set_flight_mode(my_universe->get_setting_master(), true);

    yli::sdl::flush_sdl_event_queue();

    while (!my_universe->get_is_exit_requested())
    {
        const double current_time_in_main_loop = yli::time::get_time();

        if (current_time_in_main_loop - last_time_for_display_sync >= (1.0f / my_universe->get_max_FPS()))
        {
            last_time_for_display_sync = yli::time::get_time();

            number_of_frames++;

            while (current_time_in_main_loop - last_time_to_display_FPS >= 1.0f)
            {
                // If last `std::stringstream` here was more than 1 sec ago,
                // std::stringstream` and reset number of frames.
                if (number_of_frames > 0)
                {
                    std::stringstream ms_frame_text_stringstream;
                    ms_frame_text_stringstream << std::fixed << std::setprecision(2) << 1000.0f / static_cast<double>(number_of_frames) << " ms/frame; " <<
                        number_of_frames << " Hz";
                    ms_frame_text = ms_frame_text_stringstream.str();
                    frame_rate_text2D->change_string(ms_frame_text);
                    number_of_frames = 0;
                }

                // `last_time_to_display_FPS` needs to be incremented to avoid infinite loop.
                last_time_to_display_FPS += 1.0f;

                // Update audio also (in case the sound has reached the end).
                audio_master->update();
            }

            // Clear the screen.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            my_universe->compute_delta_time();

            my_universe->mouse_x = my_universe->get_window_width() / 2;
            my_universe->mouse_y = my_universe->get_window_height() / 2;

            // Poll all SDL events.
            while (SDL_PollEvent(&sdl_event))
            {
                if (sdl_event.type == SDL_MOUSEMOTION)
                {
                    my_universe->mouse_x += sdl_event.motion.xrel; // horizontal motion relative to screen center.
                    my_universe->mouse_y += sdl_event.motion.yrel; // vertical motion relative to screen center.
                }
                else if (sdl_event.type == SDL_KEYDOWN)
                {
                    const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                    for (std::size_t i = 0; i < current_keypress_callback_engine_vector_pointer->size(); i++)
                    {
                        if (current_keypress_callback_engine_vector_pointer->at(i).keycode == scancode)
                        {
                            yli::callback_system::CallbackEngine* const callback_engine = current_keypress_callback_engine_vector_pointer->at(i).callback_engine;
                            const std::shared_ptr<yli::common::AnyValue> any_value = callback_engine->execute();

                            if (any_value != nullptr &&
                                    any_value->type == yli::common::UINT32_T)
                            {
                                if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Do not display help screen when in console.
                                    my_universe->can_display_help_screen = false;
                                }
                                else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Enable display help screen when not in console.
                                    my_universe->can_display_help_screen = true;
                                }
                                else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                                {
                                    my_universe->request_exit();
                                }

                                // Process no more than 1 callback for each keypress.
                                break;
                            }
                        }
                    }

                    my_console->process_key_event(sdl_event.key);
                }
                else if (sdl_event.type == SDL_KEYUP)
                {
                    const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                    for (std::size_t i = 0; i < current_keyrelease_callback_engine_vector_pointer->size(); i++)
                    {
                        if (current_keyrelease_callback_engine_vector_pointer->at(i).keycode == scancode)
                        {
                            yli::callback_system::CallbackEngine* const callback_engine = current_keyrelease_callback_engine_vector_pointer->at(i).callback_engine;
                            const std::shared_ptr<yli::common::AnyValue> any_value = callback_engine->execute();

                            if (any_value != nullptr &&
                                    any_value->type == yli::common::UINT32_T)
                            {
                                if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Do not display help screen when in console.
                                    my_universe->can_display_help_screen = false;
                                }
                                else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Enable display help screen when not in console.
                                    my_universe->can_display_help_screen = true;
                                }
                                else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                                {
                                    my_universe->request_exit();
                                }

                                // Process no more than 1 callback for each keyrelease.
                                break;
                            }
                        }
                    }
                }
                else if (sdl_event.type == SDL_WINDOWEVENT)
                {
                    if (sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                    {
                        has_mouse_focus = true;
                    }
                    else if (sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                    {
                        has_mouse_focus = false;
                    }
                }
                else if (sdl_event.type == SDL_QUIT)
                {
                    my_universe->request_exit();
                }
            }

            // mouse position.
            const double xpos = static_cast<double>(my_universe->mouse_x);
            const double ypos = static_cast<double>(my_universe->mouse_y);

            // Reset mouse position for next frame.
            if (has_mouse_focus)
            {
                yli::input::set_cursor_position(
                        my_universe->get_window(),
                        static_cast<double>(my_universe->get_window_width()) / 2,
                        static_cast<double>(my_universe->get_window_height()) / 2);

                if (my_universe->has_mouse_ever_moved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
                {
                    my_universe->has_mouse_ever_moved = true;

                    // Compute new orientation.
                    my_universe->current_camera_horizontal_angle += my_universe->mouse_speed * static_cast<float>(my_universe->get_window_width() / 2 - xpos);
                    my_universe->current_camera_horizontal_angle = remainder(my_universe->current_camera_horizontal_angle, (2.0f * PI));

                    if (my_universe->is_invert_mouse_in_use)
                    {
                        // Invert mouse.
                        my_universe->current_camera_vertical_angle -= my_universe->mouse_speed * static_cast<float>(my_universe->get_window_height() / 2 - ypos);
                    }
                    else
                    {
                        // Don't invert mouse.
                        my_universe->current_camera_vertical_angle += my_universe->mouse_speed * static_cast<float>(my_universe->get_window_height() / 2 - ypos);
                    }

                    my_universe->current_camera_vertical_angle = remainder(my_universe->current_camera_vertical_angle, (2.0f * PI));
                }
            }

            // Direction: spherical coordinates to cartesian coordinates conversion.
            my_universe->current_camera_direction = glm::vec3(
                    cos(my_universe->current_camera_vertical_angle) * sin(my_universe->current_camera_horizontal_angle),
                    sin(my_universe->current_camera_vertical_angle),
                    cos(my_universe->current_camera_vertical_angle) * cos(my_universe->current_camera_horizontal_angle));

            // Right vector.
            my_universe->current_camera_right = glm::vec3(
                    sin(my_universe->current_camera_horizontal_angle - PI/2.0f),
                    0,
                    cos(my_universe->current_camera_horizontal_angle - PI/2.0f));

            // Up vector.
            my_universe->current_camera_up = glm::cross(my_universe->current_camera_right, my_universe->current_camera_direction);

            if (!my_console->get_in_console())
            {
                const uint8_t* const current_key_states = SDL_GetKeyboardState(nullptr);

                // Check for keypresses and call corresponding callbacks.
                for (std::size_t i = 0; i < action_mode_continuous_keypress_callback_engines.size(); i++)
                {
                    bool is_pressed = false;

                    if (input_method_in_use == yli::input::KEYBOARD)
                    {
                        if (current_key_states[action_mode_continuous_keypress_callback_engines.at(i).keycode] == 1) // 1 = pressed, 0 = not pressed.
                        {
                            is_pressed = true;
                        }
                    }
                    else if (input_method_in_use == yli::input::INPUT_FILE)
                    {
                        // TODO: implement optionally loading keyreleases from a file (do not execute `SDL_GetKeyboardState` in that case).
                        if (false)
                        {
                            is_pressed = true;
                        }
                    }
                    else
                    {
                        std::cerr << "Unsupported input method: " << input_method_in_use << "\n";
                    }

                    if (is_pressed)
                    {
                        yli::callback_system::CallbackEngine* const callback_engine = action_mode_continuous_keypress_callback_engines.at(i).callback_engine;
                        const std::shared_ptr<yli::common::AnyValue> any_value = callback_engine->execute();

                        if (any_value != nullptr &&
                                any_value->type == yli::common::UINT32_T)
                        {
                            if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                            {
                                // Do not display help screen when in console.
                                my_universe->can_display_help_screen = false;
                                break;
                            }
                            else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                            {
                                // Enable display help screen when not in console.
                                my_universe->can_display_help_screen = true;
                                break;
                            }
                            else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                            {
                                my_universe->request_exit();
                                break;
                            }
                        }
                    }
                }
            }

            // Gravity etc. physical phenomena.
            my_universe->do_physics();

            std::stringstream angles_and_coordinates_stringstream;
            angles_and_coordinates_stringstream << std::fixed << std::setprecision(2) <<
                my_universe->current_camera_horizontal_angle << "," <<
                my_universe->current_camera_vertical_angle << " rad; " <<
                RADIANS_TO_DEGREES(my_universe->current_camera_horizontal_angle) << "," <<
                RADIANS_TO_DEGREES(my_universe->current_camera_vertical_angle) << " deg\n" <<
                "(" <<
                my_universe->current_camera_cartesian_coordinates.x << "," <<
                my_universe->current_camera_cartesian_coordinates.y << "," <<
                my_universe->current_camera_cartesian_coordinates.z << ")";
            const std::string angles_and_coordinates_string = angles_and_coordinates_stringstream.str();
            angles_and_coordinates_text2D->change_string(angles_and_coordinates_string);

            std::stringstream time_stringstream;
            time_stringstream << std::fixed << std::setprecision(2) << yli::time::get_time() << " sec";
            const std::string time_string = time_stringstream.str();
            time_text2D->change_string(time_string);

            const std::string on_string = "on";
            const std::string off_string = "off";

            if (my_universe->in_help_mode && my_universe->can_display_help_screen)
            {
                std::stringstream help_text_stringstream;
                help_text_stringstream <<
                    "Hirvi " << yli::ontology::Universe::version << "\n"
                    "\n"
                    "arrow keys\n"
                    "space jump\n"
                    "enter duck\n"
                    "F1 help mode\n"
                    "`  enter console\n"
                    "I  invert mouse (" << (my_universe->is_invert_mouse_in_use ? on_string : off_string) << ")\n"
                    "F  flight mode (" << (my_universe->is_flight_mode_in_use ? on_string : off_string) << ")\n"
                    "Ctrl      turbo\n" <<
                    "Ctrl+Ctrl extra turbo\n";
                const std::string help_text_string = help_text_stringstream.str();
                help_text2D->change_string(help_text_string);
            }
            else
            {
                help_text2D->change_string("");
            }

            if (my_universe->testing_spherical_terrain_in_use)
            {
                std::stringstream spherical_coordinates_stringstream;
                spherical_coordinates_stringstream << std::fixed << std::setprecision(2) <<
                    "rho:" << my_universe->current_camera_spherical_coordinates.rho <<
                    "theta:" << my_universe->current_camera_spherical_coordinates.theta <<
                    "phi:" << my_universe->current_camera_spherical_coordinates.phi;
                std::string spherical_coordinates_string = spherical_coordinates_stringstream.str();
                spherical_coordinates_text2D->change_string(spherical_coordinates_string);
            }
            else
            {
                spherical_coordinates_text2D->change_string("");
            }

            // Render the `Universe`.
            my_universe->render();

            my_universe->finalize_delta_time_loop();
        }
    }

    // Do cleanup.
    cleanup_callback_engine.execute();

    return 0;
}
