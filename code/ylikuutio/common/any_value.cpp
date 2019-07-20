// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#include "any_value.hpp"
#include "any_struct.hpp"
#include "spherical_coordinates_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::fixed, std::ios
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace console
    {
        class Console;
    }

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
    }

    namespace common
    {
        std::string AnyValue::get_datatype() const
        {
            std::string datatype_string;

            switch (this->type)
            {
                case (UNKNOWN):
                    return "unknown";
                case (ANY_STRUCT_SHARED_PTR):
                    return "std::shared_ptr<yli::common::AnyStruct>";
                case (BOOL):
                    return "bool";
                case (CHAR):
                    return "char";
                case (FLOAT):
                    return "float";
                case (DOUBLE):
                    return "double";
                case (INT32_T):
                    return "int32_t";
                case (UINT32_T):
                    return "uint32_t";
                case (BOOL_POINTER):
                    return "bool*";
                case (FLOAT_POINTER):
                    return "float*";
                case (DOUBLE_POINTER):
                    return "double*";
                case (INT32_T_POINTER):
                    return "int32_t*";
                case (UINT32_T_POINTER):
                    return "uint32_t*";
                case (UNIVERSE_POINTER):
                    return "yli::ontology::Universe*";
                case (SCENE_POINTER):
                    return "yli::ontology::Scene*";
                case (SHADER_POINTER):
                    return "yli::ontology::Shader*";
                case (MATERIAL_POINTER):
                    return "yli::ontology::Material*";
                case (SPECIES_POINTER):
                    return "yli::ontology::Species*";
                case (OBJECT_POINTER):
                    return "yli::ontology::Object*";
                case (VECTORFONT_POINTER):
                    return "yli::ontology::VectorFont*";
                case (GLYPH_POINTER):
                    return "yli::ontology::Glyph*";
                case (TEXT3D_POINTER):
                    return "yli::ontology::Text3D*";
                case (TEXT2D_POINTER):
                    return "yli::ontology::Text2D*";
                case (CONSOLE_POINTER):
                    return "yli::console::Console*";
                case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                    return "yli::common::SphericalCoordinatesStruct*";
                case (STD_STRING_POINTER):
                    return "std::string*";
                case (STD_VECTOR_INT8_T_SHARED_PTR):
                    return "std::shared_ptr<std::vector<int8_t>>";
                case (STD_VECTOR_UINT8_T_SHARED_PTR):
                    return "std::shared_ptr<std::vector<uint8_t>>";
                case (STD_VECTOR_INT16_T_SHARED_PTR):
                    return "std::shared_ptr<std::vector<int16_t>>";
                case (STD_VECTOR_UINT16_T_SHARED_PTR):
                    return "std::shared_ptr<std::vector<uint16_t>>";
                case (STD_VECTOR_INT32_T_SHARED_PTR):
                    return "std::shared_ptr<std::vector<int32_t>>";
                case (STD_VECTOR_UINT32_T_SHARED_PTR):
                    return "std::shared_ptr<std::vector<uint32_t>>";
                case (STD_VECTOR_FLOAT_SHARED_PTR):
                    return "std::shared_ptr<std::vector<float>>";
                case (GLM_VEC3_POINTER):
                    return "glm::vec3*";
                case (GLM_VEC4_POINTER):
                    return "glm::vec4*";
                default:
                    return "TODO: define string for this datatype!";
            }
        }

        std::string AnyValue::get_string() const
        {
            std::string any_value_string;
            std::stringstream any_value_stringstream;
            any_value_stringstream.precision(6); // 6 decimals in floating point output.

            switch (this->type)
            {
                case (UNKNOWN):
                    any_value_stringstream << "unknown";
                    break;
                case (ANY_STRUCT_SHARED_PTR):
                    if (this->any_struct_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << std::hex << this->any_struct_shared_ptr.get() << std::dec;
                    }
                    break;
                case (BOOL):
                    any_value_stringstream << (this->bool_value ? "true" : "false");
                    break;
                case (CHAR):
                    any_value_stringstream << this->char_value;
                    break;
                case (FLOAT):
                    any_value_stringstream << std::fixed << this->float_value;
                    break;
                case (DOUBLE):
                    any_value_stringstream << std::fixed << this->double_value;
                    break;
                case (INT32_T):
                    // in Linux `int` is 32 bits, `long` is 64 bits, `long long` is also 64 bits.
                    // in Windows `int` is 32 bits, `long` is also 32 bits, `long long` is 64 bits.
                    any_value_stringstream << this->int32_t_value;
                    break;
                case (UINT32_T):

                    // in Linux `int` is 32 bits, `long` is 64 bits, `long long` is also 64 bits.
                    // in Windows `int` is 32 bits, `long` is also 32 bits, `long long` is 64 bits.
                    any_value_stringstream << this->uint32_t_value;
                    break;
                case (BOOL_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->bool_pointer << std::dec;
                    break;
                case (FLOAT_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->float_pointer << std::dec;
                    break;
                case (DOUBLE_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->double_pointer << std::dec;
                    break;
                case (INT32_T_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->int32_t_pointer << std::dec;
                    break;
                case (UINT32_T_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->uint32_t_pointer << std::dec;
                    break;
                case (UNIVERSE_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->universe << std::dec;
                    break;
                case (SCENE_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->scene_pointer << std::dec;
                    break;
                case (SHADER_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->shader_pointer << std::dec;
                    break;
                case (MATERIAL_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->material_pointer << std::dec;
                    break;
                case (SPECIES_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->species_pointer << std::dec;
                    break;
                case (OBJECT_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->object_pointer << std::dec;
                    break;
                case (VECTORFONT_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->vector_font_pointer << std::dec;
                    break;
                case (GLYPH_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->glyph_pointer << std::dec;
                    break;
                case (TEXT3D_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->text3D_pointer << std::dec;
                    break;
                case (TEXT2D_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->font2D_pointer << std::dec;
                    break;
                case (CONSOLE_POINTER):
                    any_value_stringstream << std::hex << (uint64_t) this->console_pointer << std::dec;
                    break;
                case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                    if (this->spherical_coordinates_struct_pointer == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "{ " << this->spherical_coordinates_struct_pointer->rho
                            << ", " << this->spherical_coordinates_struct_pointer->theta
                            << ", " << this->spherical_coordinates_struct_pointer->phi
                            << " }";
                    }
                    break;
                case (STD_STRING_POINTER):
                    if (this->std_string_pointer == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << *this->std_string_pointer;
                    }
                    break;
                case (STD_VECTOR_INT8_T_SHARED_PTR):
                    if (this->std_vector_int8_t_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<int8_t>>";
                    }
                    break;
                case (STD_VECTOR_UINT8_T_SHARED_PTR):
                    if (this->std_vector_uint8_t_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<uint8_t>>";
                    }
                    break;
                case (STD_VECTOR_INT16_T_SHARED_PTR):
                    if (this->std_vector_int16_t_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<int16_t>>";
                    }
                    break;
                case (STD_VECTOR_UINT16_T_SHARED_PTR):
                    if (this->std_vector_uint16_t_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<uint16_t>>";
                    }
                    break;
                case (STD_VECTOR_INT32_T_SHARED_PTR):
                    if (this->std_vector_int32_t_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<int32_t>>";
                    }
                    break;
                case (STD_VECTOR_UINT32_T_SHARED_PTR):
                    if (this->std_vector_uint32_t_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<uint32_t>>";
                    }
                    break;
                case (STD_VECTOR_FLOAT_SHARED_PTR):
                    if (this->std_vector_float_shared_ptr == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "std::shared_ptr<std::vector<float>>";
                    }
                    break;
                case (GLM_VEC3_POINTER):
                    if (this->glm_vec3_pointer == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "{ " << this->glm_vec3_pointer->x
                            << ", " << this->glm_vec3_pointer->y
                            << ", " << this->glm_vec3_pointer->z
                            << " }";
                    }
                    break;
                case (GLM_VEC4_POINTER):
                    if (this->glm_vec4_pointer == nullptr)
                    {
                        any_value_stringstream << "nullptr";
                    }
                    else
                    {
                        any_value_stringstream << "{ " << this->glm_vec4_pointer->x
                            << ", " << this->glm_vec4_pointer->y
                            << ", " << this->glm_vec4_pointer->z
                            << ", " << this->glm_vec4_pointer->w
                            << " }";
                    }
                    break;
                default:
                    return "TODO: define string for this datatype!";
            }

            any_value_string = any_value_stringstream.str();
            return any_value_string;
        }

        yli::ontology::Entity* AnyValue::get_entity_pointer() const
        {
            switch (this->type)
            {
                case (UNIVERSE_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->universe));
                case (SCENE_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->scene_pointer));
                case (SHADER_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->shader_pointer));
                case (MATERIAL_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->material_pointer));
                case (SPECIES_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->species_pointer));
                case (OBJECT_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->object_pointer));
                case (VECTORFONT_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->vector_font_pointer));
                case (GLYPH_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->glyph_pointer));
                case (TEXT3D_POINTER):
                    return static_cast<yli::ontology::Entity*>(static_cast<void*>(this->text3D_pointer));
                default:
                    return nullptr;
            }
        }

        bool AnyValue::set_value(const std::string& value_string)
        {
            std::stringstream value_stringstream;
            void* void_pointer = nullptr;

            switch (this->type)
            {
                case (UNKNOWN):
                    return false;
                case (ANY_STRUCT_SHARED_PTR):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr =
                            std::make_shared<yli::common::AnyStruct>();
                        this->any_struct_shared_ptr = any_struct_shared_ptr;
                        return true;
                    }
                case (BOOL):
                    {
                        if (value_string == "true") // Ylikuutio is case sensitive!
                        {
                            this->bool_value = true;
                            return true;
                        }
                        else if (value_string == "false") // Ylikuutio is case sensitive!
                        {
                            this->bool_value = false;
                            return true;
                        }
                        return false;
                    }
                case (CHAR):
                    {
                        if (value_string.size() == 1)
                        {
                            this->char_value = value_string[0];
                            return true;
                        }
                        return false;
                    }
                case (FLOAT):
                    {
                        if (!yli::string::check_if_float_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> this->float_value;
                        return true;
                    }
                case (DOUBLE):
                    {
                        if (!yli::string::check_if_double_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> this->double_value;
                        return true;
                    }
                case (INT32_T):
                    {
                        if (!yli::string::check_if_signed_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> this->int32_t_value;
                        return true;
                    }
                case (UINT32_T):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> this->uint32_t_value;
                        return true;
                    }
                case (BOOL_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->bool_pointer = static_cast<bool*>(void_pointer);
                        return true;
                    }
                case (FLOAT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->float_pointer = static_cast<float*>(void_pointer);
                        return true;
                    }
                case (DOUBLE_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->double_pointer = static_cast<double*>(void_pointer);
                        return true;
                    }
                case (INT32_T_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->int32_t_pointer = static_cast<int32_t*>(void_pointer);
                        return true;
                    }
                case (UINT32_T_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->uint32_t_pointer = static_cast<uint32_t*>(void_pointer);
                        return true;
                    }
                case (UNIVERSE_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->universe = static_cast<yli::ontology::Universe*>(void_pointer);
                        return true;
                    }
                case (SCENE_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->scene_pointer = static_cast<yli::ontology::Scene*>(void_pointer);
                        return true;
                    }
                case (SHADER_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->shader_pointer = static_cast<yli::ontology::Shader*>(void_pointer);
                        return true;
                    }
                case (MATERIAL_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->material_pointer = static_cast<yli::ontology::Material*>(void_pointer);
                        return true;
                    }
                case (SPECIES_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->species_pointer = static_cast<yli::ontology::Species*>(void_pointer);
                        return true;
                    }
                case (OBJECT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->object_pointer = static_cast<yli::ontology::Object*>(void_pointer);
                        return true;
                    }
                case (VECTORFONT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->vector_font_pointer = static_cast<yli::ontology::VectorFont*>(void_pointer);
                        return true;
                    }
                case (GLYPH_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->glyph_pointer = static_cast<yli::ontology::Glyph*>(void_pointer);
                        return true;
                    }
                case (TEXT3D_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->text3D_pointer = static_cast<yli::ontology::Text3D*>(void_pointer);
                        return true;
                    }
                case (TEXT2D_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->font2D_pointer = static_cast<yli::ontology::Font2D*>(void_pointer);
                        return true;
                    }
                case (CONSOLE_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->console_pointer = static_cast<yli::console::Console*>(void_pointer);
                        return true;
                    }
                case (SPHERICAL_COORDINATES_STRUCT_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->spherical_coordinates_struct_pointer = static_cast<yli::common::SphericalCoordinatesStruct*>(void_pointer);
                        return true;
                    }
                case (GLM_VEC3_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->glm_vec3_pointer = static_cast<glm::vec3*>(void_pointer);
                        return true;
                    }
                case (GLM_VEC4_POINTER):
                    {
                        if (!yli::string::check_if_unsigned_integer_string(value_string))
                        {
                            return false;
                        }

                        value_stringstream << value_string;
                        value_stringstream >> void_pointer;
                        this->glm_vec4_pointer = static_cast<glm::vec4*>(void_pointer);
                        return true;
                    }
                default:
                    return false;
            }
        }

        void AnyValue::set_default_values()
        {
            this->any_struct_shared_ptr = nullptr;
            this->std_vector_int8_t_shared_ptr = nullptr;
            this->std_vector_uint8_t_shared_ptr = nullptr;
            this->std_vector_int16_t_shared_ptr = nullptr;
            this->std_vector_uint16_t_shared_ptr = nullptr;
            this->std_vector_int32_t_shared_ptr = nullptr;
            this->std_vector_uint32_t_shared_ptr = nullptr;
            this->std_vector_float_shared_ptr = nullptr;
            this->type = yli::common::UNKNOWN;
        }

        AnyValue::AnyValue(const yli::common::AnyValue& original)
        {
            // copy constructor.
            this->type = original.type;
            this->any_struct_shared_ptr = original.any_struct_shared_ptr;
            this->bool_value = original.bool_value;
            this->char_value = original.char_value;
            this->float_value = original.float_value;
            this->double_value = original.double_value;
            this->int32_t_value = original.int32_t_value;
            this->uint32_t_value = original.uint32_t_value;
            this->bool_pointer = original.bool_pointer;
            this->float_pointer = original.float_pointer;
            this->double_pointer = original.double_pointer;
            this->int32_t_pointer = original.int32_t_pointer;
            this->uint32_t_pointer = original.uint32_t_pointer;
            this->universe = original.universe;
            this->scene_pointer = original.scene_pointer;
            this->shader_pointer = original.shader_pointer;
            this->material_pointer = original.material_pointer;
            this->species_pointer = original.species_pointer;
            this->object_pointer = original.object_pointer;
            this->vector_font_pointer = original.vector_font_pointer;
            this->glyph_pointer = original.glyph_pointer;
            this->text3D_pointer = original.text3D_pointer;
            this->symbiosis_pointer = original.symbiosis_pointer;
            this->font2D_pointer = original.font2D_pointer;
            this->console_pointer = original.console_pointer;
            this->spherical_coordinates_struct_pointer = original.spherical_coordinates_struct_pointer;
            this->std_string_pointer = original.std_string_pointer;
            this->std_vector_int8_t_shared_ptr = original.std_vector_int8_t_shared_ptr;
            this->std_vector_uint8_t_shared_ptr = original.std_vector_uint8_t_shared_ptr;
            this->std_vector_int16_t_shared_ptr = original.std_vector_int16_t_shared_ptr;
            this->std_vector_uint16_t_shared_ptr = original.std_vector_uint16_t_shared_ptr;
            this->std_vector_int32_t_shared_ptr = original.std_vector_int32_t_shared_ptr;
            this->std_vector_uint32_t_shared_ptr = original.std_vector_uint32_t_shared_ptr;
            this->std_vector_float_shared_ptr = original.std_vector_float_shared_ptr;
            this->glm_vec3_pointer = original.glm_vec3_pointer;
            this->glm_vec4_pointer = original.glm_vec4_pointer;
        }

        AnyValue::AnyValue(const std::string& type, const std::string& value_string)
        {
            this->set_default_values();

            if (type == "std::shared_ptr<yli::common::AnyStruct>")
            {
                this->type = yli::common::ANY_STRUCT_SHARED_PTR;
                this->set_value(value_string);
            }
            else if (type == "bool")
            {
                this->type = yli::common::BOOL;
                this->set_value(value_string);
            }
            else if (type == "char")
            {
                this->type = yli::common::CHAR;
                this->set_value(value_string);
            }
            else if (type == "float")
            {
                this->type = yli::common::FLOAT;
                this->set_value(value_string);
            }
            else if (type == "double")
            {
                this->type = yli::common::DOUBLE;
                this->set_value(value_string);
            }
            else if (type == "int32_t")
            {
                this->type = yli::common::INT32_T;
                this->set_value(value_string);
            }
            else if (type == "uint32_t")
            {
                this->type = yli::common::UINT32_T;
                this->set_value(value_string);
            }
            else if (type == "bool*")
            {
                this->type = yli::common::BOOL_POINTER;
                this->set_value(value_string);
            }
            else if (type == "float*")
            {
                this->type = yli::common::FLOAT_POINTER;
                this->set_value(value_string);
            }
            else if (type == "double*")
            {
                this->type = yli::common::FLOAT_POINTER;
                this->set_value(value_string);
            }
            else if (type == "int32_t*")
            {
                this->type = yli::common::INT32_T_POINTER;
                this->set_value(value_string);
            }
            else if (type == "uint32_t*")
            {
                this->type = yli::common::UINT32_T_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Universe*")
            {
                this->type = yli::common::UNIVERSE_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Scene*")
            {
                this->type = yli::common::SCENE_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Shader*")
            {
                this->type = yli::common::SHADER_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Material*")
            {
                this->type = yli::common::MATERIAL_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Species*")
            {
                this->type = yli::common::SPECIES_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Object*")
            {
                this->type = yli::common::OBJECT_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::VectorFont*")
            {
                this->type = yli::common::VECTORFONT_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Glyph*")
            {
                this->type = yli::common::GLYPH_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Text3D*")
            {
                this->type = yli::common::TEXT3D_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Symbiosis*")
            {
                this->type = yli::common::SYMBIOSIS_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::ontology::Text2D*")
            {
                this->type = yli::common::TEXT2D_POINTER;
                this->set_value(value_string);
            }
            else if (type == "yli::console::Console*")
            {
                this->type = yli::common::CONSOLE_POINTER;
                this->set_value(value_string);
            }
            else
            {
                this->type = yli::common::UNKNOWN;
            }
        }

        AnyValue::AnyValue()
        {
            // constructor.
            this->set_default_values();
        }

        AnyValue::AnyValue(std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::ANY_STRUCT_SHARED_PTR;
            this->any_struct_shared_ptr = any_struct_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<yli::common::AnyStruct>")
            {
                this->type = yli::common::ANY_STRUCT_SHARED_PTR;
                this->any_struct_shared_ptr = any_struct_shared_ptr;
            }
        }

        AnyValue::AnyValue(const bool bool_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::BOOL;
            this->bool_value = bool_value;
        }

        AnyValue::AnyValue(const std::string& type, const bool bool_value)
        {
            // constructor.
            this->set_default_values();

            if (type == "bool")
            {
                this->type = yli::common::BOOL;
                this->bool_value = bool_value;
            }
        }

        AnyValue::AnyValue(const char char_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::CHAR;
            this->char_value = char_value;
        }

        AnyValue::AnyValue(const std::string& type, const char char_value)
        {
            // constructor.
            this->set_default_values();

            if (type == "char")
            {
                this->type = yli::common::CHAR;
                this->char_value = char_value;
            }
        }

        AnyValue::AnyValue(const float float_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::FLOAT;
            this->float_value = float_value;
        }

        AnyValue::AnyValue(const std::string& type, const float float_value)
        {
            // constructor.
            this->set_default_values();

            if (type == "float")
            {
                this->type = yli::common::FLOAT;
                this->float_value = float_value;
            }
        }

        AnyValue::AnyValue(const double double_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::DOUBLE;
            this->double_value = double_value;
        }

        AnyValue::AnyValue(const std::string& type, const double double_value)
        {
            // constructor.
            this->set_default_values();

            if (type == "double")
            {
                this->type = yli::common::DOUBLE;
                this->double_value = double_value;
            }
        }

        AnyValue::AnyValue(const int32_t int32_t_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::INT32_T;
            this->int32_t_value = int32_t_value;
        }

        AnyValue::AnyValue(const std::string& type, const int32_t int32_t_value)
        {
            // constructor.
            this->set_default_values();

            if (type == "int32_t")
            {
                this->type = yli::common::INT32_T;
                this->int32_t_value = int32_t_value;
            }
        }

        AnyValue::AnyValue(const uint32_t uint32_t_value)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::UINT32_T;
            this->uint32_t_value = uint32_t_value;
        }

        AnyValue::AnyValue(const std::string& type, const uint32_t uint32_t_value)
        {
            // constructor.
            this->set_default_values();

            if (type == "uint32_t")
            {
                this->type = yli::common::UINT32_T;
                this->uint32_t_value = uint32_t_value;
            }
        }

        AnyValue::AnyValue(bool* const bool_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::BOOL_POINTER;
            this->bool_pointer = bool_pointer;
        }

        AnyValue::AnyValue(const std::string& type, bool* const bool_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "bool*")
            {
                this->type = yli::common::BOOL_POINTER;
                this->bool_pointer = bool_pointer;
            }
        }

        AnyValue::AnyValue(float* const float_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::FLOAT_POINTER;
            this->float_pointer = float_pointer;
        }

        AnyValue::AnyValue(const std::string& type, float* const float_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "float*")
            {
                this->type = yli::common::FLOAT_POINTER;
                this->float_pointer = float_pointer;
            }
        }

        AnyValue::AnyValue(double* const double_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::DOUBLE_POINTER;
            this->double_pointer = double_pointer;
        }

        AnyValue::AnyValue(const std::string& type, double* const double_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "double*")
            {
                this->type = yli::common::DOUBLE_POINTER;
                this->double_pointer = double_pointer;
            }
        }

        AnyValue::AnyValue(int32_t* const int32_t_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::INT32_T_POINTER;
            this->int32_t_pointer = int32_t_pointer;
        }

        AnyValue::AnyValue(const std::string& type, int32_t* const int32_t_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "int32_t*")
            {
                this->type = yli::common::INT32_T_POINTER;
                this->int32_t_pointer = int32_t_pointer;
            }
        }

        AnyValue::AnyValue(uint32_t* const uint32_t_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::UINT32_T_POINTER;
            this->uint32_t_pointer = uint32_t_pointer;
        }

        AnyValue::AnyValue(const std::string& type, uint32_t* const uint32_t_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "uint32_t*")
            {
                this->type = yli::common::UINT32_T_POINTER;
                this->uint32_t_pointer = uint32_t_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Universe* const universe)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::UNIVERSE_POINTER;
            this->universe = universe;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Universe* const universe)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Universe*")
            {
                this->type = yli::common::UNIVERSE_POINTER;
                this->universe = universe;
            }
        }

        AnyValue::AnyValue(yli::ontology::Scene* const scene_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::SCENE_POINTER;
            this->scene_pointer = scene_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Scene* const scene_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Scene*")
            {
                this->type = yli::common::SCENE_POINTER;
                this->scene_pointer = scene_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Shader* const shader_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::SHADER_POINTER;
            this->shader_pointer = shader_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Shader* const shader_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Shader*")
            {
                this->type = yli::common::SHADER_POINTER;
                this->shader_pointer = shader_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Material* const material_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::MATERIAL_POINTER;
            this->material_pointer = material_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Material* const material_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Material*")
            {
                this->type = yli::common::MATERIAL_POINTER;
                this->material_pointer = material_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Species* const species_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::SPECIES_POINTER;
            this->species_pointer = species_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Species* const species_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Species*")
            {
                this->type = yli::common::SPECIES_POINTER;
                this->species_pointer = species_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Object* const object_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::OBJECT_POINTER;
            this->object_pointer = object_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Object* const object_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Object*")
            {
                this->type = yli::common::OBJECT_POINTER;
                this->object_pointer = object_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::VectorFont* const vector_font_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::VECTORFONT_POINTER;
            this->vector_font_pointer = vector_font_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::VectorFont* const vector_font_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Vectorfont*")
            {
                this->type = yli::common::VECTORFONT_POINTER;
                this->vector_font_pointer = vector_font_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Glyph* const glyph_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::GLYPH_POINTER;
            this->glyph_pointer = glyph_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Glyph* const glyph_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Glyph*")
            {
                this->type = yli::common::GLYPH_POINTER;
                this->glyph_pointer = glyph_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Text3D* const text3D_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::TEXT3D_POINTER;
            this->text3D_pointer = text3D_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Text3D* const text3D_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Text3D*")
            {
                this->type = yli::common::TEXT3D_POINTER;
                this->text3D_pointer = text3D_pointer;
            }
        }

        AnyValue::AnyValue(yli::ontology::Font2D* const font2D_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::TEXT2D_POINTER;
            this->font2D_pointer = font2D_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::ontology::Font2D* const font2D_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::ontology::Font2D*")
            {
                this->type = yli::common::TEXT2D_POINTER;
                this->font2D_pointer = font2D_pointer;
            }
        }

        AnyValue::AnyValue(yli::console::Console* const console_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::CONSOLE_POINTER;
            this->console_pointer = console_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::console::Console* const console_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::console::Console*")
            {
                this->type = yli::common::CONSOLE_POINTER;
                this->console_pointer = console_pointer;
            }
        }

        AnyValue::AnyValue(yli::common::SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::SPHERICAL_COORDINATES_STRUCT_POINTER;
            this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
        }

        AnyValue::AnyValue(const std::string& type, yli::common::SphericalCoordinatesStruct* const spherical_coordinates_struct_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "yli::common::SphericalCoordinatesStruct*")
            {
                this->type = yli::common::SPHERICAL_COORDINATES_STRUCT_POINTER;
                this->spherical_coordinates_struct_pointer = spherical_coordinates_struct_pointer;
            }
        }

        AnyValue::AnyValue(std::string* const std_string_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_STRING_POINTER;
            this->std_string_pointer = std_string_pointer;
        }

        AnyValue::AnyValue(const std::string& type, std::string* const std_string_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::string*")
            {
                this->type = yli::common::STD_STRING_POINTER;
                this->std_string_pointer = std_string_pointer;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_INT8_T_SHARED_PTR;
            this->std_vector_int8_t_shared_ptr = std_vector_int8_t_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<int8_t>>")
            {
                this->type = yli::common::STD_VECTOR_INT8_T_SHARED_PTR;
                this->std_vector_int8_t_shared_ptr = std_vector_int8_t_shared_ptr;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_UINT8_T_SHARED_PTR;
            this->std_vector_uint8_t_shared_ptr = std_vector_uint8_t_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<uint8_t>>")
            {
                this->type = yli::common::STD_VECTOR_UINT8_T_SHARED_PTR;
                this->std_vector_uint8_t_shared_ptr = std_vector_uint8_t_shared_ptr;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_INT16_T_SHARED_PTR;
            this->std_vector_int16_t_shared_ptr = std_vector_int16_t_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<int16_t>>")
            {
                this->type = yli::common::STD_VECTOR_INT16_T_SHARED_PTR;
                this->std_vector_int16_t_shared_ptr = std_vector_int16_t_shared_ptr;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_UINT16_T_SHARED_PTR;
            this->std_vector_uint16_t_shared_ptr = std_vector_uint16_t_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<uint16_t>>")
            {
                this->type = yli::common::STD_VECTOR_UINT16_T_SHARED_PTR;
                this->std_vector_uint16_t_shared_ptr = std_vector_uint16_t_shared_ptr;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_INT32_T_SHARED_PTR;
            this->std_vector_int32_t_shared_ptr = std_vector_int32_t_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<int32_t>>")
            {
                this->type = yli::common::STD_VECTOR_INT32_T_SHARED_PTR;
                this->std_vector_int32_t_shared_ptr = std_vector_int32_t_shared_ptr;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_UINT32_T_SHARED_PTR;
            this->std_vector_uint32_t_shared_ptr = std_vector_uint32_t_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<uint32_t>>")
            {
                this->type = yli::common::STD_VECTOR_UINT32_T_SHARED_PTR;
                this->std_vector_uint32_t_shared_ptr = std_vector_uint32_t_shared_ptr;
            }
        }

        AnyValue::AnyValue(std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::STD_VECTOR_FLOAT_SHARED_PTR;
            this->std_vector_float_shared_ptr = std_vector_float_shared_ptr;
        }

        AnyValue::AnyValue(const std::string& type, std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr)
        {
            // constructor.
            this->set_default_values();

            if (type == "std::shared_ptr<std::vector<float>>")
            {
                this->type = yli::common::STD_VECTOR_FLOAT_SHARED_PTR;
                this->std_vector_float_shared_ptr = std_vector_float_shared_ptr;
            }
        }

        AnyValue::AnyValue(glm::vec3* const glm_vec3_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::GLM_VEC3_POINTER;
            this->glm_vec3_pointer = glm_vec3_pointer;
        }

        AnyValue::AnyValue(const std::string& type, glm::vec3* const glm_vec3_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "glm::vec3*")
            {
                this->type = yli::common::GLM_VEC3_POINTER;
                this->glm_vec3_pointer = glm_vec3_pointer;
            }
        }

        AnyValue::AnyValue(glm::vec4* const glm_vec4_pointer)
        {
            // constructor.
            this->set_default_values();
            this->type = yli::common::GLM_VEC4_POINTER;
            this->glm_vec4_pointer = glm_vec4_pointer;
        }

        AnyValue::AnyValue(const std::string& type, glm::vec4* const glm_vec4_pointer)
        {
            // constructor.
            this->set_default_values();

            if (type == "glm::vec4*")
            {
                this->type = yli::common::GLM_VEC4_POINTER;
                this->glm_vec4_pointer = glm_vec4_pointer;
            }
        }
    }
}
