#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli
{
    namespace callback_system
    {
        void CallbackParameter::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::callback_system::CallbackObject* const callback_object = this->parent;

            if (callback_object == nullptr)
            {
                std::cerr << "ERROR: `CallbackParameter::bind_to_parent`: `callback_object` is `nullptr`!\n";
                return;
            }

            // note: `CallbackObject::bind_callback_parameter` also stores named variables in its `anyvalue_hashmap`.
            callback_object->bind_callback_parameter(this);
        }

        CallbackParameter::CallbackParameter(const std::string& name, std::shared_ptr<yli::datatypes::AnyValue> any_value, const bool is_reference, yli::callback_system::CallbackObject* const parent)
        {
            // constructor.
            this->name = name;
            this->any_value = any_value;
            this->is_reference = is_reference;
            this->parent = parent;

            // get childID from the CallbackObject and set pointer to this CallbackParameter.
            this->bind_to_parent();
        }

        CallbackParameter::~CallbackParameter()
        {
            // destructor.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.

            std::cout << "Callback parameter with childID " << this->childID << " will be destroyed.\n";

            yli::callback_system::CallbackObject* const callback_object = this->parent;

            if (callback_object == nullptr)
            {
                std::cerr << "ERROR: `CallbackParameter::~CallbackParameter`: `callback_object` is `nullptr`!\n";
                return;
            }

            // set pointer to this `CallbackParameter` to `nullptr`.
            callback_object->set_callback_parameter_pointer(this->childID, nullptr);
        }

        std::shared_ptr<yli::datatypes::AnyValue> CallbackParameter::get_any_value() const
        {
            return std::make_shared<yli::datatypes::AnyValue>(*this->any_value);
        }
    }
}
