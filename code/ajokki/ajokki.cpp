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

#include "ajokki_background_colors.hpp"
#include "ajokki_cleanup_callbacks.hpp"
#include "ajokki_console_callbacks.hpp"
#include "ajokki_helsinki_east_downtown_scene.hpp"
#include "ajokki_joensuu_center_west_scene.hpp"
#include "ajokki_keyboard_callbacks.hpp"
#include "ajokki_debug.hpp"
#include "ajokki_console.hpp"
#include "ajokki_movement.hpp"
#include "ajokki_location_and_orientation.hpp"
#include "ajokki_wireframe.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/console/console_command_callback.hpp"
#include "code/ylikuutio/console/console_struct.hpp"
#include "code/ylikuutio/console/console_callback_object.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/ontology/vboindexer.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/text3D.hpp"
#include "code/ylikuutio/ontology/text3D_struct.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/time/time.hpp"
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

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstdio>        // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// model filename.
// std::string g_model_filename = "cube.obj";
// std::string g_model_filename = "oma_icosphere.obj";
// std::string g_model_filename = "kirjainkuutio.obj";
// std::string g_model_filename = "noise1024x1024.bmp";
std::string g_model_filename = "noise256x256.bmp";
// std::string g_model_filename = "noise128x128.bmp";

// texture file format: bmp/...
std::string g_texture_file_format = "bmp";

// color channel to use for height data.
// std::string g_height_data_color_channel = "red";
// std::string g_height_data_color_channel = "green";
// std::string g_height_data_color_channel = "blue";
std::string g_height_data_color_channel = "mean"; // "all" is equivalent to "mean".

// texture filename.
// std::string_g_texture_filename = "kuutio-uv-numerot.bmp";
// std::string g_texture_filename = "punamusta.bmp";
std::string g_texture_filename = "GrassGreenTexture0002.bmp";

// font texture file format: bmp/...
std::string g_font_texture_file_format = "bmp";

// font texture filename.
// std::string g_font_texture_filename = "Holstein.DDS";
std::string g_font_texture_filename = "Holstein.bmp";

// background music filename.
std::string music_filename = "414270__greek555__sample-97-bpm.wav";

