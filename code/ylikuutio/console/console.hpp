#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

#include "console_struct.hpp"
#include "console_command_callback.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#include "SDL.h"

// Include standard headers
#include <cstddef>       // std::size_t
#include <list>          // std::list
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `Console` works through keypress callbacks and keyrelease callbacks, and
// `glfwSetCharModsCallback`. If the action of a key should not happen many
// times in a very fast succession, some means to control the frequency is
// needed. The easiest option is to use a `bool` variable like
// `bool enable_action`.
//
// In the keypress callback, the value of `enable_action` is tested, and
// nothing is done if it's `false`.
//
// If `enable_action` is `true`, the corresponding action takes place,
// after which `enable_action` is set to `false`.
//
// In the keyrelease callback `enable_action` is set to `true`.
//
// `glfwSetCharModsCallback` sets a separate callback for some special keys.
// This is used for entering text into console (writing commands).
// All other console-related functions are implemented through keypress
// callbacks and keyrelease callbacks.

namespace yli
{
    namespace map
    {
        template <class T1>
            void print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, yli::console::Console* const console);
    }

    namespace console
    {
        class Console
        {
            public:
                // constructor.
                Console(const ConsoleStruct& console_struct);

                // destructor.
                ~Console();

                void set_my_keypress_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer);
                void set_my_keyrelease_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer);
                void set_font2D(yli::ontology::Font2D* const font2D);
                void add_command_callback(const std::string& command, ConsoleCommandCallback callback);
                void print_text(const std::string& text);
                void print_help();
                void draw_console() const;

                bool get_in_console() const;
                void process_key_event(const SDL_KeyboardEvent& keyboard_event);

                // Public callbacks.

                // Action mode keyrelease callbacks begin here.

                static std::shared_ptr<yli::datatypes::AnyValue> enable_enter_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Action mode keypress callbacks begin here.

                static std::shared_ptr<yli::datatypes::AnyValue> enter_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Console mode keyrelease callbacks begin here.

                static std::shared_ptr<yli::datatypes::AnyValue> enable_exit_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> release_left_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> release_right_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> release_left_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> release_right_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> release_left_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> release_right_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_move_to_previous_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_move_to_next_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_backspace(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_enter_key(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_ctrl_c(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_ctrl_w(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_page_up(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_page_down(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_home(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enable_end(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Console mode keypress callbacks begin here.

                static std::shared_ptr<yli::datatypes::AnyValue> exit_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> press_left_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> press_right_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> press_left_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> press_right_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> press_left_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> press_right_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> move_to_previous_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> move_to_next_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> backspace(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> enter_key(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> ctrl_c(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> ctrl_w(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> page_up(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> page_down(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> home(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::datatypes::AnyValue> end(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Public callbacks end here.

                template <class T1>
                    friend void yli::map::print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, yli::console::Console* const console);

            private:
                static void charmods_callback(SDL_Window* window, unsigned int codepoint, int mods);

                // Callbacks end here.

                yli::ontology::Universe* get_universe() const;

                void copy_historical_input_into_current_input();
                bool exit_console();
                void delete_character();
                void move_cursor_left();
                void move_cursor_right();
                void move_cursor_to_start_of_line();
                void move_cursor_to_end_of_line();

                std::list<char> current_input; // This is used for actual inputs.
                std::list<char>::iterator cursor_it;
                std::size_t cursor_index;
                bool in_console;
                bool can_move_to_previous_input;
                bool can_move_to_next_input;
                bool can_backspace;
                bool can_enter_key;
                bool can_ctrl_c;
                bool can_ctrl_w;
                bool can_page_up;
                bool can_page_down;
                bool can_home;
                bool can_end;
                bool is_left_control_pressed;
                bool is_right_control_pressed;
                bool is_left_alt_pressed;
                bool is_right_alt_pressed;
                bool is_left_shift_pressed;
                bool is_right_shift_pressed;

                std::vector<std::list<char>> command_history;
                std::vector<std::list<char>> console_history;

                bool in_history;
                bool in_historical_input;
                std::size_t history_line_i;
                std::size_t historical_input_i;
                std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.

                // These are related to keypress callbacks.
                std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
                std::vector<KeyAndCallbackStruct>* previous_keypress_callback_engine_vector_pointer;
                std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer;

                // These are related to keyrelease callbacks.
                std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
                std::vector<KeyAndCallbackStruct>* previous_keyrelease_callback_engine_vector_pointer;
                std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer;

                // `std::unordered_map` contains console command callbacks.
                std::unordered_map<std::string, ConsoleCommandCallback> command_callback_map;

                // This is a pointer to `yli::ontology::Universe`.
                yli::ontology::Universe* universe;

                // This is a pointer to `font2D::Font2D` instance that is used for printing.
                yli::ontology::Font2D* font2D_pointer;

                std::size_t console_top_y;
                std::size_t console_bottom_y;
                std::size_t console_left_x;
                std::size_t console_right_x;

                std::size_t n_rows;
                std::size_t n_columns;

                const std::string prompt = "$ ";
        };
    }
}

#endif
