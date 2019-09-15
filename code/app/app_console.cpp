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

#include "app_console.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace app
{
    void set_console(
            yli::config::SettingMaster* const setting_master,
            const uint32_t console_top_y,
            const uint32_t console_bottom_y,
            const uint32_t console_left_x,
            const uint32_t console_right_x)
    {
        // Variables related to console.
        yli::config::SettingStruct console_top_y_setting_struct(std::make_shared<yli::common::AnyValue>(console_top_y));
        console_top_y_setting_struct.name = "console_top_y";
        console_top_y_setting_struct.setting_master = setting_master;
        console_top_y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_top_y;
        console_top_y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_top_y_setting_struct);

        yli::config::SettingStruct console_bottom_y_setting_struct(std::make_shared<yli::common::AnyValue>(console_bottom_y));
        console_bottom_y_setting_struct.name = "console_bottom_y";
        console_bottom_y_setting_struct.setting_master = setting_master;
        console_bottom_y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_bottom_y;
        console_bottom_y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_bottom_y_setting_struct);

        yli::config::SettingStruct console_left_x_setting_struct(std::make_shared<yli::common::AnyValue>(console_left_x));
        console_left_x_setting_struct.name = "console_left_x";
        console_left_x_setting_struct.setting_master = setting_master;
        console_left_x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_left_x;
        console_left_x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_left_x_setting_struct);

        yli::config::SettingStruct console_right_x_setting_struct(std::make_shared<yli::common::AnyValue>(console_right_x));
        console_right_x_setting_struct.name = "console_right_x";
        console_right_x_setting_struct.setting_master = setting_master;
        console_right_x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_right_x;
        console_right_x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_right_x_setting_struct);
    }
}