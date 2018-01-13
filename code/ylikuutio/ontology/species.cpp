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

namespace ontology
{
    void Species::bind_to_parent()
    {
        // get `childID` from `Material` and set pointer to this `Species`.
        this->parent->bind_species(this);
    }

    Species::~Species()
    {
        // destructor.
        std::cout << "Species with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all objects of this species.
        std::cout << "All objects of this species will be destroyed.\n";
        hierarchy::delete_children<ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

        // Cleanup VBO, shader and texture.
        glDeleteBuffers(1, &this->vertexbuffer);
        glDeleteBuffers(1, &this->uvbuffer);
        glDeleteBuffers(1, &this->normalbuffer);
        glDeleteBuffers(1, &this->elementbuffer);

        // set pointer to this species to nullptr.
        this->parent->set_species_pointer(this->childID, nullptr);
    }

    void Species::render()
    {
        this->prerender();

        // render this `Species`.
        ontology::render_species_or_glyph<ontology::Species*>(this);

        this->postrender();
    }

    ontology::Entity* Species::get_parent() const
    {
        return this->parent;
    }

    void Species::set_object_pointer(const int32_t childID, ontology::Object* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
    }

    void Species::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }

    int32_t Species::get_image_width()
    {
        return this->image_width;
    }

    int32_t Species::get_image_height()
    {
        return this->image_height;
    }

    void Species::bind_to_new_parent(ontology::Material* const new_material_pointer)
    {
        // unbind from the old parent `Material`.
        this->parent->unbind_species(this->childID);

        // get `childID` from `Material` and set pointer to this `Species`.
        this->parent = new_material_pointer;
        this->parent->bind_species(this);
    }
}
