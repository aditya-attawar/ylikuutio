#ifndef __INPUT_PARAMETERS_TO_ANY_VALUE_CALLBACK_HPP_INCLUDED
#define __INPUT_PARAMETERS_TO_ANY_VALUE_CALLBACK_HPP_INCLUDED

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }

    namespace datatypes
    {
        class AnyValue;
    }
}

typedef std::shared_ptr<yli::datatypes::AnyValue> (*InputParametersToAnyValueCallback) (
        yli::callback_system::CallbackEngine*,
        yli::callback_system::CallbackObject*,
        std::vector<yli::callback_system::CallbackParameter*>&);

#endif
