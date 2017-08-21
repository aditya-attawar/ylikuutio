#ifndef __CONSOLE_COMMAND_CALLBACK_HPP_INCLUDED
#define __CONSOLE_COMMAND_CALLBACK_HPP_INCLUDED

// Include standard headers
#include <string> // std::string
#include <vector> // std::vector

namespace console
{
    class Console;
}

namespace datatypes
{
    class AnyValue;
}

namespace ontology
{
    class Universe;
}

typedef datatypes::AnyValue* (*ConsoleCommandCallback) (
        console::Console*,
        ontology::Universe*,
        std::vector<std::string>& command_parameters);

#endif
