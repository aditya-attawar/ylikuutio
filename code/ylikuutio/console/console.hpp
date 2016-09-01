#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

#include "command_and_callback_struct.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <list>          // std::list
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace console
{
    class Console
    {
        public:
            // constructor.
            Console(ConsoleStruct console_struct);

            // destructor.
            ~Console();

            void set_my_keypress_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer);
            void set_my_keyrelease_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer);
            void print_text(std::string text);
            void print_help();
            void draw_console();

            // Public callbacks.

            // Action mode keyrelease callbacks begin here.

            static datatypes::AnyValue* enable_enter_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Action mode keypress callbacks begin here.

            static datatypes::AnyValue* enter_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Console mode keyrelease callbacks begin here.

            static datatypes::AnyValue* enable_exit_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* release_left_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* release_right_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* release_left_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* release_right_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* release_left_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* release_right_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* enable_move_to_previous_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* enable_move_to_next_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* enable_backspace(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* enable_enter_key(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* enable_ctrl_c(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Console mode keypress callbacks begin here.

            static datatypes::AnyValue* exit_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* press_left_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* press_right_control_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* press_left_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* press_right_alt_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* press_left_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* press_right_shift_in_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* move_to_previous_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* move_to_next_input(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* backspace(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* enter_key(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            static datatypes::AnyValue* ctrl_c(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>&,
                    console::Console* console);

            // Public callbacks end here.

        private:
            static void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods);

            // Callbacks end here.

            void copy_historical_input_into_current_input();
            bool exit_console();
            void delete_character();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();
            void page_up();
            void page_down();
            void home();
            void end();

            std::list<char> current_input; // This is used for actual inputs.
            std::list<char>::iterator cursor_it;
            uint32_t cursor_index;
            bool in_console;
            bool can_enter_console;
            bool can_exit_console;
            bool can_move_to_previous_input;
            bool can_move_to_next_input;
            bool can_backspace;
            bool can_enter_key;
            bool can_ctrl_c;
            bool is_left_control_pressed;
            bool is_right_control_pressed;
            bool is_left_alt_pressed;
            bool is_right_alt_pressed;
            bool is_left_shift_pressed;
            bool is_right_shift_pressed;

            std::vector<std::list<char>> command_history;
            std::vector<std::list<char>> console_history;

            bool in_historical_input;
            uint32_t historical_input_i;
            std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.

            // These are related to keypress callbacks.
            std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_keypress_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer;

            // These are related to keyrelease callbacks.
            std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_keyrelease_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer;

            // This is a pointer to `std::unordered_map<std::string, bool>` that contains console command callbacks.
            std::unordered_map<std::string, ConsoleCommandCallback>* command_callback_map_pointer;

            // This is a pointer to `ontology::Universe`.
            ontology::Universe* universe_pointer;

            // This is a pointer to `font2D::Font2D` instance that is used for printing.
            ontology::Font2D* text2D_pointer;
    };
}

#endif
