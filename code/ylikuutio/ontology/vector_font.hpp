#ifndef __FONT_HPP_INCLUDED
#define __FONT_HPP_INCLUDED

#include "entity.hpp"
#include "glyph.hpp"
#include "material.hpp"
#include "glyph_struct.hpp"
#include "vector_font_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/loaders/font_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <cstring>       // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream>      // std::cout, std::cin, std::cerr
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace ontology
{
    class Material;
    class Text3D;

    class VectorFont: public ontology::Entity
    {
        public:
            // constructor.
            // TODO: `VectorFont` constructor also creates each `Glyph` and binds them to the `VectorFont`.
            VectorFont(ontology::Universe* const universe, const VectorFontStruct& vector_font_struct)
                : Entity(universe)
            {
                // constructor.
                this->font_file_format      = vector_font_struct.font_file_format;
                this->font_filename         = vector_font_struct.font_filename;
                this->vertex_scaling_factor = vector_font_struct.vertex_scaling_factor;
                this->parent        = vector_font_struct.parent;

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
                        glyph_struct.universe = universe;
                        glyph_struct.shader_pointer = static_cast<ontology::Shader*>(this->parent->get_parent());
                        glyph_struct.parent = this;

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
                this->type = "ontology::VectorFont*";
            }

            // destructor.
            // Destroying a `VectorFont` destroys also all `Text3D` entities, and after that all `Glyph` entities.
            virtual ~VectorFont();

            void bind_glyph(ontology::Glyph* glyph);
            void bind_text3D(ontology::Text3D* text3D);

            // this method sets `Glyph` pointer.
            void set_glyph_pointer(const int32_t childID, ontology::Glyph* const child_pointer);

            // this method sets `Text3D` pointer.
            void set_text3D_pointer(const int32_t childID, ontology::Text3D* const child_pointer);

            // this method sets pointer to this species to nullptr, sets `parent` according to the input, and requests a new `childID` from the new material.
            void bind_to_new_parent(ontology::Material* const new_material_pointer);

            void set_name(const std::string& name);

            // this method returns a pointer to `Glyph` that matches the given `unicode_value`,
            // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
            ontology::Glyph* get_glyph_pointer(int32_t unicode_value);

            // The rest fields are created in the constructor.

            ontology::Material* parent; // pointer to `Material`.

            template<class T1>
                friend void render_children(const std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            // this method renders all `Glyph`s of this `VectorFont`.
            void render();

            ontology::Entity* get_parent() const override;
            int32_t get_number_of_children() const override;
            int32_t get_number_of_descendants() const override;

            std::string font_file_format;         // type of the model file, eg. `"bmp"`.
            std::string font_filename;            // filename of the model file.
            GLfloat vertex_scaling_factor;
            const char* char_font_file_format;
            const char* char_font_filename;

            std::vector<std::vector<std::vector<glm::vec2>>> glyph_vertex_data;
            std::vector<std::vector<glm::vec2>> glyph_UV_data;
            std::vector<std::vector<glm::vec2>> glyph_normal_data;
            std::vector<std::string> glyph_names;
            std::vector<std::string> unicode_strings;

            std::vector<ontology::Glyph*> glyph_pointer_vector;
            std::vector<ontology::Text3D*> text3D_pointer_vector;
            std::queue<int32_t> free_glyphID_queue;
            std::queue<int32_t> free_text3D_ID_queue;
            int32_t number_of_glyphs;
            int32_t number_of_text3Ds;

            std::unordered_map<int32_t, ontology::Glyph*> unicode_glyph_map;
    };
}

#endif
