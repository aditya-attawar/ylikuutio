#include "glyph_object_creation.hpp"
#include "entity_factory.hpp"
#include "universe.hpp"
#include "vector_font.hpp"
#include "text3D.hpp"
#include "object.hpp"
#include "object_struct.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Glyph;

        void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* const text3D)
        {
            const char* text_pointer = text_string.c_str();

            while (*text_pointer != '\0')
            {
                int32_t unicode_value = yli::string::extract_unicode_value_from_string(text_pointer);
                yli::ontology::Glyph* glyph_pointer = text3D->parent->get_glyph_pointer(unicode_value);

                if (glyph_pointer == nullptr)
                {
                    // `nullptr`, so skip this character.
                    std::cerr << "Error: no matching Glyph found for unicode_value 0x" << std::hex << unicode_value << std::dec << "\n";
                    continue;
                }

                std::cout << "Creating the glyph Object for unicode_value 0x" << std::hex << unicode_value << std::dec << "\n";

                ObjectStruct object_struct;
                object_struct.glyph = glyph_pointer;
                object_struct.text3D_parent = text3D;
                object_struct.original_scale_vector = text3D->original_scale_vector;
                object_struct.rotate_angle = text3D->rotate_angle;
                object_struct.is_character = true;
                object_struct.cartesian_coordinates = text3D->cartesian_coordinates; // TODO: adjust this as needed.
                object_struct.rotate_vector = text3D->rotate_vector;

                yli::ontology::EntityFactory* const entity_factory = text3D->universe->get_entity_factory();

                if (entity_factory != nullptr)
                {
                    entity_factory->create_Object(object_struct);
                }
            }

            // TODO: Add support for Unicode strings.

            // TODO: go through `text_string`.

            // TODO: extract Unicode.
            //
            // TODO: If the Unicode exists in the hash map, create the corresponding glyph `Object`.
            //       If not, continue from the next Unicode of `text_string`.
        }
    }
}
