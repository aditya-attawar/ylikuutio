#include "ajokki_debug.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_debug_variables(config::SettingMaster* setting_master)
    {
        bool is_flight_mode_in_use = true;
        std::shared_ptr<datatypes::AnyValue> any_value_is_flight_mode_in_use = std::make_shared<datatypes::AnyValue>(is_flight_mode_in_use);
        SettingStruct is_flight_mode_in_use_setting_struct(any_value_is_flight_mode_in_use);
        is_flight_mode_in_use_setting_struct.name = "is_flight_mode_in_use";
        is_flight_mode_in_use_setting_struct.setting_master_pointer = setting_master;
        is_flight_mode_in_use_setting_struct.activate_callback = &config::SettingMaster::activate_is_flight_mode_in_use;
        is_flight_mode_in_use_setting_struct.read_callback = &config::SettingMaster::read_is_flight_mode_in_use;
        is_flight_mode_in_use_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(is_flight_mode_in_use_setting_struct);

        bool testing_spherical_world_in_use = false;
        std::shared_ptr<datatypes::AnyValue> any_value_testing_spherical_world_in_use = std::make_shared<datatypes::AnyValue>(testing_spherical_world_in_use);
        SettingStruct testing_spherical_world_in_use_setting_struct(any_value_testing_spherical_world_in_use);
        testing_spherical_world_in_use_setting_struct.name = "testing_spherical_world_in_use";
        testing_spherical_world_in_use_setting_struct.setting_master_pointer = setting_master;
        testing_spherical_world_in_use_setting_struct.activate_callback =  &config::SettingMaster::activate_testing_spherical_world_in_use;
        testing_spherical_world_in_use_setting_struct.read_callback = &config::SettingMaster::read_testing_spherical_world_in_use;
        testing_spherical_world_in_use_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(testing_spherical_world_in_use_setting_struct);
    }
}
