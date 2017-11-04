#ifndef __SETTING_HPP_INCLUDED
#define __SETTING_HPP_INCLUDED

#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace console
{
    class Console;
}

namespace config
{
    class SettingMaster;

    class Setting
    {
        public:
            // constructor.
            Setting(const SettingStruct& setting_struct);

            // destructor.
            ~Setting();

            std::string help();

            friend SettingMaster;
            friend console::Console;

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            std::string name;

            // The setting value (may be a pointer a some datatype).
            std::shared_ptr<datatypes::AnyValue> setting_value;

            // pointer to `ActivateCallback` used to activate the new value after setting it.
            ActivateCallback activate_callback;

            // pointer to `ReadCallback` used to read the value. Leave to `nullptr` to read the value from `setting_value` of `class Setting`.
            ReadCallback read_callback;

            config::SettingMaster* parent; // pointer to `SettingMaster`.

            int32_t childID;                       // setting ID, returned by `config::SettingMaster->get_settingID()`.
    };
}

#endif
