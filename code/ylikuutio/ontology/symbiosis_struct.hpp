#ifndef __SYMBIOSIS_STRUCT_HPP_INCLUDED
#define __SYMBIOSIS_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Shader;
}

typedef struct SymbiosisStruct
{
    SymbiosisStruct()
        : parent(nullptr), triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    ontology::Shader* parent; // pointer to the `Scene` object.

    std::string model_file_format;    // type of the symbiosis model file.
    std::string model_filename;       // filename of the symbiosis model file.
    std::string triangulation_type;   // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
} SymbiosisStruct;

#endif
