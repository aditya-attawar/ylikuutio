#include "entity.hpp"
#include "universe.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace ontology
{
    Entity::Entity(ontology::Universe* universe)
    {
        // constructor.
        this->childID = -1;
        this->universe_pointer = universe;
        this->prerender_callback = nullptr;
        this->postrender_callback = nullptr;
    }

    Entity::~Entity()
    {
        // destructor.
        std::cout << "Entity destructor called.\n";

        if (this->name.empty())
        {
            std::cerr << "Entity destructor: error: name is empty.\n";
            return;
        }

        if (this->universe_pointer == nullptr)
        {
            std::cerr << "Entity destructor: error: `universe_pointer` is `nullptr`.\n";
            return;
        }

        // OK, this `Entity` had a name, so it's name shall be erased.
        if (this->universe_pointer->entity_map.count(this->name) != 0)
        {
            std::cout << "Entity destructor: erasing " << this->name << " from `entity_map` ...\n";

            // OK, `Universe` knows the name of this `Entity`.
            this->universe_pointer->entity_map.erase(this->name);
        }
    }

    std::string Entity::get_type()
    {
        return this->type;
    }

    void Entity::prerender()
    {
        if (this->prerender_callback != nullptr &&
                this->universe_pointer != nullptr &&
                this->universe_pointer->setting_master_pointer != nullptr)
        {
            this->prerender_callback(this->universe_pointer, this->universe_pointer->setting_master_pointer);
        }
    }

    void Entity::postrender()
    {
        if (this->postrender_callback != nullptr &&
                this->universe_pointer != nullptr &&
                this->universe_pointer->setting_master_pointer != nullptr)
        {
            this->postrender_callback(this->universe_pointer, this->universe_pointer->setting_master_pointer);
        }
    }
}
