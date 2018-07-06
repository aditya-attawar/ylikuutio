#ifndef __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

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

namespace ajokki
{
    std::shared_ptr<datatypes::AnyValue> version(
            ylikuutio::console::Console* console,
            ontology::Entity*,
            std::vector<std::string>& command_parameters);

    std::shared_ptr<datatypes::AnyValue> quit(
            ylikuutio::console::Console*,
            ontology::Entity*,
            std::vector<std::string>& command_parameters);

    std::shared_ptr<datatypes::AnyValue> help(
            ylikuutio::console::Console*,
            ontology::Entity*,
            std::vector<std::string>& command_parameters);
}

#endif
