#ifndef __ANY_VALUE_HPP_INCLUDED
#define __ANY_VALUE_HPP_INCLUDED

#include "spherical_coordinates_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    class Entity;
    class Universe;
    class Scene;
    class Shader;
    class Material;
    class Species;
    class Object;
    class VectorFont;
    class Glyph;
    class Text3D;
    class Symbiosis;
    class Font2D;
}

namespace console
{
    class Console;
}

namespace datatypes
{
    enum datatype
    {
        UNKNOWN,
        BOOL,
        CHAR,
        FLOAT,
        DOUBLE,
        INT32_T,
        UINT32_T,
        BOOL_POINTER,
        FLOAT_POINTER,
        DOUBLE_POINTER,
        INT32_T_POINTER,
        UINT32_T_POINTER,
        UNIVERSE_POINTER,
        SCENE_POINTER,
        SHADER_POINTER,
        MATERIAL_POINTER,
        SPECIES_POINTER,
        OBJECT_POINTER,
        VECTORFONT_POINTER,
        GLYPH_POINTER,
        TEXT3D_POINTER,
        SYMBIOSIS_POINTER,
        TEXT2D_POINTER,
        CONSOLE_POINTER,
        SPHERICAL_COORDINATES_STRUCT_POINTER,
        GLM_VEC3_POINTER
    };

    typedef class AnyValue
    {
        public:
            std::string get_datatype();
            std::string get_string();
            ontology::Entity* get_entity_pointer();
            bool set_value(const std::string value_string);

            // copy constructor.
            AnyValue(const datatypes::AnyValue& original);

            AnyValue(const std::string type, const std::string value_string);
            AnyValue();
            AnyValue(const bool bool_value);
            AnyValue(const char char_value);
            AnyValue(const float float_value);
            AnyValue(const double double_value);
            AnyValue(const int32_t int32_t_value);
            AnyValue(const uint32_t uint32_t_value);
            AnyValue(bool* const bool_pointer);
            AnyValue(float* const float_pointer);
            AnyValue(double* const double_pointer);
            AnyValue(int32_t* const int32_t_pointer);
            AnyValue(uint32_t* const uint32_t_pointer);
            AnyValue(ontology::Universe* const universe_pointer);
            AnyValue(ontology::Scene* const scene_pointer);
            AnyValue(ontology::Shader* const shader_pointer);
            AnyValue(ontology::Material* const material_pointer);
            AnyValue(ontology::Species* const species_pointer);
            AnyValue(ontology::Object* const object_pointer);
            AnyValue(ontology::VectorFont* const vector_font_pointer);
            AnyValue(ontology::Glyph* const glyph_pointer);
            AnyValue(ontology::Text3D* const text3D_pointer);
            AnyValue(ontology::Symbiosis* const symbiosis_pointer);
            AnyValue(ontology::Font2D* const font2D_pointer);
            AnyValue(console::Console* const console_pointer);
            AnyValue(SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer);
            AnyValue(glm::vec3* const glm_vec3_pointer);

            AnyValue(const std::string type, const bool bool_value);
            AnyValue(const std::string type, const char char_value);
            AnyValue(const std::string type, const float float_value);
            AnyValue(const std::string type, const double double_value);
            AnyValue(const std::string type, const int32_t int32_t_value);
            AnyValue(const std::string type, const uint32_t uint32_t_value);
            AnyValue(const std::string type, bool* const bool_pointer);
            AnyValue(const std::string type, float* const float_pointer);
            AnyValue(const std::string type, double* const double_pointer);
            AnyValue(const std::string type, int32_t* const int32_t_pointer);
            AnyValue(const std::string type, uint32_t* const uint32_t_pointer);
            AnyValue(const std::string type, ontology::Universe* const universe_pointer);
            AnyValue(const std::string type, ontology::Scene* const scene_pointer);
            AnyValue(const std::string type, ontology::Shader* const shader_pointer);
            AnyValue(const std::string type, ontology::Material* const material_pointer);
            AnyValue(const std::string type, ontology::Species* const species_pointer);
            AnyValue(const std::string type, ontology::Object* const object_pointer);
            AnyValue(const std::string type, ontology::VectorFont* const vector_font_pointer);
            AnyValue(const std::string type, ontology::Glyph* const glyph_pointer);
            AnyValue(const std::string type, ontology::Text3D* const text3D_pointer);
            AnyValue(const std::string type, ontology::Symbiosis* const symbiosis_pointer);
            AnyValue(const std::string type, ontology::Font2D* const font2D_pointer);
            AnyValue(const std::string type, console::Console* const console_pointer);
            AnyValue(const std::string type, SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer);
            AnyValue(const std::string type, glm::vec3* const glm_vec3_pointer);

            int type;
            bool bool_value;
            char char_value;
            float float_value;
            double double_value;
            int32_t int32_t_value;
            uint32_t uint32_t_value;
            bool* bool_pointer;
            float* float_pointer;
            double* double_pointer;
            int32_t* int32_t_pointer;
            uint32_t* uint32_t_pointer;
            ontology::Universe* universe_pointer;
            ontology::Scene* scene_pointer;
            ontology::Shader* shader_pointer;
            ontology::Material* material_pointer;
            ontology::Species* species_pointer;
            ontology::Object* object_pointer;
            ontology::VectorFont* vector_font_pointer;
            ontology::Glyph* glyph_pointer;
            ontology::Text3D* text3D_pointer;
            ontology::Symbiosis* symbiosis_pointer;
            ontology::Font2D* font2D_pointer;
            console::Console* console_pointer;
            SphericalCoordinatesStruct* spherical_coordinates_struct_pointer;
            glm::vec3* glm_vec3_pointer;

        private:
            void set_default_values();
    } AnyValue;
}

#endif
