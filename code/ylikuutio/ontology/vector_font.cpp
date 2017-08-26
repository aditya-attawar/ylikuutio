#include "vector_font.hpp"
#include "glyph.hpp"
#include "render_templates.hpp"
#include "vector_font_struct.hpp"
#include "glyph_struct.hpp"
#include "code/ylikuutio/loaders/font_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <cstring>       // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream>      // std::cout, std::cin, std::cerr
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map

namespace ontology
{
    class Text3D;

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

    VectorFont::VectorFont(const VectorFontStruct vector_font_struct)
    {
        // constructor.
        this->font_file_format      = vector_font_struct.font_file_format;
        this->font_filename         = vector_font_struct.font_filename;
        this->vertex_scaling_factor = vector_font_struct.vertex_scaling_factor;
        this->parent_pointer        = vector_font_struct.parent_pointer;
        this->universe_pointer      = this->parent_pointer->universe_pointer;

        this->char_font_file_format = this->font_file_format.c_str();
        this->char_font_filename    = this->font_filename.c_str();

        this->number_of_glyphs = 0;
        this->number_of_text3Ds = 0;

        // get `childID` from `Material` and set pointer to this `VectorFont`.
        this->bind_to_parent();

        bool font_loading_result = false;

        if ((std::strcmp(this->char_font_file_format, "svg") == 0) || (std::strcmp(this->char_font_file_format, "SVG") == 0))
        {
            font_loading_result = loaders::load_SVG_font(
                    this->font_filename,
                    this->glyph_vertex_data,
                    this->glyph_names,
                    this->unicode_strings);
        }

        if (font_loading_result)
        {
            // OK, `VectorFont` loading was successful.
            // Create each `Glyph` and bind them to `VectorFont`.

            std::cout << "Number of glyphs to be created: " << this->glyph_vertex_data.size() << "\n";

            for (uint32_t glyph_i = 0; glyph_i < this->glyph_vertex_data.size(); glyph_i++)
            {
                const char* unicode_char_pointer = this->unicode_strings.at(glyph_i).c_str();
                const char* temp_unicode_char_pointer = unicode_char_pointer;

                int32_t unicode_value = string::extract_unicode_value_from_string(temp_unicode_char_pointer);
                if (unicode_value >= 0xd800 && unicode_value <= 0xdfff)
                {
                    // invalid Unicode, skip to next `Glyph`.
                    std::cerr << std::dec << "Error: invalid Unicode: " << unicode_value << "\n";
                    continue;
                }

                GlyphStruct glyph_struct;
                glyph_struct.glyph_vertex_data = &this->glyph_vertex_data.at(glyph_i);
                glyph_struct.glyph_name_pointer = this->glyph_names.at(glyph_i).c_str();
                glyph_struct.unicode_char_pointer = unicode_char_pointer;
                glyph_struct.parent_pointer = this;

                std::string glyph_name_string = glyph_struct.glyph_name_pointer;
                std::string unicode_string = glyph_struct.unicode_char_pointer;
                std::cout << "Creating Glyph \"" << glyph_name_string << "\", Unicode: \"" << unicode_string << "\"\n";
                ontology::Glyph* glyph = new ontology::Glyph(glyph_struct);

                // so that each `Glyph` can be referred to,
                // we need a hash map that points from Unicode string to `Glyph`.
                this->unicode_glyph_map[unicode_value] = glyph;
            }
        }

        this->child_vector_pointers_vector.push_back(&this->glyph_pointer_vector);
        this->child_vector_pointers_vector.push_back(&this->text3D_pointer_vector);
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

    int32_t VectorFont::get_number_of_children()
    {
        return this->number_of_glyphs + this->number_of_text3Ds;
    }

    int32_t VectorFont::get_number_of_descendants()
    {
        return -1;
    }

    void VectorFont::set_glyph_pointer(const uint32_t childID, ontology::Glyph* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->glyph_pointer_vector, this->free_glyphID_queue, &this->number_of_glyphs);
    }

    void VectorFont::set_text3D_pointer(const uint32_t childID, ontology::Text3D* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->text3D_pointer_vector, this->free_text3D_ID_queue, &this->number_of_text3Ds);
    }

    void VectorFont::bind_to_new_parent(ontology::Material* const new_material_pointer)
    {
        hierarchy::bind_child_to_new_parent<ontology::VectorFont*, ontology::Material*>(this, new_material_pointer, this->parent_pointer->vector_font_pointer_vector, this->parent_pointer->free_vector_fontID_queue, &this->parent_pointer->number_of_vector_fonts);
    }

    void VectorFont::set_name(const std::string name)
    {
        ontology::set_name(name, this);
    }
}