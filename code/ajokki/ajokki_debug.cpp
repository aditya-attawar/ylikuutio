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

#include "ajokki_debug.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_debug_variables(yli::config::SettingMaster* setting_master)
    {
        bool is_flight_mode_in_use = true;
        std::shared_ptr<yli::datatypes::AnyValue> any_value_is_flight_mode_in_use = std::make_shared<yli::datatypes::AnyValue>(is_flight_mode_in_use);
        yli::config::SettingStruct is_flight_mode_in_use_setting_struct(any_value_is_flight_mode_in_use);
        is_flight_mode_in_use_setting_struct.name = "is_flight_mode_in_use";
        is_flight_mode_in_use_setting_struct.setting_master = setting_master;
        is_flight_mode_in_use_setting_struct.activate_callback = &yli::config::SettingMaster::activate_is_flight_mode_in_use;
        is_flight_mode_in_use_setting_struct.read_callback = &yli::config::SettingMaster::read_is_flight_mode_in_use;
        is_flight_mode_in_use_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(is_flight_mode_in_use_setting_struct);
    }
}
