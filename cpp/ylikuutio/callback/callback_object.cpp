#include "callback_object.hpp"
#include "callback_parameter.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/common/globals.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace callback_system
{
    void CallbackObject::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<callback_system::CallbackObject*>(this, this->parent_pointer->callback_object_pointer_vector, this->parent_pointer->free_callback_objectID_queue);
    }

    CallbackObject::CallbackObject(callback_system::CallbackEngine* parent_pointer)
    {
        // constructor.
        this->parent_pointer = parent_pointer;

        // get childID from the CallbackEngine and set pointer to this CallbackObject.
        this->bind_to_parent();
    }

    CallbackObject::CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* parent_pointer)
    {
        // constructor.
        this->callback = callback;
        this->parent_pointer = parent_pointer;

        // get childID from the CallbackEngine and set pointer to this CallbackObject.
        this->bind_to_parent();
    }

    CallbackObject::~CallbackObject()
    {
        std::cout << "This callback object will be destroyed.\n";

        // destroy all callback parameters of this callback object.
        std::cout << "All callback parameters of this callback object will be destroyed.\n";
        for (uint32_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
        {
            delete this->callback_parameter_pointer_vector[child_i];
        }
    }

    void CallbackObject::set_callback_parameter_pointer(uint32_t childID, void* child_pointer)
    {
        std::vector<void*> callback_parameter_void_pointer_vector;
        callback_parameter_void_pointer_vector.assign(this->callback_parameter_pointer_vector.begin(), this->callback_parameter_pointer_vector.end());
        hierarchy::set_child_pointer(childID, child_pointer, callback_parameter_void_pointer_vector, this->free_callback_parameterID_queue);
    }

    AnyValue CallbackObject::execute()
    {
        std::cout << "Hello from AnyValue CallbackObject::execute()\n";

        for (uint32_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
        {
            void* void_input_parameter_pointer = this->callback_parameter_pointer_vector.at(child_i);
            callback_system::CallbackParameter* input_parameter_pointer = static_cast<callback_system::CallbackParameter*>(void_input_parameter_pointer);

            switch (input_parameter_pointer->any_value.type)
            {
                case datatypes::BOOL:
                    this->parent_pointer->set_bool(input_parameter_pointer->name, input_parameter_pointer->any_value.bool_value);
                    break;
                case datatypes::FLOAT:
                    this->parent_pointer->set_float(input_parameter_pointer->name, input_parameter_pointer->any_value.float_value);
                    break;
                case datatypes::DOUBLE:
                    this->parent_pointer->set_double(input_parameter_pointer->name, input_parameter_pointer->any_value.double_value);
                    break;
                case datatypes::INT32_T:
                    this->parent_pointer->set_int32_t(input_parameter_pointer->name, input_parameter_pointer->any_value.int32_t_value);
                    break;
                case datatypes::UINT32_T:
                    this->parent_pointer->set_uint32_t(input_parameter_pointer->name, input_parameter_pointer->any_value.uint32_t_value);
                    break;
                case datatypes::VOID_POINTER:
                    this->parent_pointer->set_void_pointer(input_parameter_pointer->name, input_parameter_pointer->any_value.void_pointer);
                    break;
                default:
                    break;
            }
        }
        return this->callback(this->callback_parameter_pointer_vector);
    }
}
