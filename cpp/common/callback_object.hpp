#ifndef __CALLBACK_OBJECT_HPP_INCLUDED
#define __CALLBACK_OBJECT_HPP_INCLUDED

#include "any_value.hpp"
#include "callback_engine.hpp"
#include "callback_parameter.hpp"
#include "globals.hpp"

// Include standard headers
#include <cmath>         // NAN
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace callback_system
{
    class CallbackObject
    {
        // CallbackObject is an object that contains a single callback.

        public:
            // constructor.
            CallbackObject(callback_system::CallbackEngine* callback_engine_pointer);

            // constructor.
            CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* callback_engine_pointer);

            // add reference to an input variable.
            // this does not store the value to an appropriate hashmap.
            // storing the value must be done before or after this call.
            // each type has its own namespace!
            // void add_input_parameter(std::string name, AnyValue any_value, bool is_reference);

            // execute this callback.
            AnyValue execute();

            callback_system::CallbackEngine* callback_engine_pointer;

            std::string output_type;
            std::string output_variable_name;
            std::vector<callback_system::CallbackParameter*> callback_parameter_pointer_vector;

            InputParametersToAnyValueCallback callback;
    };
}

#endif
