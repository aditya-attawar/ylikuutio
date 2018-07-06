#ifndef __CALLBACK_OBJECT_HPP_INCLUDED
#define __CALLBACK_OBJECT_HPP_INCLUDED

#include "callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace ylikuutio
{
    namespace callback_system
    {
        class CallbackParameter;

        class CallbackObject
        {
            // CallbackObject is an object that contains a single callback.

            public:
                // constructor.
                CallbackObject(ylikuutio::callback_system::CallbackEngine* parent);

                // constructor.
                CallbackObject(const InputParametersToAnyValueCallback callback, ylikuutio::callback_system::CallbackEngine* parent);

                // destructor.
                virtual ~CallbackObject();

                // this method changes the callback without changing the parameters of CallbackObject.
                void set_new_callback(const InputParametersToAnyValueCallback callback);

                // getter functions for callbacks and callback objects.
                std::shared_ptr<datatypes::AnyValue> get_any_value(const std::string& name) const;
                std::shared_ptr<datatypes::AnyValue> get_arg(const uint32_t arg_i) const;

                // setter function for callbacks and callback objects.
                void set_any_value(const std::string& name, std::shared_ptr<datatypes::AnyValue> any_value);

                friend class CallbackEngine;
                friend class CallbackParameter;
                template<class T1>
                    friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
                template<class T1, class T2>
                    friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

            protected:
                void bind_to_parent();

                // this method sets a callback parameter pointer.
                void set_callback_parameter_pointer(const int32_t childID, ylikuutio::callback_system::CallbackParameter* const child_pointer);

                void bind_child_to_parent(ylikuutio::callback_system::CallbackParameter* child_pointer);

                // execute this callback.
                virtual std::shared_ptr<datatypes::AnyValue> execute();

                ylikuutio::callback_system::CallbackEngine* parent; // pointer to the callback engine.

                int32_t childID;                                 // callback object ID, returned by `ylikuutio::callback_system::CallbackEngine->get_callback_objectID()`.

                std::vector<ylikuutio::callback_system::CallbackParameter*> callback_parameter_pointer_vector;
                std::queue<int32_t> free_callback_parameterID_queue;
                int32_t number_of_callback_parameters;

                InputParametersToAnyValueCallback callback;

                // A hash map used to store variables.
                std::unordered_map<std::string, datatypes::AnyValue> anyvalue_hashmap;
        };
    }
}

#endif
