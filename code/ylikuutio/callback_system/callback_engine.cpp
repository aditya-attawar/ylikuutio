#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace callback_system
{
    CallbackEngine::CallbackEngine()
    {
        // constructor.
        this->number_of_callback_objects = 0;
    }

    CallbackEngine::~CallbackEngine()
    {
        // destructor.
        std::cout << "This callback engine will be destroyed.\n";

        // destroy all callback objects of this callback engine.
        std::cout << "All callback objects of this callback engine will be destroyed.\n";
        hierarchy::delete_children<callback_system::CallbackObject*>(this->callback_object_pointer_vector, &this->number_of_callback_objects);
    }

    void CallbackEngine::set_callback_object_pointer(const uint32_t childID, callback_system::CallbackObject* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->callback_object_pointer_vector, this->free_callback_objectID_queue, &this->number_of_callback_objects);
    }

    datatypes::AnyValue* CallbackEngine::execute()
    {
        datatypes::AnyValue* any_value = new datatypes::AnyValue();

        // execute all callbacks.
        for (uint32_t child_i = 0; child_i < this->callback_object_pointer_vector.size(); child_i++)
        {
            callback_system::CallbackObject* callback_object_pointer = static_cast<callback_system::CallbackObject*>(this->callback_object_pointer_vector[child_i]);
            any_value = callback_object_pointer->execute();

            this->return_values.push_back(any_value);
        }

        this->return_values.clear();
        return any_value;
    }

    uint32_t CallbackEngine::get_n_of_return_values()
    {
        return this->return_values.size();
    }

    datatypes::AnyValue* CallbackEngine::get_nth_return_value(uint32_t n)
    {
        // note: indexing of `n` begins from 0.

        uint32_t n_of_return_values = this->get_n_of_return_values();

        if (n_of_return_values <= n)
        {
            return nullptr;
        }

        return this->return_values.at(n_of_return_values - 1);
    }

    datatypes::AnyValue* CallbackEngine::get_previous_return_value()
    {
        uint32_t n_of_return_values = this->get_n_of_return_values();

        if (n_of_return_values == 0)
        {
            return nullptr;
        }

        return this->return_values.at(this->return_values.size() - 1);
    }
}
