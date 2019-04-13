#ifndef __MODEL_HPP_INCLUDED
#define __MODEL_HPP_INCLUDED

#include "entity.hpp"
#include "species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Object;
        class Chunk;

        class Model: public yli::ontology::Entity
        {
            public:
                // constructor.
                Model(yli::ontology::Universe* const universe, const bool vram_buffer_in_use)
                    : Entity(universe)
                {
                    // constructor.

                    // Initialize class members with some dummy values.
                    // `std::numeric_limits<std::size_t>::max()` means that `childID` is not defined.
                    this->childID                      = std::numeric_limits<std::size_t>::max();
                    this->lightID                      = 0;
                    this->vertex_position_modelspaceID = 0;
                    this->vertexUVID                   = 0;
                    this->vertex_normal_modelspaceID   = 0;
                    this->vertexbuffer                 = 0;
                    this->uvbuffer                     = 0;
                    this->normalbuffer                 = 0;
                    this->elementbuffer                = 0;
                    this->initial_rotate_angle         = 0.0f;
                    this->initial_rotate_vector        = glm::vec3(0.0f, 1.0f, 1.0f);

                    this->number_of_objects = 0;

                    this->vram_buffer_in_use = vram_buffer_in_use;

                    // `yli::ontology::Entity` member variables begin here.
                    // `yli::ontology::Model` constructor takes care of `child_vector_pointers_vector`.
                    // Descendant classes of `yli::ontology::Model` need to set the value of `type_string`!
                    // Descendant classes of `yli::ontology::Model` need to set the value of `can_be_erased`!
                    this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
                    this->type_string = "yli::ontology::Model*";
                }

                Model(const Model&) = delete;            // Delete copy constructor.
                Model &operator=(const Model&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Model();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                std::size_t get_number_of_vertices() const;
                const std::vector<glm::vec3>& get_vertices() const;
                const std::vector<glm::vec2>& get_uvs() const;
                const std::vector<glm::vec3>& get_normals() const;
                const std::vector<uint32_t>& get_indices() const;

                uint32_t get_vertex_position_modelspaceID() const;
                uint32_t get_vertexUVID() const;
                uint32_t get_vertex_normal_modelspaceID() const;

                uint32_t get_vertexbuffer() const;
                uint32_t get_uvbuffer() const;
                uint32_t get_normalbuffer() const;
                uint32_t get_elementbuffer() const;

                void store_vertex_position_modelspaceID(const uint32_t vertex_position_modelspaceID);
                void store_vertexUVID(const uint32_t vertexUVID);
                void store_vertex_normal_modelspaceID(const uint32_t vertex_normal_modelspaceID);

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_species_or_glyph(T1 species_or_glyph_pointer);

            protected:
                float initial_rotate_angle;              // initial rotate angle.
                glm::vec3 initial_rotate_vector;         // initial rotate vector.

                std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
                glm::vec3 light_position;                // light position.

                uint32_t lightID;                        // light ID, returned by `glGetUniformLocation(programID, "light_position_worldspace");`.

                std::vector<yli::ontology::Object*> object_pointer_vector;
                std::queue<std::size_t> free_objectID_queue;
                std::size_t number_of_objects;

                std::string triangulation_type;

                uint32_t vertex_position_modelspaceID;
                uint32_t vertexUVID;
                uint32_t vertex_normal_modelspaceID;

                std::vector<glm::vec3> vertices;         // vertices of the `Model`.
                std::vector<glm::vec2> uvs;              // UVs of the `Model`.
                std::vector<glm::vec3> normals;          // normals of the `Model`.

                std::vector<uint32_t> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
                std::vector<glm::vec3> indexed_vertices;
                std::vector<glm::vec2> indexed_uvs;
                std::vector<glm::vec3> indexed_normals;

                uint32_t vertexbuffer;
                uint32_t uvbuffer;
                uint32_t normalbuffer;
                uint32_t elementbuffer;

                bool vram_buffer_in_use;
        };
    }
}

#endif
