#ifndef __GLYPH_HPP_INCLUDED
#define __GLYPH_HPP_INCLUDED

#include "species_or_glyph.hpp"
#include "entity_templates.hpp"
#include "model.hpp"
#include "text3D.hpp"
#include "vector_font.hpp"
#include "glyph_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Universe;
    class Object;

    class Glyph: public ontology::Model
    {
        public:
            // constructor.
            Glyph(GlyphStruct glyph_struct);

            // destructor.
            // glyphs should be destroyed only by destroying the entire `VectorFont`.
            ~Glyph();

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, ontology::Object* child_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            uint32_t get_objectID();

            friend class Object;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);

        private:
            void bind_to_parent();

            // this method renders all `Object`s of this `Glyph`.
            void render();

            ontology::VectorFont* parent_pointer;  // pointer to `VectorFont`.

            std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
            const char* glyph_name_pointer;        // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
            const char* unicode_char_pointer;      // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.

            ontology::Universe* universe_pointer;
    };
}

#endif
