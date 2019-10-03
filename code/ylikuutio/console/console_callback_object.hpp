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

#ifndef __CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED
#define __CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED

#include "code/ylikuutio/ontology/console.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackParameter;
    }

    namespace common
    {
        class AnyValue;
    }

    namespace console
    {
        class ConsoleCallbackObject : public yli::callback_system::CallbackObject
        {
            public:
                // constructor.
                ConsoleCallbackObject(InputParametersToAnyValueCallbackWithConsole console_callback,
                        yli::callback_system::CallbackEngine* parent, yli::ontology::Console* console_pointer)
                    : yli::callback_system::CallbackObject(nullptr, parent)
                {
                    // constructor.
                    this->callback = nullptr;
                    this->console_callback = console_callback;
                    this->console_pointer = console_pointer;
                }

                // destructor.
                ~ConsoleCallbackObject();

            private:
                // execute this callback.
                std::shared_ptr<yli::common::AnyValue> execute();

                InputParametersToAnyValueCallbackWithConsole console_callback;
                yli::ontology::Console* console_pointer;
        };
    }
}

#endif