int main(int argc, char* argv[])
{
    std::vector<std::string> arg_vector;

    if (argc > 1)
    {
        arg_vector.assign(argv + 1, argv + argc);

        // Print command line arguments (without the executable name string).
        for (std::string argument : arg_vector)
        {
            std::cout << argument << "\n";
        }
    }
    else
    {
        std::cout << "no command line arguments.\n";
    }

    int input_method_in_use = ylikuutio::input::KEYBOARD;

    // Create the world, store it in `my_universe`.
    std::cout << "Creating ontology::Entity* my_universe_entity ...\n";
    UniverseStruct universe_struct;
    universe_struct.window_title = "Ajokki 0.0.1, powered by Ylikuutio 0.0.1";
    ontology::Universe* my_universe = new ontology::Universe(universe_struct);

    ontology::EntityFactory* entity_factory = my_universe->get_entity_factory();

    // Create the setting master, store it in `my_setting_master`.
    std::cout << "Creating config::SettingMaster* my_setting_master ...\n";
    config::SettingMaster* my_setting_master = new config::SettingMaster(my_universe);

    ylikuutio::audio::AudioMaster audio_master;

    float earth_radius = 6371.0f; // in kilometres

    SettingStruct planet_radius_setting_struct(std::make_shared<datatypes::AnyValue>(earth_radius));
    planet_radius_setting_struct.name = "planet_radius";
    planet_radius_setting_struct.setting_master = my_setting_master;
    planet_radius_setting_struct.activate_callback = &config::SettingMaster::activate_planet_radius; // world may be a planet or a moon.
    planet_radius_setting_struct.should_ylikuutio_call_activate_callback_now = true;
    new config::Setting(planet_radius_setting_struct);

    std::cout << "Creating callback_system::CallbackEngine* cleanup_callback_engine ...\n";
    callback_system::CallbackEngine* cleanup_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* cleanup_callback_object = new callback_system::CallbackObject(nullptr, cleanup_callback_engine);

    if (my_universe->get_window() == nullptr)
    {
        std::cerr << "Failed to open GLFW window.\n";
        cleanup_callback_engine->execute();
        return -1;
    }
    ylikuutio::opengl::make_context_current(my_universe->get_window());
    ylikuutio::input::disable_cursor(my_universe->get_window());

    // Initialize GLEW.
    if (!ylikuutio::opengl::init_glew())
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below.
    ylikuutio::input::set_sticky_keys(my_universe->get_window());
    ylikuutio::input::set_cursor_position(my_universe->get_window(), static_cast<double>(my_universe->get_window_width()) / 2, static_cast<double>(my_universe->get_window_height()) / 2);

    // Enable depth test.
    ylikuutio::opengl::enable_depth_test();
    // Accept fragment if it closer to the camera than the former one.
    ylikuutio::opengl::set_depth_func_to_less();

    // Cull triangles which normal is not towards the camera.
    ylikuutio::opengl::cull_triangles();

    std::cout << "Setting up background colors ...\n";
    ajokki::set_background_colors(my_setting_master);
    std::cout << "Setting up wireframe state ...\n";
    ajokki::set_wireframe(my_setting_master);
    std::cout << "Setting up movement ...\n";
    ajokki::set_movement(my_setting_master);
    std::cout << "Setting up location and orientation ...\n";
    ajokki::set_location_and_orientation(my_setting_master);
    std::cout << "Setting up debug variables ...\n";
    ajokki::set_debug_variables(my_setting_master);
    std::cout << "Setting up console ...\n";
    ajokki::set_console(my_setting_master);

    // Create the `World`s.

    std::cout << "Creating ontology::Entity* earth_world_entity ...\n";
    ontology::Entity* earth_world_entity = entity_factory->create_World();
    std::cout << "Creating ontology::World* earth_world ...\n";
    ontology::World* earth_world = dynamic_cast<ontology::World*>(earth_world_entity);

    if (earth_world == nullptr)
    {
        return -1;
    }

    std::cout << "Setting earth_world as the active world ...\n";
    my_universe->set_active_world(earth_world);

    // Create the `Scene`s.
    // The `Scene`s will be created in the following order:
    // 1. Helsinki
    // 2. Joensuu
    // 3. altiplano

    // Helsinki `Scene` begins here.

    std::cout << "Creating ontology::Entity* helsinki_east_downtown_scene_entity and its contents ...\n";
    ontology::Entity* helsinki_east_downtown_scene_entity = ajokki::create_helsinki_east_downtown_scene(entity_factory, earth_world);

    if (helsinki_east_downtown_scene_entity == nullptr)
    {
        return -1;
    }

    std::cout << "Creating ontology::Scene* helsinki_east_downtown_scene ...\n";
    ontology::Scene* helsinki_east_downtown_scene = dynamic_cast<ontology::Scene*>(helsinki_east_downtown_scene_entity);

    my_universe->is_flight_mode_in_use = true;

    if (helsinki_east_downtown_scene == nullptr)
    {
        return -1;
    }

    // Set `helsinki_east_downtown_scene` to be the currently active `Scene` in `earth_world`.
    std::cout << "Setting helsinki_east_downtown_scene as the active scene ...\n";
    earth_world->set_active_scene(helsinki_east_downtown_scene);

    // Helsinki `Scene` ends here.

    // Joensuu `Scene` begins here.

    std::cout << "Creating ontology::Scene* joensuu_center_west_scene and its contents ...\n";
    if (ajokki::create_joensuu_center_west_scene(entity_factory, earth_world) == nullptr)
    {
        return -1;
    }

    // Joensuu `Scene` ends here.

    // altiplano `Scene` begins here.

    std::cout << "Creating ontology::Entity* altiplano_scene_entity ...\n";
    ontology::Entity* altiplano_scene_entity = entity_factory->create_Scene(earth_world, -1.0f * std::numeric_limits<float>::infinity());
    std::cout << "Creating ontology::Scene* altiplano_scene ...\n";
    ontology::Scene* altiplano_scene = dynamic_cast<ontology::Scene*>(altiplano_scene_entity);

    if (altiplano_scene == nullptr)
    {
        std::cerr << "Failed to create Scene.\n";
        return -1;
    }

    altiplano_scene->set_name("altiplano_scene");

    // Set `altiplano_scene` to be the currently active `Scene`.
    // my_universe->set_active_scene(altiplano_scene);

    altiplano_scene->set_turbo_factor(5.0f);
    altiplano_scene->set_twin_turbo_factor(100.0f);

    // Create the shader, store it in `altiplano_shader`.
    ShaderStruct altiplano_shader_struct;
    altiplano_shader_struct.parent = altiplano_scene;
    altiplano_shader_struct.vertex_shader = "StandardShading.vertexshader";
    altiplano_shader_struct.fragment_shader = "StandardShading.fragmentshader";

    std::cout << "Creating ontology::Entity* altiplano_shader_entity ...\n";
    ontology::Entity* altiplano_shader_entity = entity_factory->create_Shader(altiplano_shader_struct);
    std::cout << "Creating ontology::Shader* altiplano_shader ...\n";
    ontology::Shader* altiplano_shader = dynamic_cast<ontology::Shader*>(altiplano_shader_entity);

    if (altiplano_shader == nullptr)
    {
        std::cerr << "Failed to create Shader.\n";
        return -1;
    }

    // Create the material, store it in `altiplano_grass_material`.
    MaterialStruct altiplano_grass_material_struct;
    altiplano_grass_material_struct.parent = altiplano_shader;
    altiplano_grass_material_struct.texture_file_format = g_texture_file_format;
    altiplano_grass_material_struct.texture_filename = g_texture_filename;

    std::cout << "Creating ontology::Entity* altiplano_grass_material_entity ...\n";
    ontology::Entity* altiplano_grass_material_entity = entity_factory->create_Material(altiplano_grass_material_struct);
    std::cout << "Creating ontology::Material* altiplano_grass_material ...\n";
    ontology::Material* altiplano_grass_material = dynamic_cast<ontology::Material*>(altiplano_grass_material_entity);

    if (altiplano_grass_material == nullptr)
    {
        std::cerr << "Failed to create grass Material.\n";
        return -1;
    }

    altiplano_grass_material->set_name("altiplano_grass_material");

    // Create the species, store it in `terrain_species`.
    SpeciesStruct(altiplano_terrain_species_struct);
    altiplano_terrain_species_struct.scene = altiplano_scene;
    altiplano_terrain_species_struct.shader = altiplano_shader;
    altiplano_terrain_species_struct.parent = altiplano_grass_material;
    altiplano_terrain_species_struct.model_file_format = "SRTM";
    altiplano_terrain_species_struct.model_filename = "./"; // for testing
    altiplano_terrain_species_struct.color_channel = g_height_data_color_channel;
    altiplano_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
    altiplano_terrain_species_struct.is_terrain = true;
    altiplano_terrain_species_struct.x_step = 1;
    altiplano_terrain_species_struct.z_step = 1;
    altiplano_terrain_species_struct.planet_radius = earth_radius;
    altiplano_terrain_species_struct.divisor = 1000.0f;

    std::cout << "Creating ontology::Entity* altiplano_terrain_species_entity ...\n";
    ontology::Entity* altiplano_terrain_species_entity = entity_factory->create_Species(altiplano_terrain_species_struct);
    std::cout << "Creating ontology::Species* altiplano_terrain_species ...\n";
    ontology::Species* altiplano_terrain_species = dynamic_cast<ontology::Species*>(altiplano_terrain_species_entity);

    if (altiplano_terrain_species == nullptr)
    {
        std::cerr << "Failed to create Species.\n";
        return -1;
    }

    altiplano_terrain_species->set_name("altiplano_terrain_species");

    // Create altiplano terrain.
    ObjectStruct altiplano_struct;
    altiplano_struct.species_parent = altiplano_terrain_species;
    altiplano_struct.cartesian_coordinates = std::make_shared<glm::vec3>(0.0f, 0.0f, 0.0f);
    altiplano_struct.rotate_angle = 0.0f;
    altiplano_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    altiplano_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    entity_factory->create_Object(altiplano_struct);
    // altiplano `Scene` ends here.

    my_universe->turbo_factor = 100.0f;
    my_universe->twin_turbo_factor = 500.0f;
    // keypress callbacks.
    std::vector<KeyAndCallbackStruct>* action_mode_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();

    // This vector points to current keypress callback engines vector.
    std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer;
    current_keypress_callback_engine_vector_pointer = &action_mode_keypress_callback_engines;

    // keyrelease callbacks.
    std::vector<KeyAndCallbackStruct>* action_mode_keyrelease_callback_engines = new std::vector<KeyAndCallbackStruct>();

    // This vector points to current keyrelease callback engines vector.
    std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer;
    current_keyrelease_callback_engine_vector_pointer = &action_mode_keyrelease_callback_engines;

    // Initialize our little text library with the Holstein font
    const char* char_g_font_texture_filename = g_font_texture_filename.c_str();
    const char* char_g_font_texture_file_format = g_font_texture_file_format.c_str();

    std::cout << "Creating ontology::Entity* my_font2D_entity ...\n";
    ontology::Entity* my_font2D_entity = entity_factory->create_Font2D(my_universe->get_window_width(), my_universe->get_window_height(), char_g_font_texture_filename, char_g_font_texture_file_format);
    std::cout << "Creating ontology::Font2D* my_font2D ...\n";
    ontology::Font2D* my_font2D = dynamic_cast<ontology::Font2D*>(my_font2D_entity);

    if (my_font2D == nullptr)
    {
        std::cerr << "Failed to create Font2D.\n";
        return -1;
    }

    std::cout << "Font2D created successfully.\n";

    std::unordered_map<std::string, ConsoleCommandCallback> command_callback_map;

    ConsoleStruct console_struct;
    console_struct.current_keypress_callback_engine_vector_pointer_pointer = current_keypress_callback_engine_vector_pointer;
    console_struct.current_keyrelease_callback_engine_vector_pointer_pointer = current_keyrelease_callback_engine_vector_pointer;
    console_struct.command_callback_map_pointer = &command_callback_map;
    console_struct.universe = my_universe;
    console_struct.font2D_pointer = my_font2D;

    std::cout << "Creating console::Console* my_console ...\n";

    console::Console* my_console = new console::Console(console_struct); // create a console.

    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::cout << "Defining action mode keyrelease callback engines.\n";

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` release: enable enter console.
    callback_system::CallbackEngine* enable_enter_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_enter_console, enable_enter_console_callback_engine, my_console);

    // Callback code for left Control release: release first turbo.
    callback_system::CallbackEngine* release_first_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* release_first_turbo_callback_object = new callback_system::CallbackObject(&ajokki::release_first_turbo, release_first_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, release_first_turbo_callback_object);

    // Callback code for right Control release: release second turbo.
    callback_system::CallbackEngine* release_second_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* release_second_turbo_callback_object = new callback_system::CallbackObject(&ajokki::release_second_turbo, release_second_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, release_second_turbo_callback_object);

    // Callback code for I release: enable_toggle invert mouse.
    callback_system::CallbackEngine* enable_toggle_invert_mouse_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enable_toggle_invert_mouse_callback_object = new callback_system::CallbackObject(&ajokki::enable_toggle_invert_mouse, enable_toggle_invert_mouse_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, enable_toggle_invert_mouse_callback_object);

    // Callback code for F release: enable_toggle flight mode.
    callback_system::CallbackEngine* enable_toggle_flight_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enable_toggle_flight_mode_callback_object = new callback_system::CallbackObject(&ajokki::enable_toggle_flight_mode, enable_toggle_flight_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, enable_toggle_flight_mode_callback_object);

    // Callback code for F1 release: enable toggle help mode.
    callback_system::CallbackEngine* enable_toggle_help_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enable_toggle_help_mode_callback_object = new callback_system::CallbackObject(&ajokki::enable_toggle_help_mode, enable_toggle_help_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, enable_toggle_help_mode_callback_object);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::cout << "Defining action mode keypress callback engines.\n";

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` (tilde key above Tab, usually used for console).
    callback_system::CallbackEngine* enter_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enter_console, enter_console_callback_engine, my_console);

    // Callback code for esc: exit program.
    callback_system::CallbackEngine* exit_program_callback_engine = new callback_system::CallbackEngine();
    new callback_system::CallbackObject(&ajokki::exit_program, exit_program_callback_engine);

    // Callback code for left Control: first turbo.
    callback_system::CallbackEngine* first_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* first_turbo_callback_object = new callback_system::CallbackObject(&ajokki::first_turbo, first_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, first_turbo_callback_object);

    // Callback code for right Control: second turbo.
    callback_system::CallbackEngine* second_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* second_turbo_callback_object = new callback_system::CallbackObject(&ajokki::second_turbo, second_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, second_turbo_callback_object);

    // Callback code for key up: move forward.
    callback_system::CallbackEngine* move_forward_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* move_forward_callback_object = new callback_system::CallbackObject(
            &ajokki::move_forward, move_forward_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, move_forward_callback_object);

    // Callback code for key down: move backward.
    callback_system::CallbackEngine* move_backward_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* move_backward_callback_object = new callback_system::CallbackObject(
            &ajokki::move_backward, move_backward_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, move_backward_callback_object);

    // Callback code for key left: strafe left.
    callback_system::CallbackEngine* strafe_left_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* strafe_left_callback_object = new callback_system::CallbackObject(
            &ajokki::strafe_left, strafe_left_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, strafe_left_callback_object);

    // Callback code for key right: strafe right.
    callback_system::CallbackEngine* strafe_right_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* strafe_right_callback_object = new callback_system::CallbackObject(
            &ajokki::strafe_right, strafe_right_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, strafe_right_callback_object);

    // Callback code for space: ascent.
    callback_system::CallbackEngine* ascent_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* ascent_callback_object = new callback_system::CallbackObject(
            &ajokki::ascent, ascent_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, ascent_callback_object);

    // Callback code for enter: descent.
    callback_system::CallbackEngine* descent_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* descent_callback_object = new callback_system::CallbackObject(
            &ajokki::descent, descent_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, descent_callback_object);

    // Callback code for I: toggle invert mouse.
    callback_system::CallbackEngine* toggle_invert_mouse_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* toggle_invert_mouse_callback_object = new callback_system::CallbackObject(&ajokki::toggle_invert_mouse, toggle_invert_mouse_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, toggle_invert_mouse_callback_object);

    // Callback code for F: toggle flight mode.
    callback_system::CallbackEngine* toggle_flight_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* toggle_flight_mode_callback_object = new callback_system::CallbackObject(&ajokki::toggle_flight_mode, toggle_flight_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, toggle_flight_mode_callback_object);

    // Callback code for F1: toggle help mode.
    callback_system::CallbackEngine* toggle_help_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* toggle_help_mode_callback_object = new callback_system::CallbackObject(&ajokki::toggle_help_mode, toggle_help_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, toggle_help_mode_callback_object);

    // Callback code for D: delete Suzanne species.
    std::string suzanne_species_string = "suzanne_species";
    callback_system::CallbackEngine* delete_suzanne_species_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* delete_suzanne_species_callback_object = new callback_system::CallbackObject(
            &ajokki::delete_entity, delete_suzanne_species_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, delete_suzanne_species_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&suzanne_species_string), false, delete_suzanne_species_callback_object);

    // Callback code for G: switch to grass material.
    std::string grass_material_string = "helsinki_east_downtown_grass_material";
    callback_system::CallbackEngine* switch_to_grass_material_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* switch_to_grass_material_callback_object = new callback_system::CallbackObject(
            &ajokki::switch_to_new_material, switch_to_grass_material_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, switch_to_grass_material_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&suzanne_species_string), false, switch_to_grass_material_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&grass_material_string), false, switch_to_grass_material_callback_object);

    // Callback code for U: switch back to pink_geometric_tiles_material.
    std::string pink_geometric_tiles_material_string = "pink_geometric_tiles_material";
    callback_system::CallbackEngine* switch_to_pink_geometric_tiles_material_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* switch_to_pink_geometric_tiles_material_callback_object = new callback_system::CallbackObject(
            &ajokki::switch_to_new_material, switch_to_pink_geometric_tiles_material_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, switch_to_pink_geometric_tiles_material_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&suzanne_species_string), false, switch_to_pink_geometric_tiles_material_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&pink_geometric_tiles_material_string), false, switch_to_pink_geometric_tiles_material_callback_object);

    // Callback code for T: transform `suzanne2` into terrain.
    std::string helsinki_species_string = "Helsinki_species";
    std::string suzanne2_string = "suzanne2";
    callback_system::CallbackEngine* transform_into_terrain_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* transform_into_terrain_callback_object = new callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_terrain_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, transform_into_terrain_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&suzanne2_string), false, transform_into_terrain_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&helsinki_species_string), false, transform_into_terrain_callback_object);

    // Callback code for A: transform `suzanne2` back into monkey.
    callback_system::CallbackEngine* transform_into_monkey_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* transform_into_monkey_callback_object = new callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_monkey_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, transform_into_monkey_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&suzanne2_string), false, transform_into_monkey_callback_object);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(&suzanne_species_string), false, transform_into_monkey_callback_object);

    /*********************************************************************\
     *  Callback engines for console keyreleases begin here.             *
    \*********************************************************************/

    std::cout << "Defining console keyrelease callback engines.\n";

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` release: enable exit console.
    callback_system::CallbackEngine* enable_exit_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_exit_console, enable_exit_console_callback_engine, my_console);

    // Callback code for left Control release.
    callback_system::CallbackEngine* release_left_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_left_control_in_console, release_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control release.
    callback_system::CallbackEngine* release_right_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_right_control_in_console, release_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt release.
    callback_system::CallbackEngine* release_left_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_left_alt_in_console, release_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt release.
    callback_system::CallbackEngine* release_right_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_right_alt_in_console, release_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift release.
    callback_system::CallbackEngine* release_left_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_left_shift_in_console, release_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift release.
    callback_system::CallbackEngine* release_right_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_right_shift_in_console, release_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up release: enable move to previous input.
    callback_system::CallbackEngine* enable_move_to_previous_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_move_to_previous_input, enable_move_to_previous_input_callback_engine, my_console);

    // Callback code for key down release: enable move to next input.
    callback_system::CallbackEngine* enable_move_to_next_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_move_to_next_input, enable_move_to_next_input_callback_engine, my_console);

    // Callback code for backspace release: enable backspace.
    callback_system::CallbackEngine* enable_backspace_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_backspace, enable_backspace_callback_engine, my_console);

    // Callback code for enter release: enable Enter key.
    callback_system::CallbackEngine* enable_enter_key_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_enter_key, enable_enter_key_callback_engine, my_console);

    // Callback code for C release: enable Control-C.
    callback_system::CallbackEngine* enable_ctrl_c_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_ctrl_c, enable_ctrl_c_callback_engine, my_console);

    // Callback code for W release: enable Control-W.
    callback_system::CallbackEngine* enable_ctrl_w_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_ctrl_w, enable_ctrl_w_callback_engine, my_console);

    // Callback code for PgUp release: enable PgUp.
    callback_system::CallbackEngine* enable_page_up_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_page_up, enable_page_up_callback_engine, my_console);

    // Callback code for PgDn release: enable PgDn.
    callback_system::CallbackEngine* enable_page_down_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_page_down, enable_page_down_callback_engine, my_console);

    // Callback code for Home release: enable Home.
    callback_system::CallbackEngine* enable_home_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_home, enable_home_callback_engine, my_console);

    // Callback code for End release: enable End.
    callback_system::CallbackEngine* enable_end_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_end, enable_end_callback_engine, my_console);

    /*********************************************************************\
     *  Callback engines for console keypresses begin here.              *
    \*********************************************************************/

    std::cout << "Defining console keypress callback engines.\n";

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` (tilde key above Tab, usually used for console).
    callback_system::CallbackEngine* exit_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::exit_console, exit_console_callback_engine, my_console);

    // Callback code for left Control press.
    callback_system::CallbackEngine* press_left_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_left_control_in_console, press_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control press.
    callback_system::CallbackEngine* press_right_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_right_control_in_console, press_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt press.
    callback_system::CallbackEngine* press_left_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_left_alt_in_console, press_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt press.
    callback_system::CallbackEngine* press_right_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_right_alt_in_console, press_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift press.
    callback_system::CallbackEngine* press_left_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_left_shift_in_console, press_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift press.
    callback_system::CallbackEngine* press_right_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_right_shift_in_console, press_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up: move to previous input.
    callback_system::CallbackEngine* move_to_previous_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::move_to_previous_input, move_to_previous_input_callback_engine, my_console);

    // Callback code for key down: move to next input.
    callback_system::CallbackEngine* move_to_next_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::move_to_next_input, move_to_next_input_callback_engine, my_console);

    // Callback code for backspace: delete character left of cursor from current input in console.
    callback_system::CallbackEngine* backspace_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::backspace, backspace_callback_engine, my_console);

    // Callback code for Enter key.
    callback_system::CallbackEngine* enter_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enter_key, enter_callback_engine, my_console);

    // Callback code for C: Control-C.
    callback_system::CallbackEngine* ctrl_c_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::ctrl_c, ctrl_c_callback_engine, my_console);

    // Callback code for W: Control-W.
    callback_system::CallbackEngine* ctrl_w_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::ctrl_w, ctrl_w_callback_engine, my_console);

    // Callback code for PgUp.
    callback_system::CallbackEngine* page_up_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::page_up, page_up_callback_engine, my_console);

    // Callback code for PgDn.
    callback_system::CallbackEngine* page_down_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::page_down, page_down_callback_engine, my_console);

    // Callback code for Home.
    callback_system::CallbackEngine* home_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::home, home_callback_engine, my_console);

    // Callback code for End.
    callback_system::CallbackEngine* end_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::end, end_callback_engine, my_console);

    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, cleanup_callback_object);
    new callback_system::CallbackParameter("font2D_pointer", std::make_shared<datatypes::AnyValue>(my_font2D), false, cleanup_callback_object);
    cleanup_callback_object->set_new_callback(&ajokki::full_cleanup);

    // Keyrelease callbacks for action mode.
    // Key releases are checked in the order of this struct.
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enable_enter_console_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, release_first_turbo_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, release_second_turbo_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_I, enable_toggle_invert_mouse_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F, enable_toggle_flight_mode_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F1, enable_toggle_help_mode_callback_engine });

    // Keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enter_console_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ESCAPE, exit_program_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, first_turbo_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, second_turbo_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_UP, move_forward_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, move_backward_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT, strafe_left_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT, strafe_right_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_SPACE, ascent_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, descent_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_I, toggle_invert_mouse_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F, toggle_flight_mode_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F1, toggle_help_mode_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_D, delete_suzanne_species_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_G, switch_to_grass_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_P, switch_to_pink_geometric_tiles_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_T, transform_into_terrain_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_A, transform_into_monkey_callback_engine });

    // Keyrelease callbacks for console.
    // Key releases are checked in the order of this struct.
    std::vector<KeyAndCallbackStruct>* console_keyrelease_callback_engines = new std::vector<KeyAndCallbackStruct>();
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enable_exit_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, release_left_control_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, release_right_control_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_ALT, release_left_alt_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_ALT, release_right_alt_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_SHIFT, release_left_shift_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_SHIFT, release_right_shift_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_UP, enable_move_to_previous_input_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, enable_move_to_next_input_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_BACKSPACE, enable_backspace_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, enable_enter_key_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_C, enable_ctrl_c_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_W, enable_ctrl_w_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_UP, enable_page_up_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_DOWN, enable_page_down_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_HOME, enable_home_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_END, enable_end_callback_engine });
    my_console->set_my_keyrelease_callback_engine_vector_pointer(console_keyrelease_callback_engines);

    // Keypress callbacks for console.
    // Keypresses are checked in the order of this struct.
    std::vector<KeyAndCallbackStruct>* console_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, exit_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, press_left_control_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, press_right_control_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_ALT, press_left_alt_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_ALT, press_right_alt_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_SHIFT, press_left_shift_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_SHIFT, press_right_shift_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_UP, move_to_previous_input_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, move_to_next_input_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_BACKSPACE, backspace_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, enter_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_C, ctrl_c_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_W, ctrl_w_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_UP, page_up_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_DOWN, page_down_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_HOME, home_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_END, end_callback_engine });
    my_console->set_my_keypress_callback_engine_vector_pointer(console_keypress_callback_engines);

    /*********************************************************************\
     * Callback engines for console commands begin here.                 *
     * These define what commands there are available in the console     *
     * and what each command does.                                       *
     \********************************************************************/

    std::cout << "Defining console command callback engines.\n";

    // Config callbacks.
    command_callback_map["set"] = &config::SettingMaster::set_and_print;
    command_callback_map["get"] = &config::SettingMaster::get_and_print;

    // Object handling callbacks.
    command_callback_map["info"] = &ontology::Universe::info;
    command_callback_map["delete"] = &ontology::Universe::delete_entity;
    command_callback_map["activate"] = &ontology::Universe::activate;

    // Exit program callbacks.
    command_callback_map["bye"] = &ajokki::quit;
    command_callback_map["chau"] = &ajokki::quit;
    command_callback_map["ciao"] = &ajokki::quit;
    command_callback_map["heippa"] = &ajokki::quit;
    command_callback_map["quit"] = &ajokki::quit;
    command_callback_map["sayonara"] = &ajokki::quit;

    // Other callbacks.
    command_callback_map["help"] = &ajokki::help;
    command_callback_map["version"] = &ajokki::version;

    // For speed computation
    double last_time_to_display_FPS = ylikuutio::time::get_time();
    double last_time_for_display_sync = ylikuutio::time::get_time();
    int nbFrames = 0;

    bool ms_frame_text_ready = false;

    bool is_exit_requested = false;

    // Measure speed
    double last_time_before_reading_keyboard = NAN;
    double current_time_before_reading_keyboard = NAN;

    if (!audio_master.load_and_play(music_filename))
    {
        std::cout << "Music file " << music_filename << " could not be loaded!\n";
    }

    while (!is_exit_requested)
    {
        double current_time_in_main_loop = ylikuutio::time::get_time();

        if (current_time_in_main_loop - last_time_for_display_sync >= (1.0f / my_universe->get_max_FPS()))
        {
            last_time_for_display_sync = ylikuutio::time::get_time();

            char ms_frame_text[256];
            nbFrames++;

            while (current_time_in_main_loop - last_time_to_display_FPS >= 1.0f)
            {
                // If last `std::printf()` was more than 1 sec ago,
                // `std::printf` and reset.
                std::snprintf(ms_frame_text, sizeof(ms_frame_text), "%.02f ms/frame; %.02f Hz", 1000.0f / ((double) nbFrames), 1000.0f / (1000.0f / ((double) nbFrames)));
                ms_frame_text_ready = true;
                nbFrames = 0;
                last_time_to_display_FPS += 1.0;
            }

            // Clear the screen.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwPollEvents();

            my_universe->compute_delta_time();

            // Get mouse position
            double xpos, ypos;
            glfwGetCursorPos(my_universe->get_window(), &xpos, &ypos);

            // Reset mouse position for next frame
            glfwSetCursorPos(my_universe->get_window(), my_universe->get_window_width() / 2, my_universe->get_window_height() / 2);

            if (my_universe->has_mouse_ever_moved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
            {
                my_universe->has_mouse_ever_moved = true;

                // Compute new orientation
                my_universe->horizontal_angle += my_universe->mouse_speed * GLfloat(my_universe->get_window_width() / 2 - xpos);
                my_universe->horizontal_angle = remainder(my_universe->horizontal_angle, (2.0f * PI));

                if (my_universe->is_invert_mouse_in_use)
                {
                    // invert mouse.
                    my_universe->vertical_angle -= my_universe->mouse_speed * GLfloat(my_universe->get_window_height() / 2 - ypos);
                }
                else
                {
                    // don't invert mouse.
                    my_universe->vertical_angle += my_universe->mouse_speed * GLfloat(my_universe->get_window_height() / 2 - ypos);
                }
                my_universe->vertical_angle = remainder(my_universe->vertical_angle, (2.0f * PI));
            }

            // Direction : Spherical coordinates to Cartesian coordinates conversion
            my_universe->direction = glm::vec3(
                    cos(my_universe->vertical_angle) * sin(my_universe->horizontal_angle),
                    sin(my_universe->vertical_angle),
                    cos(my_universe->vertical_angle) * cos(my_universe->horizontal_angle)
                    );

            // Right vector
            my_universe->right = glm::vec3(
                    sin(my_universe->horizontal_angle - PI/2.0f),
                    0,
                    cos(my_universe->horizontal_angle - PI/2.0f)
                    );

            // Up vector
            my_universe->up = glm::cross(my_universe->right, my_universe->direction);

            // Check for key releases and call corresponding callbacks.
            for (uint32_t i = 0; i < (*current_keyrelease_callback_engine_vector_pointer)->size(); i++)
            {
                bool is_released = false;

                if (input_method_in_use == ylikuutio::input::KEYBOARD)
                {
                    if (glfwGetKey(my_universe->get_window(), (*current_keyrelease_callback_engine_vector_pointer)->at(i).keycode) == GLFW_RELEASE)
                    {
                        is_released = true;
                    }
                }
                else if (input_method_in_use == ylikuutio::input::INPUT_FILE)
                {
                    // TODO: implement optionally loading keyreleases from a file (do not execute `glfwGetKey` in that case).
                    if (false)
                    {
                        is_released = true;
                    }
                }
                else
                {
                    std::cerr << "Unsupported input method: " << input_method_in_use << "\n";
                }

                if (is_released)
                {
                    callback_system::CallbackEngine* callback_engine = (*current_keyrelease_callback_engine_vector_pointer)->at(i).callback_engine;
                    std::shared_ptr<datatypes::AnyValue> any_value = callback_engine->execute();
                }
            }

            // Check for keypresses and call corresponding callbacks.
            for (uint32_t i = 0; i < (*current_keypress_callback_engine_vector_pointer)->size(); i++)
            {
                bool is_pressed = false;

                if (input_method_in_use == ylikuutio::input::KEYBOARD)
                {
                    if (glfwGetKey(my_universe->get_window(), (*current_keypress_callback_engine_vector_pointer)->at(i).keycode) == GLFW_PRESS)
                    {
                        is_pressed = true;
                    }
                }
                else if (input_method_in_use == ylikuutio::input::INPUT_FILE)
                {
                    // TODO: implement optionally loading keyreleases from a file (do not execute `glfwGetKey` in that case).
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
                    callback_system::CallbackEngine* callback_engine = (*current_keypress_callback_engine_vector_pointer)->at(i).callback_engine;
                    std::shared_ptr<datatypes::AnyValue> any_value = callback_engine->execute();

                    if (any_value != nullptr &&
                            any_value->type == datatypes::UINT32_T)
                    {
                        if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                        {
                            // Read all keys, but don't call any more callbacks,
                            // as we are entering the console now. Reading all keys
                            // is needed to flush the input. Not calling any more
                            // callbacks is needed to make callback-related code
                            // simpler, we don't need to worry about consecutive
                            // changes in program mode or in
                            // `current_callback_engine_vector_pointer`. That allows
                            // callbacks to change eg.
                            // `current_callback_engine_vector_pointer` given that
                            // they signal it, eg. with `ENTER_CONSOLE_MAGIC_NUMBER`
                            // (as in this loop).

                            for (uint32_t key_code = 0; key_code <= GLFW_KEY_LAST; key_code++)
                            {
                                glfwGetKey(my_universe->get_window(), key_code);
                            }

                            // Do not display help screen when in console.
                            my_universe->can_display_help_screen = false;
                            break;
                        }
                        if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                        {
                            // Read all keys, but don't call any more callbacks,
                            // we are exiting the console now. The reasons for doing
                            // this are the same as when entering the console.
                            // See the above comment related to entering the console.

                            for (uint32_t key_code = 0; key_code <= GLFW_KEY_LAST; key_code++)
                            {
                                glfwGetKey(my_universe->get_window(), key_code);
                            }

                            // Enable display help screen when not in console.
                            my_universe->can_display_help_screen = true;
                            break;
                        }
                        if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                        {
                            // Read all keys, but don't call any more callbacks,
                            // we are exiting the program now. The reasons for doing
                            // this are the same as when entering the console.
                            // See the above comment related to entering the console.

                            for (uint32_t key_code = 0; key_code <= GLFW_KEY_LAST; key_code++)
                            {
                                glfwGetKey(my_universe->get_window(), key_code);
                            }

                            is_exit_requested = true;
                            break;
                        }
                    }
                }
            }

            // Render the world.
            my_universe->render();

            // Draw the console (including current input).
            my_console->draw_console();

            PrintingStruct printing_struct;
            printing_struct.screen_width = static_cast<GLuint>(my_universe->get_window_width());
            printing_struct.screen_height = static_cast<GLuint>(my_universe->get_window_height());
            printing_struct.text_size = my_universe->get_text_size();
            printing_struct.font_size = my_universe->get_font_size();
            printing_struct.char_font_texture_file_format = "bmp";

            if (my_universe != nullptr && my_universe->cartesian_coordinates != nullptr)
            {
                char angles_and_coordinates_text[256];
                std::snprintf(
                        angles_and_coordinates_text,
                        sizeof(angles_and_coordinates_text),
                        "%.2f,%.2f rad; %.2f,%.2f deg\\n(%.2f,%.2f,%.2f)",
                        my_universe->horizontal_angle,
                        my_universe->vertical_angle,
                        RADIANS_TO_DEGREES(my_universe->horizontal_angle),
                        RADIANS_TO_DEGREES(my_universe->vertical_angle),
                        my_universe->cartesian_coordinates->x,
                        my_universe->cartesian_coordinates->y,
                        my_universe->cartesian_coordinates->z);

                char time_text[256];
                std::snprintf(time_text, sizeof(time_text), "%.2f sec", ylikuutio::time::get_time());

                char null_text[] = "";
                char on_text[] = "on";
                char off_text[] = "off";
                char in_use_text[] = " (in use)";

                char help_text_char[1024];
                std::snprintf(
                        help_text_char,
                        sizeof(help_text_char),
                        "Ajokki v. 0.0.1\\n"
                        "\\n"
                        "arrow keys\\n"
                        "space jump\\n"
                        "enter duck\\n"
                        "F1 help mode\\n"
                        "`  enter console\\n"
                        "I  invert mouse (%s)\\n"
                        "F  flight mode (%s)\\n"
                        "Ctrl      turbo\\n"
                        "Ctrl+Ctrl extra turbo\\n"
                        "for debugging:\\n"
                        "G  grass texture\\n"
                        "U  uvmap texture\\n"
                        "T  terrain species\\n"
                        "A  suzanne species\\n",
                        (my_universe->is_invert_mouse_in_use ? on_text : off_text),
                        (my_universe->is_flight_mode_in_use ? on_text : off_text));

                char spherical_coordinates_text[256];

                if (my_universe != nullptr && my_universe->testing_spherical_terrain_in_use)
                {
                    std::snprintf(spherical_coordinates_text, sizeof(spherical_coordinates_text), "rho:%.2f theta:%.2f phi:%.2f", my_universe->spherical_coordinates->rho, my_universe->spherical_coordinates->theta, my_universe->spherical_coordinates->phi);
                }

                // print cartesian coordinates on bottom left corner.
                printing_struct.x = 0;
                printing_struct.y = 0;
                printing_struct.text_char = angles_and_coordinates_text;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "bottom";
                my_font2D->printText2D(printing_struct);

                if (my_universe != nullptr && my_universe->in_help_mode && my_universe->can_display_help_screen)
                {
                    // print help text.
                    printing_struct.x = 0;
                    printing_struct.y = my_universe->get_window_height() - (3 * my_universe->get_text_size());
                    printing_struct.text_char = help_text_char;
                    printing_struct.horizontal_alignment = "left";
                    printing_struct.vertical_alignment = "top";
                    my_font2D->printText2D(printing_struct);
                }

                if (my_universe != nullptr && my_universe->testing_spherical_terrain_in_use)
                {
                    // print spherical coordinates on bottom left corner.
                    printing_struct.x = 0;
                    printing_struct.y += 2 * my_universe->get_text_size();
                    printing_struct.text_char = spherical_coordinates_text;
                    printing_struct.horizontal_alignment = "left";
                    printing_struct.vertical_alignment = "bottom";
                    my_font2D->printText2D(printing_struct);
                }

                // print time data on top left corner.
                printing_struct.x = 0;
                printing_struct.y = static_cast<GLuint>(my_universe->get_window_height());
                printing_struct.text_char = time_text;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "top";
                my_font2D->printText2D(printing_struct);
            }

            if (ms_frame_text_ready)
            {
                // print frame rate data on top right corner.
                printing_struct.x = my_universe->get_window_width();
                printing_struct.y = my_universe->get_window_height();
                printing_struct.text_char = ms_frame_text;
                printing_struct.horizontal_alignment = "right";
                printing_struct.vertical_alignment = "top";
                my_font2D->printText2D(printing_struct);
            }

            // Swap buffers.
            glfwSwapBuffers(my_universe->get_window());

            my_universe->finalize_delta_time_loop();
        }

        // Check if the window was closed.
        if (glfwWindowShouldClose(my_universe->get_window()) != 0)
        {
            is_exit_requested = true;
        }
    }

    // do cleanup.
    cleanup_callback_engine->execute();

    // Delete all keyrelease callback engines.
    for (uint32_t i = 0; i < action_mode_keyrelease_callback_engines->size(); i++)
    {
        delete action_mode_keyrelease_callback_engines->at(i).callback_engine;
    }
    delete action_mode_keyrelease_callback_engines;

    // Delete all keypress callback engines.
    for (uint32_t i = 0; i < action_mode_keypress_callback_engines->size(); i++)
    {
        delete action_mode_keypress_callback_engines->at(i).callback_engine;
    }
    delete action_mode_keypress_callback_engines;

    delete cleanup_callback_engine;
    delete my_console;

    return 0;
}
