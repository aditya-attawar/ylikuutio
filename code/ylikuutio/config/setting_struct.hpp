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

#ifndef __SETTING_STRUCT_HPP_INCLUDED
#define __SETTING_STRUCT_HPP_INCLUDED

#include "activate_callback.hpp"
#include "read_callback.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli
{
    namespace common
    {
        class AnyValue;
    }

    namespace config
    {
        class SettingMaster;

        struct SettingStruct
        {
            SettingStruct(std::shared_ptr<yli::common::AnyValue> initial_value)
                : initial_value(initial_value),
                setting_master(nullptr),
                activate_callback(nullptr),
                read_callback(nullptr),
                should_ylikuutio_call_activate_callback_now(true)
            {
                // constructor.
            }
            std::string name;
            std::shared_ptr<yli::common::AnyValue> initial_value;
            yli::config::SettingMaster* setting_master;
            ActivateCallback activate_callback;
            ReadCallback read_callback;
            bool should_ylikuutio_call_activate_callback_now;
        };
    }
}

#endif
