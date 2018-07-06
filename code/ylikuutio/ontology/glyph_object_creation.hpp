#ifndef __CREATE_GLYPH_OBJECTS_HPP_INCLUDED
#define __CREATE_GLYPH_OBJECTS_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ylikuutio
{
    namespace ontology
    {
        class Text3D;

        void create_glyph_objects(const std::string& text_string, ylikuutio::ontology::Text3D* const text3D);
    }
}

#endif
