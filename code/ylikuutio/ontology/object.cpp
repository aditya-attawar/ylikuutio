#include "object.hpp"
#include "glyph.hpp"
#include "species.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace ontology
{
    void Object::bind_to_parent()
    {
        // get `childID` from the `Species` or the `Glyph` and set pointer to this `Object`.

        if (this->is_character)
        {
            ontology::Text3D* parent_pointer;
            parent_pointer = this->text3D_parent_pointer;
            // for ontological hierarchy (rendering hierarchy does not use `childID`).
            // get `childID` from the `Glyph` and set pointer to this `Object`.
            hierarchy::bind_child_to_parent<ontology::Object*>(this, parent_pointer->object_pointer_vector, parent_pointer->free_objectID_queue);
        }
        else
        {
            ontology::Species* parent_pointer;
            parent_pointer = this->species_parent_pointer;
            // for ontological hierarchy (rendering hierarchy does not use `childID`).
            // get `childID` from the `Species` and set pointer to this `Object`.
            hierarchy::bind_child_to_parent<ontology::Object*>(this, parent_pointer->object_pointer_vector, parent_pointer->free_objectID_queue);
        }
    }

    Object::Object(ObjectStruct object_struct)
    {
        // constructor.
        this->coordinate_vector     = object_struct.coordinate_vector;
        this->original_scale_vector = object_struct.original_scale_vector;
        this->rotate_angle          = object_struct.rotate_angle;
        this->rotate_vector         = object_struct.rotate_vector;
        this->translate_vector      = object_struct.translate_vector;
        this->has_entered           = false;
        this->is_character          = object_struct.is_character;

        if (this->is_character)
        {
            this->species_parent_pointer = nullptr;
            this->glyph_parent_pointer   = object_struct.glyph_parent_pointer;
            this->text3D_parent_pointer  = object_struct.text3D_parent_pointer;
        }
        else
        {
            this->species_parent_pointer = object_struct.species_parent_pointer;
            this->glyph_parent_pointer   = nullptr;
        }

        // get `childID` from the `Species` or the `Glyph` and set pointer to this `Object`.
        this->bind_to_parent();

        bool model_loading_result = false;
    }

    Object::~Object()
    {
        // destructor.

        // set pointer to this object to nullptr.
        if (this->is_character)
        {
            std::string unicode_string = this->glyph_parent_pointer->unicode_char_pointer;
            std::cout << "Object with childID " << std::dec << this->childID << " (Unicode: \"" << unicode_string << "\") will be destroyed.\n";
            this->text3D_parent_pointer->set_object_pointer(this->childID, nullptr);
        }
        else
        {
            std::cout << "Object with childID " << std::dec << this->childID << " will be destroyed.\n";
            this->species_parent_pointer->set_object_pointer(this->childID, nullptr);
        }
    }

    void Object::act()
    {
        // act according to this game/simulation object's programming.
    }

    void Object::render()
    {
        ontology::Shader* shader_pointer;

        if (this->is_character)
        {
            shader_pointer = this->glyph_parent_pointer->parent_pointer->parent_pointer->parent_pointer;
            ontology::render_this_object<ontology::Glyph*>(this, shader_pointer);
        }
        else
        {
            shader_pointer = this->species_parent_pointer->parent_pointer->parent_pointer;
            ontology::render_this_object<ontology::Species*>(this, shader_pointer);
        }
    }

    void Object::bind_to_new_parent(void* new_parent_pointer)
    {
        // this method sets pointer to this `Object` to nullptr, sets `parent_pointer` according to the input,
        // and requests a new `childID` from the new `Species` or from the new `Glyph`.

        if (this->is_character)
        {
            ontology::Glyph* parent_pointer;
            parent_pointer = this->glyph_parent_pointer;
            // set pointer to this child to nullptr in the old parent.
            ontology::Object* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(this->childID, dummy_child_pointer, glyph_parent_pointer->object_pointer_vector, glyph_parent_pointer->free_objectID_queue);
            // set the new parent pointer.
            this->glyph_parent_pointer = static_cast<ontology::Glyph*>(new_parent_pointer);
            // bind to the new parent.
            this->bind_to_parent();
        }
        else
        {
            ontology::Species* parent_pointer;
            parent_pointer = this->species_parent_pointer;
            // set pointer to this child to nullptr in the old parent.
            ontology::Object* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(this->childID, dummy_child_pointer, species_parent_pointer->object_pointer_vector, species_parent_pointer->free_objectID_queue);
            // set the new parent pointer.
            this->species_parent_pointer = static_cast<ontology::Species*>(new_parent_pointer);
            // bind to the new parent.
            this->bind_to_parent();
        }
    }

    // Public callbacks (to be called from AI scripts written in Chibi-Scheme).

    void Object::set_dest(ontology::Object* object, float x, float y, float z)
    {
        // Set target towards which to move.
        object->dest_vector = glm::vec3(x, y, z);
    }

    float Object::get_x(ontology::Object* object)
    {
        // Get x coordinate of `object`.
        return object->coordinate_vector.x;
    }

    float Object::get_y(ontology::Object* object)
    {
        // Get y coordinate of `object`.
        return object->coordinate_vector.x;
    }

    float Object::get_z(ontology::Object* object)
    {
        // Get z coordinate of `object`.
        return object->coordinate_vector.x;
    }

    float Object::get_dest_x(ontology::Object* object)
    {
        // Get x destination coordinate of `object`.
        return object->dest_vector.x;
    }

    float Object::get_dest_y(ontology::Object* object)
    {
        // Get y destination coordinate of `object`.
        return object->dest_vector.x;
    }

    float Object::get_dest_z(ontology::Object* object)
    {
        // Get z destination coordinate of `object`.
        return object->dest_vector.x;
    }

    // Public callbacks end here.
}
