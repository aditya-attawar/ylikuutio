#ifndef __CONSOLE_COMMAND_CALLBACK_HPP_INCLUDED
#define __CONSOLE_COMMAND_CALLBACK_HPP_INCLUDED

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <string> // std::string
#include <vector> // std::vector

namespace ylikuutio
{
    namespace console
    {
        class Console;
    }
}

namespace datatypes
{
    class AnyValue;
}

namespace ontology
{
    class Entity;
}

typedef std::shared_ptr<datatypes::AnyValue> (*ConsoleCommandCallback) (
        ylikuutio::console::Console*,
        ontology::Entity*,
        std::vector<std::string>& command_parameters);

#endif
