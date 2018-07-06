#include "species.hpp"
#include "vboindexer.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "object.hpp"
#include "species_or_glyph.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace ylikuutio
{
    namespace ontology
    {
        void Species::bind_to_parent()
        {
            // get `childID` from `Material` and set pointer to this `Species`.
            this->material_parent->bind_species(this);
        }

        void Species::bind_to_new_parent(ylikuutio::ontology::Material* const new_material_pointer)
        {
            // unbind from the old parent `Material`.
            this->material_parent->unbind_species(this->childID);

            // get `childID` from `Material` and set pointer to this `Species`.
            this->material_parent = new_material_pointer;
            this->material_parent->bind_species(this);
        }

        Species::~Species()
        {
            if (!this->is_symbiont_species)
            {
                // destructor.
                std::cout << "Species with childID " << std::dec << this->childID << " will be destroyed.\n";

                // destroy all objects of this species.
                std::cout << "All objects of this species will be destroyed.\n";
                hierarchy::delete_children<ylikuutio::ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

                // Cleanup VBO, shader and texture.
                glDeleteBuffers(1, &this->vertexbuffer);
                glDeleteBuffers(1, &this->uvbuffer);
                glDeleteBuffers(1, &this->normalbuffer);
                glDeleteBuffers(1, &this->elementbuffer);

                // set pointer to this species to nullptr.
                this->material_parent->set_species_pointer(this->childID, nullptr);
            }
        }

        void Species::render()
        {
            this->prerender();

            // render this `Species`.
            ylikuutio::ontology::render_species_or_glyph<ylikuutio::ontology::Species*>(this);

            this->postrender();
        }

        ylikuutio::ontology::Entity* Species::get_parent() const
        {
            if (this->is_symbiont_species)
            {
                return nullptr;
            }
            return this->material_parent;
        }

        void Species::set_object_pointer(const int32_t childID, ylikuutio::ontology::Object* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
        }

        int32_t Species::get_image_width() const
        {
            return this->image_width;
        }

        const std::string& Species::get_model_file_format() const
        {
            return this->model_file_format;
        }

        int32_t Species::get_image_height() const
        {
            return this->image_height;
        }
    }
}
