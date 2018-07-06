#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

// `World` is just a collection of `Scene`s which share some common resources,
// like `VectorFont`s.

namespace ylikuutio
{
    namespace ontology
    {
        class Universe;
        class Scene;

        class World: public ylikuutio::ontology::Entity
        {
            public:
                void bind(ylikuutio::ontology::Scene* const scene);

                // constructor.
                World(ylikuutio::ontology::Universe* const universe)
                    : Entity(universe)
                {
                    this->parent = universe;
                    this->active_scene = nullptr;

                    this->number_of_scenes = 0;

                    // get `childID` from `Universe` and set pointer to this `World`.
                    this->bind_to_parent();

                    this->child_vector_pointers_vector.push_back(&this->scene_pointer_vector);
                    this->type = "ylikuutio::ontology::World*";

                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~World();

                // this method renders the active `Scene` of this `World`.
                void render();

                // this method stes the active `Scene`.
                void set_active_scene(ylikuutio::ontology::Scene* const scene);

                ylikuutio::ontology::Scene* get_active_scene() const;

                // this method sets a `Scene` pointer.
                void set_scene_pointer(const int32_t childID, ylikuutio::ontology::Scene* const child_pointer);

                ylikuutio::ontology::Entity* get_parent() const override;
                int32_t get_number_of_children() const override;
                int32_t get_number_of_descendants() const override;

                template<class T1>
                    friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);

            private:
                void bind_to_parent();

                ylikuutio::ontology::Universe* parent; // pointer to the `Universe`.

                std::vector<ylikuutio::ontology::Scene*> scene_pointer_vector;
                std::queue<int32_t> free_sceneID_queue;
                int32_t number_of_scenes;

                ylikuutio::ontology::Scene* active_scene;
        };
    }
}

#endif
