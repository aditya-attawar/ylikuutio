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

#ifndef __CALLBACK_ENGINE_HPP_INCLUDED
#define __CALLBACK_ENGINE_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"
#include "input_parameters_to_any_value_callback.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <vector>        // std::vector

// callback typedefs in alphabetical order.
typedef void (*VoidToVoidCallback)(void);
typedef void (*AnyValueToVoidCallback)(yli::common::AnyValue);
typedef yli::common::AnyValue (*VoidToAnyValueCallback)(void);
typedef yli::common::AnyValue (*AnyValueToAnyValueCallback)(yli::common::AnyValue);

namespace yli
{
    namespace callback_system
    {
        class CallbackObject;

        class CallbackEngine
        {
            // `CallbackEngine` is an object that contains some callbacks and hashmaps that are used for input and output parameters.
            // `CallbackEngine` provides a way to create callback chains.
            //
            // Hierarchy of callbacks:
            //
            //     CallbackEngine
            //           ^
            //     CallbackObject
            //           ^
            //   CallbackParameter
            //
            // How to use.
            // 1. Create a new `CallbackEngine`. No callbacks have been
            //    defined yet. Calling `CallbackEngine.execute()` at this
            //    point will simply go through an empty vector and
            //    practically won't do anything interesting.
            // 2. Create a new `CallbackObject`, give pointer to the
            //    recently created `CallbackEngine` as input parameter.
            // 3. If the callback has parameter[s], create a new
            //    `CallbackParameter` for each parameter, give `CallbackObject`
            //    as input parameter for the `CallbackParameter` constructor.

            public:
                void bind_CallbackObject(yli::callback_system::CallbackObject* const callback_object);

                // constructor.
                CallbackEngine();

                // destructor.
                ~CallbackEngine();

                yli::callback_system::CallbackObject* create_CallbackObject();
                yli::callback_system::CallbackObject* create_CallbackObject(const InputParametersToAnyValueCallback callback);

                // execute all callbacks.
                std::shared_ptr<yli::common::AnyValue> execute();

                std::size_t get_n_of_return_values() const;
                std::shared_ptr<yli::common::AnyValue> get_nth_return_value(std::size_t n) const;
                std::shared_ptr<yli::common::AnyValue> get_previous_return_value() const;

                friend class CallbackObject;

            private:
                // this method sets a callback object pointer.
                void set_callback_object_pointer(const std::size_t childID, yli::callback_system::CallbackObject* const child_pointer);

                std::vector<yli::callback_system::CallbackObject*> callback_object_pointer_vector;
                std::queue<std::size_t> free_callback_objectID_queue;
                std::size_t number_of_callback_objects;

                std::vector<std::shared_ptr<yli::common::AnyValue>> return_values;
        };
    }
}

#endif
