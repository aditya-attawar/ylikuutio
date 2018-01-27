#include "symbiosis.hpp"
#include "shader.hpp"
#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "holobiont.hpp"
#include "material_struct.hpp"
#include "entity_templates.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include <ofbx.h>

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Holobiont;

    void Symbiosis::bind_symbiont_material(ontology::SymbiontMaterial* const symbiont_material)
    {
        // get `childID` from `Symbiosis` and set pointer to `symbiont_material`.
        hierarchy::bind_child_to_parent<ontology::SymbiontMaterial*>(
                symbiont_material,
                this->symbiont_material_pointer_vector,
                this->free_symbiont_materialID_queue,
                &this->number_of_symbiont_materials);
    }

    void Symbiosis::bind_holobiont(ontology::Holobiont* const holobiont)
    {
        // get `childID` from `Symbiosis` and set pointer to `object`.
        hierarchy::bind_child_to_parent<ontology::Holobiont*>(
                holobiont,
                this->holobiont_pointer_vector,
                this->free_holobiontID_queue,
                &this->number_of_holobionts);
    }

    void Symbiosis::unbind_holobiont(const int32_t childID)
    {
        ontology::Holobiont* dummy_child_pointer = nullptr;
        hierarchy::set_child_pointer(
                childID,
                dummy_child_pointer,
                this->holobiont_pointer_vector,
                this->free_holobiontID_queue,
                &this->number_of_holobionts);
    }

    void Symbiosis::bind_to_parent()
    {
        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        this->parent->bind_symbiosis(this);
    }

    void Symbiosis::bind_to_new_parent(ontology::Shader* const new_shader_pointer)
    {
        // unbind from the old parent `Shader`.
        this->parent->unbind_symbiosis(this->childID);

        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        this->parent = new_shader_pointer;
        this->parent->bind_symbiosis(this);
    }

    Symbiosis::~Symbiosis()
    {
        // destructor.
        std::cout << "Symbiosis with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all holobionts of this symbiosis.
        std::cout << "All holobionts of this symbiosis will be destroyed.\n";
        hierarchy::delete_children<ontology::Holobiont*>(this->holobiont_pointer_vector, &this->number_of_holobionts);

        // destroy all symbiont materials of this symbiosis.
        std::cout << "All symbiont materials of this symbiosis will be destroyed.\n";
        hierarchy::delete_children<ontology::SymbiontMaterial*>(this->symbiont_material_pointer_vector, &this->number_of_symbiont_materials);

        // set pointer to this symbiosis to nullptr.
        this->parent->set_symbiosis_pointer(this->childID, nullptr);
    }

    void Symbiosis::render()
    {
        this->prerender();

        // render this `Symbiosis` by calling `render()` function of each `SymbiontMaterial`.
        ontology::render_children<ontology::Holobiont*>(this->holobiont_pointer_vector);

        this->postrender();
    }

    void Symbiosis::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }

    ontology::Entity* Symbiosis::get_parent() const
    {
        return this->parent;
    }

    int32_t Symbiosis::get_number_of_children() const
    {
        return this->number_of_symbiont_materials + this->number_of_holobionts;
    }

    int32_t Symbiosis::get_number_of_descendants() const
    {
        return -1;
    }

    const std::string& Symbiosis::get_model_file_format()
    {
        return this->model_file_format;
    }

    void Symbiosis::set_symbiont_material_pointer(const int32_t childID, ontology::SymbiontMaterial* const child_pointer)
    {
        hierarchy::set_child_pointer(
                childID,
                child_pointer,
                this->symbiont_material_pointer_vector,
                this->free_symbiont_materialID_queue,
                &this->number_of_symbiont_materials);
    }

    void Symbiosis::set_holobiont_pointer(const int32_t childID, ontology::Holobiont* const child_pointer)
    {
        hierarchy::set_child_pointer(
                childID,
                child_pointer,
                this->holobiont_pointer_vector,
                this->free_holobiontID_queue,
                &this->number_of_holobionts);
    }

    void Symbiosis::create_symbionts()
    {
        SymbiosisLoaderStruct symbiosis_loader_struct;
        symbiosis_loader_struct.model_filename = this->model_filename;
        symbiosis_loader_struct.model_file_format = this->model_file_format;
        symbiosis_loader_struct.triangulation_type = this->triangulation_type;

        if (loaders::load_symbiosis(
                    symbiosis_loader_struct,
                    this->vertices,
                    this->uvs,
                    this->normals,
                    this->indices,
                    this->indexed_vertices,
                    this->indexed_uvs,
                    this->indexed_normals,
                    this->ofbx_diffuse_texture_mesh_map,
                    this->ofbx_meshes,
                    this->ofbx_diffuse_texture_vector,
                    this->ofbx_normal_texture_vector,
                    this->ofbx_count_texture_vector,
                    this->ofbx_mesh_count))
        {
            std::cout << "number of meshes: " << this->ofbx_mesh_count << "\n";

            std::vector<const ofbx::Texture*> ofbx_diffuse_texture_pointer_vector;
            ofbx_diffuse_texture_pointer_vector.reserve(this->ofbx_diffuse_texture_mesh_map.size());
            this->biontID_symbiont_material_vector.resize(this->ofbx_mesh_count);

            this->biontID_symbiont_species_vector.resize(this->ofbx_mesh_count);

            for (auto key_and_value : ofbx_diffuse_texture_mesh_map)
            {
                ofbx_diffuse_texture_pointer_vector.push_back(key_and_value.first); // key.
            }

            // Create `SymbiontMaterial`s.
            for (const ofbx::Texture* ofbx_texture : ofbx_diffuse_texture_pointer_vector)
            {
                std::cout << "Creating ontology::SymbiontMaterial* based on ofbx::Texture* at 0x" << std::hex << (uint64_t) ofbx_texture << std::dec << " ...\n";
                MaterialStruct material_struct;
                material_struct.shader = this->parent;
                material_struct.symbiosis = this;
                material_struct.is_symbiont_material = true;
                material_struct.ofbx_texture = ofbx_texture;
                ontology::SymbiontMaterial* symbiont_material = new ontology::SymbiontMaterial(this->universe, material_struct);
                symbiont_material->load_texture();

                std::cout << "ontology::SymbiontMaterial* successfully created.\n";

                // Create `SymbiontSpecies`s.
                // Care only about `ofbx::Texture*`s with are DIFFUSE textures.
                for (int32_t mesh_i : this->ofbx_diffuse_texture_mesh_map.at(ofbx_texture))
                {
                    int32_t vertex_count = this->vertices.at(mesh_i).size();
                    std::vector<glm::vec3> vertices = this->vertices.at(mesh_i);

                    SpeciesStruct species_struct;
                    species_struct.is_symbiont_species = true;
                    species_struct.scene = static_cast<ontology::Scene*>(this->parent->get_parent());
                    species_struct.shader = this->parent;
                    species_struct.symbiont_material = symbiont_material;
                    species_struct.vertex_count = vertex_count;
                    species_struct.vertices = this->vertices.at(mesh_i);
                    species_struct.uvs = this->uvs.at(mesh_i);
                    species_struct.normals = this->normals.at(mesh_i);
                    species_struct.light_position = this->light_position;

                    std::cout << "Creating ontology::SymbiontSpecies*, mesh index " << mesh_i << "...\n";

                    ontology::SymbiontSpecies* symbiont_species = new ontology::SymbiontSpecies(this->universe, species_struct);

                    std::cout << "ontology::SymbiontSpecies*, mesh index " << mesh_i << " successfully created.\n";

                    std::cout << "storing ontology::SymbiontMaterial* symbiont_material into vector with mesh_i " << mesh_i << " ...\n";
                    this->biontID_symbiont_material_vector.at(mesh_i) = symbiont_material;
                    std::cout << "storing ontology::SymbiontSpecies* symbiont_species into vector with mesh_i " << mesh_i << " ...\n";
                    this->biontID_symbiont_species_vector.at(mesh_i) = symbiont_species;

                    std::cout << "Success.\n";
                    // TODO: Compute the graph of each type to enable object vertex modification!
                }
            }

            std::cout << "All symbionts successfully created.\n";
        }
    }

    ontology::SymbiontSpecies* Symbiosis::get_symbiont_species(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID);
    }

    GLuint Symbiosis::get_vertex_position_modelspaceID(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_vertex_position_modelspaceID();
    }

    GLuint Symbiosis::get_vertexUVID(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_vertexUVID();
    }

    GLuint Symbiosis::get_vertex_normal_modelspaceID(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_vertex_normal_modelspaceID();
    }

    GLuint Symbiosis::get_vertexbuffer(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_vertexbuffer();
    }

    GLuint Symbiosis::get_uvbuffer(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_uvbuffer();
    }

    GLuint Symbiosis::get_normalbuffer(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_normalbuffer();
    }

    GLuint Symbiosis::get_elementbuffer(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_elementbuffer();
    }

    std::vector<uint32_t> Symbiosis::get_indices(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_indices();
        // return this->indices.at(biontID);
    }

    GLuint Symbiosis::get_indices_size(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_indices_size();
        // return this->indices.at(biontID).size();
    }

    int32_t Symbiosis::get_number_of_symbionts() const
    {
        return this->ofbx_mesh_count;
    }

    bool Symbiosis::has_texture(const int32_t biontID) const
    {
        if (biontID >= this->biontID_symbiont_material_vector.size())
        {
            return false;
        }

        if (this->biontID_symbiont_material_vector.at(biontID) == nullptr)
        {
            return false;
        }

        return true;
    }

    GLuint Symbiosis::get_texture(const int32_t biontID) const
    {
        return this->biontID_symbiont_material_vector.at(biontID)->get_texture();
    }

    GLuint Symbiosis::get_openGL_textureID(const int32_t biontID) const
    {
        return this->biontID_symbiont_material_vector.at(biontID)->get_openGL_textureID();
    }

    GLuint Symbiosis::get_lightID(const int32_t biontID) const
    {
        return this->biontID_symbiont_species_vector.at(biontID)->get_lightID();
    }

    glm::vec3 Symbiosis::get_light_position(const int32_t biontID) const
    {
        return this->light_position;
    }
}
