#include "entity_factory.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "vector_font.hpp"
#include "text3D.hpp"
#include "font2D.hpp"
#include "shader_struct.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "object_struct.hpp"
#include "vector_font_struct.hpp"
#include "text3D_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <string>    // std::string

namespace ontology
{
    EntityFactory::EntityFactory()
    {
        // constructor.
    }

    EntityFactory::~EntityFactory()
    {
        // destructor.
    }

    ontology::Entity* EntityFactory::create_Universe()
    {
        return new ontology::Universe();
    }

    ontology::Entity* EntityFactory::create_Scene(ontology::Universe* const universe, const float water_level)
    {
        return new ontology::Scene(universe, water_level);
    }

    ontology::Entity* EntityFactory::create_Shader(const ShaderStruct shader_struct)
    {
        return new ontology::Shader(shader_struct);
    }

    ontology::Entity* EntityFactory::create_Material(const MaterialStruct material_struct)
    {
        return new ontology::Material(material_struct);
    }

    ontology::Entity* EntityFactory::create_Species(const SpeciesStruct species_struct)
    {
        return new ontology::Species(species_struct);
    }

    ontology::Entity* EntityFactory::create_Object(const ObjectStruct object_struct)
    {
        return new ontology::Object(object_struct);
    }

    ontology::Entity* EntityFactory::create_VectorFont(const VectorFontStruct vector_font_struct)
    {
        return new ontology::VectorFont(vector_font_struct);
    }

    ontology::Entity* EntityFactory::create_Text3D(const Text3DStruct text3D_struct)
    {
        return new ontology::Text3D(text3D_struct);
    }

    ontology::Entity* EntityFactory::create_Font2D(
            ontology::Universe* universe,
            GLuint screen_width,
            GLuint screen_height,
            std::string texture_filename,
            std::string font_texture_file_format)
    {
        return new ontology::Font2D(
                universe,
                universe->get_window_width(),
                universe->get_window_height(),
                texture_filename.c_str(),
                font_texture_file_format.c_str());
    }
}