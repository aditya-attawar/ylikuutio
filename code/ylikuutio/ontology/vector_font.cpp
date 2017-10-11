#include "vector_font.hpp"
#include "text3D.hpp"
#include "render_templates.hpp"
#include "vector_font_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <stdint.h>      // uint32_t etc.

namespace ontology
{
    class Text3D;
    class Glyph;

    void VectorFont::bind_to_parent()
    {
        // get `childID` from `Material` and set pointer to this `VectorFont`.
        hierarchy::bind_child_to_parent<ontology::VectorFont*>(this, this->parent_pointer->vector_font_pointer_vector, this->parent_pointer->free_vector_fontID_queue, &this->parent_pointer->number_of_vector_fonts);
    }

    // this method returns a pointer to `Glyph` that matches the given `unicode_value`,
    // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
    ontology::Glyph* VectorFont::get_glyph_pointer(int32_t unicode_value)
    {
        if (this->unicode_glyph_map.count(unicode_value) == 1)
        {
            return this->unicode_glyph_map[unicode_value];
        }

        // No matching `Glyph` found!
        return nullptr;
    }

    VectorFont::~VectorFont()
    {
        // destructor.
        // Destroying a `VectorFont` destroys also all `Text3D` entities, and after that all `Glyph` entities.
        std::cout << "Font with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all 3D texts (`Text3D`) of this font.
        std::cout << "All 3D texts of this font will be destroyed.\n";
        hierarchy::delete_children<ontology::Text3D*>(this->text3D_pointer_vector, &this->number_of_text3Ds);

        // destroy all `Glyph`s of this font.
        std::cout << "All glyphs of this font will be destroyed.\n";
        hierarchy::delete_children<ontology::Glyph*>(this->glyph_pointer_vector, &this->number_of_glyphs);

        // set pointer to this `VectorFont` to nullptr.
        this->parent_pointer->set_vector_font_pointer(this->childID, nullptr);
    }

    void VectorFont::render()
    {
        this->prerender();

        // render this `VectorFont` by calling `render()` function of each `Glyph`.
        ontology::render_children<ontology::Glyph*>(this->glyph_pointer_vector);

        this->postrender();
    }

    ontology::Entity* VectorFont::get_parent()
    {
        return this->parent_pointer;
    }

    int32_t VectorFont::get_number_of_children()
    {
        return this->number_of_glyphs + this->number_of_text3Ds;
    }

    int32_t VectorFont::get_number_of_descendants()
    {
        return -1;
    }

    void VectorFont::set_glyph_pointer(const int32_t childID, ontology::Glyph* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->glyph_pointer_vector, this->free_glyphID_queue, &this->number_of_glyphs);
    }

    void VectorFont::set_text3D_pointer(const int32_t childID, ontology::Text3D* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->text3D_pointer_vector, this->free_text3D_ID_queue, &this->number_of_text3Ds);
    }

    void VectorFont::bind_to_new_parent(ontology::Material* const new_material_pointer)
    {
        hierarchy::bind_child_to_new_parent<ontology::VectorFont*, ontology::Material*>(this, new_material_pointer, this->parent_pointer->vector_font_pointer_vector, this->parent_pointer->free_vector_fontID_queue, &this->parent_pointer->number_of_vector_fonts);
    }

    void VectorFont::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }
}
