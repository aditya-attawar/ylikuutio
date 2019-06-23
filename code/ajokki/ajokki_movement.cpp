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

#include "ajokki_movement.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_movement(yli::config::SettingMaster* const setting_master)
    {
        // Variables related to voluntary movement.
        float speed = 0.5f; // 0.5 units/second
        std::shared_ptr<yli::common::AnyValue> any_value_speed = std::make_shared<yli::common::AnyValue>(speed);
        yli::config::SettingStruct speed_setting_struct(any_value_speed);
        speed_setting_struct.name = "speed";
        speed_setting_struct.setting_master = setting_master;
        speed_setting_struct.activate_callback = &yli::config::SettingMaster::activate_speed;
        speed_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(speed_setting_struct);

        float turbo_factor = 5.0f;
        // float turbo_factor = 100.0f;
        std::shared_ptr<yli::common::AnyValue> any_value_turbo_factor = std::make_shared<yli::common::AnyValue>(turbo_factor);
        yli::config::SettingStruct turbo_factor_setting_struct(any_value_turbo_factor);
        turbo_factor_setting_struct.name = "turbo_factor";
        turbo_factor_setting_struct.setting_master = setting_master;
        turbo_factor_setting_struct.activate_callback = &yli::config::SettingMaster::activate_turbo_factor;
        turbo_factor_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(turbo_factor_setting_struct);

        float twin_turbo_factor = 100.0f;
        // float twin_turbo_factor = 50000.0f;
        std::shared_ptr<yli::common::AnyValue> any_value_twin_turbo_factor = std::make_shared<yli::common::AnyValue>(twin_turbo_factor);
        yli::config::SettingStruct twin_turbo_factor_setting_struct(any_value_twin_turbo_factor);
        twin_turbo_factor_setting_struct.name = "twin_turbo_factor";
        twin_turbo_factor_setting_struct.setting_master = setting_master;
        twin_turbo_factor_setting_struct.activate_callback = &yli::config::SettingMaster::activate_twin_turbo_factor;
        twin_turbo_factor_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(twin_turbo_factor_setting_struct);

        float mouse_speed = 0.005f;
        std::shared_ptr<yli::common::AnyValue> any_value_mouse_speed = std::make_shared<yli::common::AnyValue>(mouse_speed);
        yli::config::SettingStruct mouse_speed_setting_struct(any_value_mouse_speed);
        mouse_speed_setting_struct.name = "mouse_speed";
        mouse_speed_setting_struct.setting_master = setting_master;
        mouse_speed_setting_struct.activate_callback = &yli::config::SettingMaster::activate_mouse_speed;
        mouse_speed_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(mouse_speed_setting_struct);
    }
}
