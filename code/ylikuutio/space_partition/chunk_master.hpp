#ifndef __CHUNK_MASTER_HPP_INCLUDED
#define __CHUNK_MASTER_HPP_INCLUDED

#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

// `ChunkMaster` takes care of acquiring vertices (through `callback`),
// organizing vertices into `Chunk` objects, reconstructing `Chunk`
// objects (if vertices have been modified) and deactivating (by
// unbinding) and possibly deleting `Chunk` objects (if needed).

namespace space_partition
{
    class Chunk;

    class ChunkMaster: public ontology::Entity
    {
        public:
            // constructor.
            ChunkMaster(ontology::Universe* universe, ontology::Material* const parent, GetContentCallback get_content_callback)
                : ontology::Entity(universe)
            {
                // constructor.
                this->get_content_callback = get_content_callback;
                this->number_of_chunks = 0;

                this->parent = parent;

                // get `childID` from `Material` and set pointer to this `ChunkMaster`.
                this->bind_to_parent();

                this->type = "space_partition::ChunkMaster*";
            }

            // destructor.
            virtual ~ChunkMaster();

            friend class Chunk;
            template<class T1>
                friend void ontology::render_children(const std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            // this method renders all `Chunk`s bound to this `ChunkMaster`.
            void render();

            // this method sets `Chunk` pointer.
            void set_chunk_pointer(int32_t childID, space_partition::Chunk* child_pointer);

            int32_t childID;                     // `ChunkMaster` ID, returned by `ontology::Material->get_chunk_masterID()`.

            // Callback used to get the content based on x, y, z.
            GetContentCallback get_content_callback;

            ontology::Material* parent;  // pointer to `Material`.

            std::vector<space_partition::Chunk*> chunk_pointer_vector;
            std::queue<int32_t> free_chunkID_queue;
            int32_t number_of_chunks;
    };
};

#endif
