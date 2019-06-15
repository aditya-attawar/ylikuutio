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

#include "console.hpp"
#include "console_command_callback.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"

#include "SDL.h"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <iterator>      // std::back_inserter
#include <limits>        // std::numeric_limits
#include <list>          // std::list
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace console
    {
        Console::Console(
                yli::ontology::Universe* const universe,
                std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer,
                std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer)
        {
            // constructor.
            this->should_be_rendered = true;
            this->cursor_it = this->current_input.begin();
            this->cursor_index = 0;
            this->in_history = false;
            this->in_historical_input = false;
            this->history_line_i = std::numeric_limits<std::size_t>::max();     // some dummy value.
            this->historical_input_i = std::numeric_limits<std::size_t>::max(); // some dummy value.
            this->in_console = false;
            this->can_move_to_previous_input = false;
            this->can_move_to_next_input = false;
            this->can_backspace = false;
            this->can_enter_key = false;
            this->can_ctrl_c = false;
            this->can_ctrl_w = false;
            this->can_page_up = false;
            this->can_page_down = false;
            this->can_home = false;
            this->can_end = false;
            this->is_left_control_pressed = false;
            this->is_right_control_pressed = false;
            this->is_left_alt_pressed = false;
            this->is_right_alt_pressed = false;
            this->is_left_shift_pressed = false;
            this->is_right_shift_pressed = false;
            this->previous_keypress_callback_engine_vector_pointer = nullptr;
            this->my_keypress_callback_engine_vector_pointer = nullptr;
            this->previous_keyrelease_callback_engine_vector_pointer = nullptr;
            this->my_keyrelease_callback_engine_vector_pointer = nullptr;

            std::cout << "Defining pointers in Console::Console\n";

            // This is a pointer to `std::vector<yli::callback_system::KeyAndCallbackStruct>*` that controls keypress callbacks.
            this->current_keypress_callback_engine_vector_pointer_pointer = current_keypress_callback_engine_vector_pointer_pointer;
            std::cout << "1st pointer defined in Console::Console\n";

            // This is a pointer to `std::vector<yli::callback_system::KeyAndCallbackStruct>*` that controls keyrelease callbacks.
            this->current_keyrelease_callback_engine_vector_pointer_pointer = current_keyrelease_callback_engine_vector_pointer_pointer;
            std::cout << "2nd pointer defined in Console::Console\n";

            // This is a pointer to `yli::ontology::Universe`.
            this->universe = universe;
            std::cout << "4th pointer defined in Console::Console\n";

            this->universe->set_console(this);
            std::cout << "5th pointer defined in Console::Console\n";

            // Initialize `console_top_y` to 9.
            // `console_top_y` should be set by `activate_console_top_y` anyway.
            std::cout << "Initializing console_top_y\n";
            this->console_top_y = 9;

            // Initialize `console_bottom_y` to 0.
            // `console_bottom_y` should be set by `activate_console_bottom_y` anyway.
            std::cout << "Initializing console_bottom_y\n";
            this->console_bottom_y = 0;

            // Initialize `console_left_x` to 0.
            // `console_left_x` should be set by `activate_console_left_x` anyway.
            std::cout << "Initializing console_left_x\n";
            this->console_left_x = 0;

            // Initialize `console_right_x` to 9.
            // `console_right_x` should be set by `activate_console_right_x` anyway.
            std::cout << "Initializing console_right_x\n";
            this->console_right_x = 9;

            // Initialize `n_rows`.
            // `n_rows` should be set by `activate_console_top_y` and `activate_console_bottom_y` anyway.
            std::cout << "Initializing n_rows\n";
            this->n_rows = this->console_top_y - this->console_bottom_y + 1;

            // Initialize `n_columns`.
            // `n_columns` should be set by `activate_console_left_x` and `activate_console_right_x` anyway.
            std::cout << "Initializing n_columns\n";
            this->n_columns = this->console_right_x - this->console_left_x + 1;

            if (this->n_rows > this->universe->get_window_height() / this->universe->get_text_size())
            {
                // Upper limit for the the number of rows is window height divided by text size.
                this->n_rows = this->universe->get_window_height() / this->universe->get_text_size();
            }

            if (this->n_columns > this->universe->get_window_width() / this->universe->get_text_size())
            {
                // Upper limit for the the number of columns is window width divided by text size.
                this->n_columns = this->universe->get_window_width() / this->universe->get_text_size();
            }
        }

        Console::~Console()
        {
            // destructor.
            this->exit_console();
        }

        void Console::set_my_keypress_callback_engine_vector_pointer(std::vector<yli::callback_system::KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer)
        {
            this->my_keypress_callback_engine_vector_pointer = my_keypress_callback_engine_vector_pointer;
        }

        void Console::add_command_callback(const std::string& command, ConsoleCommandCallback callback)
        {
            this->command_callback_map[command] = callback;
        }

        void Console::set_console_top_y(const uint32_t console_top_y)
        {
            this->console_top_y = console_top_y;
            this->n_rows = this->console_top_y - this->console_bottom_y + 1;

            if (this->n_rows > this->universe->get_window_height() / this->universe->get_text_size())
            {
                // Upper limit for the the number of rows is window height divided by text size.
                this->n_rows = this->universe->get_window_height() / this->universe->get_text_size();
            }
        }

        void Console::set_console_bottom_y(const uint32_t console_bottom_y)
        {
            this->console_bottom_y = console_bottom_y;
            this->n_rows = this->console_top_y - this->console_bottom_y + 1;

            if (this->n_rows > this->universe->get_window_height() / this->universe->get_text_size())
            {
                // Upper limit for the the number of rows is window height divided by text size.
                this->n_rows = this->universe->get_window_height() / this->universe->get_text_size();
            }
        }

        void Console::set_console_left_x(const uint32_t console_left_x)
        {
            this->console_left_x = console_left_x;
            this->n_columns = this->console_right_x - this->console_left_x + 1;

            if (this->n_columns > this->universe->get_window_width() / this->universe->get_text_size())
            {
                // Upper limit for the the number of columns is window width divided by text size.
                this->n_columns = this->universe->get_window_width() / this->universe->get_text_size();
            }
        }

        void Console::set_console_right_x(const uint32_t console_right_x)
        {
            this->console_right_x = console_right_x;
            this->n_columns = this->console_right_x - this->console_left_x + 1;

            if (this->n_columns > this->universe->get_window_width() / this->universe->get_text_size())
            {
                // Upper limit for the the number of columns is window width divided by text size.
                this->n_columns = this->universe->get_window_width() / this->universe->get_text_size();
            }
        }

        void Console::set_my_keyrelease_callback_engine_vector_pointer(std::vector<yli::callback_system::KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer)
        {
            this->my_keyrelease_callback_engine_vector_pointer = my_keyrelease_callback_engine_vector_pointer;
        }

        void Console::print_text(const std::string& text)
        {
            // This function is to be called from console command callbacks to print text on console.
            // Please note that it is not necessary to be in console to be able to print in console.
            std::list<char> text_char_list;
            std::size_t current_line_length = 0;

            for (const char& my_char : text)
            {
                if (my_char == '\n')
                {
                    // A newline.
                    this->console_history.push_back(text_char_list);
                    text_char_list.clear();
                    current_line_length = 0;
                }
                else if (++current_line_length <= this->n_columns)
                {
                    // Normal case.
                    text_char_list.push_back(my_char);
                }
                else
                {
                    // Newline is needed due to too long line.
                    this->console_history.push_back(text_char_list);
                    text_char_list.clear();
                    text_char_list.push_back(my_char);
                    current_line_length = 1;
                }
            }

            if (text_char_list.size() > 0)
            {
                this->console_history.push_back(text_char_list);
            }
        }

        void Console::print_help()
        {
            this->print_text("Available commands:");
            yli::map::print_keys_to_console(this->command_callback_map, this);
        }

        void Console::render() const
        {
            if (!this->in_console || !this->should_be_rendered)
            {
                return;
            }

            if (this->universe == nullptr)
            {
                return;
            }

            yli::ontology::Font2D* const font2D = this->universe->get_active_font2D();

            if (font2D == nullptr)
            {
                return;
            }

            // Convert current input into std::string.
            std::size_t characters_for_line = this->universe->get_window_width() / this->universe->get_text_size();

            // Draw the console to screen using `font2D::print_text2D`.
            TextStruct text_struct;
            text_struct.screen_width = this->universe->get_window_width();
            text_struct.screen_height = this->universe->get_window_height();
            text_struct.text_size = this->universe->get_text_size();
            text_struct.font_size = this->universe->get_font_size();
            text_struct.font_texture_file_format = "bmp";

            text_struct.x = 0;
            text_struct.y = this->universe->get_window_height() - (2 * this->universe->get_text_size());
            text_struct.horizontal_alignment = "left";
            text_struct.vertical_alignment = "top";

            if (this->in_history)
            {
                std::size_t history_end_i = history_line_i + this->n_rows;

                for (std::size_t history_i = history_line_i; history_i < history_end_i && history_i < this->console_history.size(); history_i++)
                {
                    std::list<char> historical_text = this->console_history.at(history_i);
                    text_struct.text += yli::string::convert_std_list_char_to_std_string(historical_text, characters_for_line, characters_for_line) + "\\n";
                }
            }
            else
            {
                std::size_t n_lines_of_current_input = (this->prompt.size() + this->current_input.size() - 1) / this->n_columns + 1;

                std::size_t history_start_i;

                if (n_lines_of_current_input > this->n_rows)
                {
                    // Current input does not fit completely in the console 'window'.

                    // Split current input into lines and print only n last lines,
                    // where n == `this->n_rows`.
                    std::list<char> current_input_with_prompt = this->current_input;
                    std::list<char>::iterator it = current_input_with_prompt.begin();

                    // Copy prompt into the front of the current input.
                    for (const char& my_char : this->prompt)
                    {
                        current_input_with_prompt.insert(it, my_char);
                    }

                    // Convert into a vector of lines.
                    std::vector<std::string> current_input_vector = yli::string::convert_std_list_char_to_std_vector_std_string(
                            current_input_with_prompt,
                            this->n_columns);

                    // Print only n last lines.
                    for (std::size_t i = current_input_vector.size() - this->n_rows; i < current_input_vector.size(); i++)
                    {
                        text_struct.text += current_input_vector.at(i) + "\\n";
                    }
                }
                else
                {
                    // Current input fits completely in the console 'window'.

                    if (this->console_history.size() + n_lines_of_current_input > this->n_rows)
                    {
                        // Everything does not fit in the console 'window'.
                        history_start_i = this->console_history.size() - this->n_rows + n_lines_of_current_input;
                    }
                    else
                    {
                        // Everything does fit in the console 'window'.
                        history_start_i = 0;
                    }

                    // We are not in history so print everything to the end of the history.
                    for (std::size_t history_i = history_start_i; history_i < this->console_history.size(); history_i++)
                    {
                        std::list<char> historical_text = this->console_history.at(history_i);
                        text_struct.text += yli::string::convert_std_list_char_to_std_string(historical_text, characters_for_line, characters_for_line) + "\\n";
                    }
                    text_struct.text += this->prompt + yli::string::convert_std_list_char_to_std_string(
                            this->current_input,
                            characters_for_line - this->prompt.size(), // First line is shorter due to space taken by the prompt.
                            characters_for_line);                      // The rest lines have full length.
                }
            }

            font2D->print_text2D(text_struct);
        }

        bool Console::get_in_console() const
        {
            return this->in_console;
        }

        void Console::process_key_event(const SDL_KeyboardEvent& keyboard_event)
        {
            const uint16_t modifiers = keyboard_event.keysym.mod;
            const uint16_t shift_bitmask = KMOD_LSHIFT | KMOD_RSHIFT;
            const uint16_t ctrl_alt_altgr_bitmask = KMOD_LCTRL | KMOD_RCTRL | KMOD_LALT | KMOD_RALT | KMOD_MODE;

            if (keyboard_event.state == SDL_PRESSED &&
                    keyboard_event.keysym.scancode != SDL_SCANCODE_GRAVE &&
                    keyboard_event.keysym.sym != SDLK_UNKNOWN &&
                    keyboard_event.keysym.sym != SDLK_RETURN &&
                    keyboard_event.keysym.sym != SDLK_KP_ENTER &&
                    keyboard_event.keysym.sym >= 0x20 &&
                    keyboard_event.keysym.sym <= 0x7f &&
                    ((modifiers & ctrl_alt_altgr_bitmask) == 0) &&
                    this->in_console)
            {
                this->in_history = false;

                char keyboard_char = static_cast<char>(keyboard_event.keysym.sym);

                if ((modifiers & shift_bitmask) != 0)
                {
                    // Before a support for different keyboard layouts in implemented,
                    // use US QWERTY layout as reference.
                    switch (keyboard_char)
                    {
                        case '`':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '~');
                            break;
                        case '1':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '!');
                            break;
                        case '2':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '@');
                            break;
                        case '3':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '#');
                            break;
                        case '4':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '$');
                            break;
                        case '5':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '%');
                            break;
                        case '6':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '^');
                            break;
                        case '7':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '&');
                            break;
                        case '8':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '*');
                            break;
                        case '9':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '(');
                            break;
                        case '0':
                            this->cursor_it = this->current_input.insert(this->cursor_it, ')');
                            break;
                        case '-':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '_');
                            break;
                        case '=':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '+');
                            break;
                        case '[':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '{');
                            break;
                        case ']':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '}');
                            break;
                        case '\\':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '|');
                            break;
                        case ';':
                            this->cursor_it = this->current_input.insert(this->cursor_it, ':');
                            break;
                        case '\'':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '"');
                            break;
                        case ',':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '<');
                            break;
                        case '.':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '>');
                            break;
                        case '/':
                            this->cursor_it = this->current_input.insert(this->cursor_it, '?');
                            break;
                        default:
                            if (keyboard_char >= 'a' && keyboard_char <= 'z')
                            {
                                this->cursor_it = this->current_input.insert(this->cursor_it, keyboard_char - ('a' - 'A'));
                            }
                            break;
                    }
                }
                else
                {
                    this->cursor_it = this->current_input.insert(this->cursor_it, keyboard_char);
                }

                this->cursor_it++;
                this->cursor_index++;
            }
        }

        yli::ontology::Universe* Console::get_universe() const
        {
            return this->universe;
        }

        void Console::copy_historical_input_into_current_input()
        {
            if (this->in_console)
            {
                // Copy selected historical input into current input.
                this->current_input.clear();
                std::copy(this->command_history.at(this->historical_input_i).begin(),
                        this->command_history.at(this->historical_input_i).end(),
                        std::back_inserter(this->current_input));
            }
        }

        bool Console::exit_console()
        {
            if (this->in_console &&
                    this->previous_keypress_callback_engine_vector_pointer != nullptr &&
                    this->previous_keyrelease_callback_engine_vector_pointer != nullptr)
            {
                // Restore previous keypress callback engine vector pointer.
                *this->current_keypress_callback_engine_vector_pointer_pointer = this->previous_keypress_callback_engine_vector_pointer;

                // Restore previous keyrelease callback engine vector pointer.
                *this->current_keyrelease_callback_engine_vector_pointer_pointer = this->previous_keyrelease_callback_engine_vector_pointer;

                // Mark that we have exited the console.
                this->in_console = false;

                return true;
            }
            return false;
        }

        void Console::delete_character()
        {
            if (this->in_console)
            {
                this->current_input.erase(this->cursor_it);
            }
        }

        void Console::move_cursor_left()
        {
            if (this->in_console)
            {
                this->in_history = false;

                if (this->cursor_it != this->current_input.begin())
                {
                    this->cursor_it--;
                    this->cursor_index--;
                }
            }
        }

        void Console::move_cursor_right()
        {
            if (this->in_console)
            {
                this->in_history = false;

                if (this->cursor_it != this->current_input.end())
                {
                    this->cursor_it++;
                    this->cursor_index++;
                }
            }
        }

        void Console::move_cursor_to_start_of_line()
        {
            if (this->in_console)
            {
                this->in_history = false;
                this->cursor_it = this->current_input.begin();
                this->cursor_index = 0;
            }
        }

        void Console::move_cursor_to_end_of_line()
        {
            if (this->in_console)
            {
                this->in_history = false;
                this->cursor_it = this->current_input.end();
                this->cursor_index = this->current_input.size();
            }
        }

        // Console command callbacks begin here.

        std::shared_ptr<yli::datatypes::AnyValue> Console::clear(
                yli::console::Console* const console,
                yli::ontology::Entity* const universe_entity,
                const std::vector<std::string>& command_parameters)
        {
            if (console != nullptr)
            {
                console->in_history = false;
                console->in_historical_input = false;
                console->history_line_i = 0;
                console->historical_input_i = 0;
                console->command_history.clear();
                console->console_history.clear();
                console->current_input.clear();
            }

            uint32_t clear_console_magic_number = CLEAR_CONSOLE_MAGIC_NUMBER;
            return std::make_shared<yli::datatypes::AnyValue>(clear_console_magic_number);
        }

        // Public callbacks end here.
    }
}
