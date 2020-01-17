// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "vector_font.hpp"
#include "text3D.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "vector_font_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <stdint.h>      // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        class Text3D;
        class Glyph;

        void VectorFont::bind_Glyph(yli::ontology::Glyph* const glyph)
        {
            // Get `childID` from `VectorFont` and set pointer to `glyph`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Glyph*>(
                    glyph,
                    this->glyph_pointer_vector,
                    this->free_glyphID_queue,
                    this->number_of_glyphs);
        }

        void VectorFont::bind_Text3D(yli::ontology::Text3D* const text3D)
        {
            // Get `childID` from `VectorFont` and set pointer to `text3D`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Text3D*>(
                    text3D,
                    this->text3D_pointer_vector,
                    this->free_text3D_ID_queue,
                    this->number_of_text3Ds);
        }

        void VectorFont::unbind_Text3D(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::Text3D*>(
                    childID,
                    this->text3D_pointer_vector,
                    this->free_text3D_ID_queue,
                    this->number_of_text3Ds);
        }

        void VectorFont::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::bind_to_parent`: `material` is `nullptr`!\n";
                return;
            }

            // Get `childID` from the `Material` and set pointer to this `VectorFont`.
            material->bind_VectorFont(this);
        }

        void VectorFont::bind_to_new_parent(yli::ontology::Material* const new_parent)
        {
            // This method sets pointer to this `VectorFont` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Material`.
            //
            // Requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::bind_to_new_parent`: `material` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // Unbind from the old parent `Material`.
            material->unbind_VectorFont(this->childID);

            // Get `childID` from `Material` and set pointer to this `VectorFont`.
            this->parent = new_parent;
            this->parent->bind_VectorFont(this);
        }

        // This method returns a pointer to `Glyph` that matches the given `unicode_value`,
        // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
        yli::ontology::Glyph* VectorFont::get_glyph_pointer(const int32_t unicode_value) const
        {
            if (this->unicode_glyph_map.count(unicode_value) == 1)
            {
                return this->unicode_glyph_map.at(unicode_value);
            }

            // No matching `Glyph` found!
            return nullptr;
        }

        VectorFont::~VectorFont()
        {
            // destructor.

            // Destroying a `VectorFont` destroys also all `Text3D` entities, and after that all `Glyph` entities.
            std::cout << "`VectorFont` with childID " << std::dec << this->childID << " will be destroyed.\n";

            // Destroy all 3D texts (`Text3D`) of this font.
            std::cout << "All `Text3D`s of this `VectorFont` will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Text3D*>(this->text3D_pointer_vector, this->number_of_text3Ds);

            // Destroy all `Glyph`s of this font.
            std::cout << "All `Glyph`s of this `VectorFont` will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Glyph*>(this->glyph_pointer_vector, this->number_of_glyphs);

            // Requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `VectorFont::~VectorFont`: `material` is `nullptr`!\n";
                return;
            }

            // Set pointer to this `VectorFont` to `nullptr`.
            material->unbind_VectorFont(this->childID);
        }

        void VectorFont::render()
        {
            if (this->should_be_rendered)
            {
                this->prerender();

                // Render this `VectorFont` by calling `render()` function of each `Glyph`.
                yli::ontology::render_children<yli::ontology::Glyph*>(this->glyph_pointer_vector);

                this->postrender();
            }
        }

        yli::ontology::Entity* VectorFont::get_parent() const
        {
            return this->parent;
        }

        std::size_t VectorFont::get_number_of_children() const
        {
            return this->number_of_glyphs + this->number_of_text3Ds;
        }

        std::size_t VectorFont::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->glyph_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->text3D_pointer_vector);
        }

        void VectorFont::set_glyph_pointer(const std::size_t childID, yli::ontology::Glyph* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->glyph_pointer_vector, this->free_glyphID_queue, this->number_of_glyphs);
        }
    }
}
