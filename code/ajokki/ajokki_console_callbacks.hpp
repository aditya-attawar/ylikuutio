#ifndef __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/console/command_and_callback_struct.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace ajokki
{
    datatypes::AnyValue* version(
            console::Console* console,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    datatypes::AnyValue* quit(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    datatypes::AnyValue* help(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    datatypes::AnyValue* red(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    datatypes::AnyValue* green(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    datatypes::AnyValue* blue(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);
}

#endif
