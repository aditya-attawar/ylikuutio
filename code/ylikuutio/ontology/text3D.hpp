#ifndef __TEXT3D_HPP_INCLUDED
#define __TEXT3D_HPP_INCLUDED

#include "movable.hpp"
#include "glyph_object_creation.hpp"
#include "vector_font.hpp"
#include "text3D_struct.hpp"
#include "object_struct.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Entity;
    class Object;

    class Text3D: public ontology::Movable
    {
        public:
            // constructor.
            // TODO: `Text3D` constructor also creates each `Object`,
            // and binds each to its corresponding `Glyph` for rendering hierarchy,
            // and also binds each to this `Text3D` for ontological hierarchy.
            Text3D(const Text3DStruct& text3D_struct)
                : ontology::Movable(text3D_struct.parent->universe, text3D_struct.cartesian_coordinates)
            {
                // constructor.
                this->rotate_angle = NAN;
                this->text_string = text3D_struct.text_string;
                this->parent = text3D_struct.parent;
                this->universe = this->parent->universe;

                this->number_of_objects = 0;

                // get childID from `VectorFont` and set pointer to this `Text3D`.
                this->bind_to_parent();

                std::cout << "Creating the glyph Objects for the string \"" << this->text_string << "\"\n";

                // Let's create each glyph `Object` in a loop.

                ontology::create_glyph_objects(this->text_string, this);

                this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
            }

            // destructor.
            virtual ~Text3D();

            ontology::Entity* get_parent() override;
            int32_t get_number_of_children() override;
            int32_t get_number_of_descendants() override;

            // this method deletes all glyph Objects of this `Text3D`,
            // sets pointer to this `Text3D` to nullptr,
            // sets `parent` according to the input (the new `VectorFont`),
            // requests a new `childID` from the new `VectorFont`,
            // and creates all glyph Objects of this `Text3D` with the font data.
            // Note: different fonts may provide glyphs for different Unicodes!
            void bind_to_new_parent(ontology::VectorFont* const new_vector_font_pointer);

            // this method sets a object pointer.
            void set_object_pointer(const int32_t childID, ontology::Object* const child_pointer);

            void set_name(const std::string& name);

            friend class Object;
            friend void create_glyph_objects(const std::string& text_string, ontology::Text3D* text3D);
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);

        private:
            void bind_to_parent();

            std::string text_string;

            ontology::VectorFont* parent; // pointer to `VectorFont`.

            glm::vec3 original_scale_vector;      // original scale vector.
            GLfloat rotate_angle;                 // rotate angle.
            glm::vec3 rotate_vector;              // rotate vector.
            glm::vec3 translate_vector;           // translate vector.

            std::vector<ontology::Object*> object_pointer_vector;
            std::queue<int32_t> free_objectID_queue;
            int32_t number_of_objects;
    };
}

#endif
