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

#include "wireframe_snippets.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli::snippets
{
    void set_wireframe(yli::config::SettingMaster* setting_master, const bool use_wireframe)
    {
        yli::config::SettingStruct wireframe_setting_struct(std::make_shared<yli::data::AnyValue>(use_wireframe));
        wireframe_setting_struct.name = "wireframe";
        wireframe_setting_struct.activate_callback = &yli::config::Setting::activate_wireframe;
        wireframe_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        setting_master->create_setting(wireframe_setting_struct);
    }
}
