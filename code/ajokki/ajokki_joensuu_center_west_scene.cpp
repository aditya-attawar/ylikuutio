#include "ajokki_joensuu_center_west_scene.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>   // std::cout, std::cin, std::cerr
#include <string>     // std::string

namespace yli
{
    namespace ontology
    {
        class World;
        class Entity;
    }
}

namespace ajokki
{
    yli::ontology::Entity* create_joensuu_center_west_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // Joensuu `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_scene_entity ...\n";
        yli::ontology::Entity* joensuu_center_west_scene_entity = entity_factory->create_Scene(world, 77.0f);
        std::cout << "Creating yli::ontology::Scene* joensuu_center_west_scene ...\n";
        yli::ontology::Scene* joensuu_center_west_scene = dynamic_cast<yli::ontology::Scene*>(joensuu_center_west_scene_entity);

        if (joensuu_center_west_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        joensuu_center_west_scene->set_name("joensuu_center_west_scene");

        // Set `joensuu_center_west_scene` to be the currently active `Scene`.
        // my_universe->set_active_scene(joensuu_center_west_scene);

        joensuu_center_west_scene->set_turbo_factor(5.0f);
        joensuu_center_west_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `joensuu_center_west_shader`.
        ShaderStruct joensuu_center_west_shader_struct;
        joensuu_center_west_shader_struct.parent = joensuu_center_west_scene;
        joensuu_center_west_shader_struct.vertex_shader = "StandardShading.vertexshader";
        joensuu_center_west_shader_struct.fragment_shader = "StandardShading.fragmentshader";

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_shader_entity ...\n";
        yli::ontology::Entity* joensuu_center_west_shader_entity = entity_factory->create_Shader(joensuu_center_west_shader_struct);
        std::cout << "Creating yli::ontology::Shader* joensuu_center_west_shader ...\n";
        yli::ontology::Shader* joensuu_center_west_shader = dynamic_cast<yli::ontology::Shader*>(joensuu_center_west_shader_entity);

        if (joensuu_center_west_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        // Create the material, store it in `joensuu_center_west_grass_material_struct`.
        MaterialStruct joensuu_center_west_grass_material_struct;
        joensuu_center_west_grass_material_struct.shader = joensuu_center_west_shader;
        joensuu_center_west_grass_material_struct.texture_file_format = "bmp";
        joensuu_center_west_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_grass_material_entity ...\n";
        yli::ontology::Entity* joensuu_center_west_grass_material_entity = entity_factory->create_Material(joensuu_center_west_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* joensuu_center_west_grass_material ...\n";
        yli::ontology::Material* joensuu_center_west_grass_material = dynamic_cast<yli::ontology::Material*>(joensuu_center_west_grass_material_entity);

        if (joensuu_center_west_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        joensuu_center_west_grass_material->set_name("joensuu_center_west_grass_material");

        SpeciesStruct joensuu_center_west_terrain_species_struct;
        joensuu_center_west_terrain_species_struct.scene = joensuu_center_west_scene;
        joensuu_center_west_terrain_species_struct.shader = joensuu_center_west_shader;
        joensuu_center_west_terrain_species_struct.material = joensuu_center_west_grass_material;
        joensuu_center_west_terrain_species_struct.model_file_format = "ASCII_grid";
        joensuu_center_west_terrain_species_struct.model_filename = "N5424G.asc"; // Joensuu center & western.
        joensuu_center_west_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        joensuu_center_west_terrain_species_struct.is_terrain = true;
        joensuu_center_west_terrain_species_struct.x_step = 4;
        joensuu_center_west_terrain_species_struct.z_step = 4;
        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_terrain_species_entity ...\n";
        yli::ontology::Entity* joensuu_center_west_terrain_species_entity = entity_factory->create_Species(joensuu_center_west_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* joensuu_center_west_terrain_species ...\n";
        yli::ontology::Species* joensuu_center_west_terrain_species = dynamic_cast<yli::ontology::Species*>(joensuu_center_west_terrain_species_entity);

        if (joensuu_center_west_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        joensuu_center_west_terrain_species->set_name("joensuu_center_west_terrain_species");

        // Create Joensuu center west terrain.
        ObjectStruct joensuu_center_west_struct;
        joensuu_center_west_struct.species_parent = joensuu_center_west_terrain_species;
        joensuu_center_west_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        joensuu_center_west_struct.rotate_angle = 0.0f;
        joensuu_center_west_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        joensuu_center_west_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Object(joensuu_center_west_struct);

        // Create the material, store it in `orange_fur_material_joensuu`.
        MaterialStruct orange_fur_material_joensuu_struct;
        orange_fur_material_joensuu_struct.shader = joensuu_center_west_shader;
        orange_fur_material_joensuu_struct.texture_file_format = "bmp";
        orange_fur_material_joensuu_struct.texture_filename = "orange_fur_texture.bmp";

        std::cout << "Creating yli::ontology::Entity* orange_fur_material_joensuu_entity ...\n";
        yli::ontology::Entity* orange_fur_material_joensuu_entity = entity_factory->create_Material(orange_fur_material_joensuu_struct);
        std::cout << "Creating yli::ontology::Material* orange_fur_material_joensuu ...\n";
        yli::ontology::Material* orange_fur_material_joensuu = dynamic_cast<yli::ontology::Material*>(orange_fur_material_joensuu_entity);

        if (orange_fur_material_joensuu == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        SpeciesStruct horse_species_struct;
        horse_species_struct.scene = joensuu_center_west_scene;
        horse_species_struct.shader = joensuu_center_west_shader;
        horse_species_struct.material = orange_fur_material_joensuu;
        horse_species_struct.model_file_format = "fbx";
        horse_species_struct.model_filename = "horse.fbx";
        horse_species_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* horse_species_entity ...\n";
        yli::ontology::Entity* horse_species_entity = entity_factory->create_Species(horse_species_struct);

        std::cout << "Creating yli::ontology::Species* horse_species ...\n";
        yli::ontology::Species* horse_species = dynamic_cast<yli::ontology::Species*>(horse_species_entity);

        if (horse_species == nullptr)
        {
            std::cerr << "Failed to create horse Species.\n";
            return nullptr;
        }

        horse_species->set_name("horse_species");

        ObjectStruct horse_object_struct1;
        horse_object_struct1.species_parent = horse_species;
        horse_object_struct1.original_scale_vector = glm::vec3(5.0f, 5.0f, 5.0f);
        horse_object_struct1.cartesian_coordinates = glm::vec3(2150.00f, 200.00f, 1990.00f);
        horse_object_struct1.rotate_angle = 0.00f;
        horse_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        horse_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        yli::ontology::Entity* horse1_entity = entity_factory->create_Object(horse_object_struct1);
        yli::ontology::Object* horse1 = dynamic_cast<yli::ontology::Object*>(horse1_entity);

        if (horse1 == nullptr)
        {
            std::cerr << "Failed to create horse1 Object.\n";
            return nullptr;
        }

        horse1->set_name("horse1");

        return joensuu_center_west_scene_entity;
        // Joensuu `Scene` ends here.
    }
}