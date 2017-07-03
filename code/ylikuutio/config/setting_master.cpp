#include "setting_master.hpp"
#include "setting.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace config
{
    SettingMaster::SettingMaster(ontology::Universe* universe_pointer)
    {
        // costructor.
        this->parent_pointer = universe_pointer;

        // bind to parent.
        // there can be only 1 `SettingMaster`.
        this->parent_pointer->setting_master_pointer = this;
    }

    SettingMaster::~SettingMaster()
    {
        // destructor.
    }

    bool SettingMaster::is_setting(const std::string setting_name)
    {
        return (this->setting_pointer_map.count(setting_name) == 1);
    }

    std::string SettingMaster::help()
    {
        std::string help_string = "TODO: create general helptext";
        return help_string;
    }

    std::string SettingMaster::help(const std::string setting_name)
    {
        if (this->is_setting(setting_name))
        {
            config::Setting* setting = this->setting_pointer_map[setting_name];

            if (setting != nullptr)
            {
                return setting->help();
            }
        }
        return this->help();
    }

    bool SettingMaster::set(std::string& setting_name, datatypes::AnyValue* setting_new_any_value)
    {
        if (!this->is_setting(setting_name))
        {
            return false;
        }

        // OK, this is a valid variable name.
        // Set the variable value and activate it by
        // calling the corresponding activate callback.
        config::Setting* setting = this->setting_pointer_map[setting_name];

        // create empty `AnyValue` (there is no suitable constructor yet).
        setting_new_any_value->type = setting->setting_value->type;

        // Delete the old `datatypes::AnyValue`.
        delete setting->setting_value;

        setting->setting_value = setting_new_any_value;
        setting->activate_callback(this->parent_pointer, this);
        return true;
    }

    config::Setting* SettingMaster::get(std::string& setting_name)
    {
        return this->setting_pointer_map[setting_name];
    }

    datatypes::AnyValue* SettingMaster::get_value(std::string& setting_name)
    {
        config::Setting* setting = this->get(setting_name);

        if (setting == nullptr)
        {
            return nullptr;
        }

        return setting->setting_value;
    }

    // public callbacks.

    datatypes::AnyValue* SettingMaster::set_and_print(
            console::Console* console,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        // Usage:
        // to get variable names: set
        // to get valid values:   set <variable>
        // to set variable:       set <variable> value[s]

        config::SettingMaster* setting_master = universe->setting_master_pointer;

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string setting_name = command_parameters.at(0);

            // One (1) command parameter.
            // Check the validity of the variable name.
            if (setting_master->is_setting(setting_name))
            {
                config::Setting* setting = setting_master->get(setting_name);

                if (setting != nullptr)
                {
                    // Print variable value.
                    console->print_text(setting->setting_value->get_string());
                }
            }
            else
            {
                // Invalid variable name.
                console->print_text("invalid variable name");
                console->print_text(setting_master->help());
            }
        }
        else
        {
            std::string setting_name = command_parameters.at(0);

            // At least 2 variables.
            // Check the validity of the variable name.
            if (setting_master->is_setting(setting_name))
            {
                // OK, this is a valid variable name.
                // Set the variable value and activate it by
                // calling the corresponding activate callback.
                config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                // create empty `AnyValue` (there is no suitable constructor yet).
                datatypes::AnyValue* setting_any_value = new datatypes::AnyValue();
                setting_any_value->type = setting->setting_value->type;

                // set a new value.
                bool success = setting_any_value->set_value(command_parameters.at(1));

                if (success)
                {
                    delete setting->setting_value; // delete the old value.
                    setting->setting_value = setting_any_value;
                    setting->activate_callback(universe, setting_master);
                }
            }
            else
            {
                console->print_text(setting_master->help());
            }
        }

        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::get_and_print(
            console::Console* console,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        // Usage:
        // to get variable names: get
        // to get variable value: get <variable>
        config::SettingMaster* setting_master = universe->setting_master_pointer;

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string setting_name = command_parameters.at(0);

            // One (1) command parameter.
            // Print valid values of the given variable.
            if (setting_master->is_setting(setting_name))
            {
                config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                if (setting != nullptr)
                {
                    // Print variable value.
                    console->print_text(setting->setting_value->get_string());
                }
            }
            else
            {
                // Invalid variable name.
                console->print_text("invalid variable name");
                console->print_text(setting_master->help());
            }
        }
        else
        {
            // More than 1 command parameter.
            // Print variable names.
            console->print_text(setting_master->help());
        }

        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_world_radius(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer->setting_pointer_map.count("world_radius") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* world_radius_any_value = setting_master_pointer->setting_pointer_map["world_radius"]->setting_value;

        if (world_radius_any_value == nullptr || world_radius_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->world_radius = world_radius_any_value->float_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_background_color(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("red") != 1 ||
                setting_master_pointer->setting_pointer_map.count("green") != 1 ||
                setting_master_pointer->setting_pointer_map.count("blue") != 1 ||
                setting_master_pointer->setting_pointer_map.count("alpha") != 1)
        {
            return nullptr;
        }

        // red.
        datatypes::AnyValue* red_any_value = setting_master_pointer->setting_pointer_map["red"]->setting_value;

        if (red_any_value == nullptr || red_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf red = static_cast<GLclampf>(red_any_value->float_value);

        // green.
        datatypes::AnyValue* green_any_value = setting_master_pointer->setting_pointer_map["green"]->setting_value;

        if (green_any_value == nullptr || green_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf green = static_cast<GLclampf>(green_any_value->float_value);

        // blue.
        datatypes::AnyValue* blue_any_value = setting_master_pointer->setting_pointer_map["blue"]->setting_value;

        if (blue_any_value == nullptr || blue_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf blue = static_cast<GLclampf>(blue_any_value->float_value);

        // alpha.
        datatypes::AnyValue* alpha_any_value = setting_master_pointer->setting_pointer_map["alpha"]->setting_value;

        if (alpha_any_value == nullptr || alpha_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf alpha = static_cast<GLclampf>(alpha_any_value->float_value);

        glClearColor(red, green, blue, alpha);
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_horizontal_angle(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("horizontal_angle") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* horizontal_angle_any_value = setting_master_pointer->setting_pointer_map["horizontal_angle"]->setting_value;

        if (horizontal_angle_any_value == nullptr || horizontal_angle_any_value->type != datatypes::DOUBLE)
        {
            return nullptr;
        }

        universe->horizontal_angle = horizontal_angle_any_value->double_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_vertical_angle(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("vertical_angle") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* vertical_angle_any_value = setting_master_pointer->setting_pointer_map["vertical_angle"]->setting_value;

        if (vertical_angle_any_value == nullptr || vertical_angle_any_value->type != datatypes::DOUBLE)
        {
            return nullptr;
        }

        universe->vertical_angle = vertical_angle_any_value->double_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_speed(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("speed") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* speed_any_value = setting_master_pointer->setting_pointer_map["speed"]->setting_value;

        if (speed_any_value == nullptr || speed_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->speed = speed_any_value->double_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_turbo_factor(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("turbo_factor") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* turbo_factor_any_value = setting_master_pointer->setting_pointer_map["turbo_factor"]->setting_value;

        if (turbo_factor_any_value == nullptr || turbo_factor_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->turbo_factor = turbo_factor_any_value->double_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_twin_turbo_factor(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("twin_turbo_factor") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* twin_turbo_factor_any_value = setting_master_pointer->setting_pointer_map["twin_turbo_factor"]->setting_value;

        if (twin_turbo_factor_any_value == nullptr || twin_turbo_factor_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->twin_turbo_factor = twin_turbo_factor_any_value->double_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_mouse_speed(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("mouse_speed") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* mouse_speed_any_value = setting_master_pointer->setting_pointer_map["mouse_speed"]->setting_value;

        if (mouse_speed_any_value == nullptr || mouse_speed_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->mouse_speed = mouse_speed_any_value->double_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_is_flight_mode_in_use(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("is_flight_mode_in_use") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* is_flight_mode_in_use_any_value = setting_master_pointer->setting_pointer_map["x"]->setting_value;

        if (is_flight_mode_in_use_any_value == nullptr || is_flight_mode_in_use_any_value->type != datatypes::BOOL)
        {
            return nullptr;
        }

        universe->is_flight_mode_in_use = is_flight_mode_in_use_any_value->bool_value;
    }

    datatypes::AnyValue* SettingMaster::activate_testing_spherical_world_in_use(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("testing_spherical_world_in_use") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* testing_spherical_world_in_use_any_value = setting_master_pointer->setting_pointer_map["x"]->setting_value;

        if (testing_spherical_world_in_use_any_value == nullptr || testing_spherical_world_in_use_any_value->type != datatypes::BOOL)
        {
            return nullptr;
        }

        universe->testing_spherical_world_in_use = testing_spherical_world_in_use_any_value->bool_value;
    }
}
