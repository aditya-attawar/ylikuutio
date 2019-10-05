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

#include "symbiosis.hpp"
#include "shader.hpp"
#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "holobiont.hpp"
#include "material_struct.hpp"
#include "species_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/symbiosis_loader.hpp"
#include "code/ylikuutio/load/symbiosis_loader_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include <ofbx.h>

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Holobiont;

        void Symbiosis::bind_symbiont_material(yli::ontology::SymbiontMaterial* const symbiont_material)
        {
            // get `childID` from `Symbiosis` and set pointer to `symbiont_material`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::SymbiontMaterial*>(
                    symbiont_material,
                    this->symbiont_material_pointer_vector,
                    this->free_symbiont_materialID_queue,
                    this->number_of_symbiont_materials);
        }

        void Symbiosis::unbind_symbiont_material(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->symbiont_material_pointer_vector,
                    this->free_symbiont_materialID_queue,
                    this->number_of_symbiont_materials);
        }

        void Symbiosis::bind_holobiont(yli::ontology::Holobiont* const holobiont)
        {
            // get `childID` from `Symbiosis` and set pointer to `holobiont`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Holobiont*>(
                    holobiont,
                    this->holobiont_pointer_vector,
                    this->free_holobiontID_queue,
                    this->number_of_holobionts);
        }

        void Symbiosis::unbind_holobiont(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->holobiont_pointer_vector,
                    this->free_holobiontID_queue,
                    this->number_of_holobionts);
        }

        void Symbiosis::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Symbiosis::bind_to_parent`: `shader` is `nullptr`!\n";
                return;
            }

            // get `childID` from `Shader` and set pointer to this `Symbiosis`.
            shader->bind_symbiosis(this);
        }

        void Symbiosis::bind_to_new_parent(yli::ontology::Shader* const new_parent)
        {
            // this method sets pointer to this `Symbiosis` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Shader`.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Symbiosis::bind_to_new_parent`: `shader` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Symbiosis::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Shader`.
            shader->unbind_symbiosis(this->childID);

            // get `childID` from `Shader` and set pointer to this `Symbiosis`.
            this->parent = new_parent;
            this->parent->bind_symbiosis(this);
        }

        Symbiosis::~Symbiosis()
        {
            // destructor.
            std::cout << "Symbiosis with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all `Holobiont`s of this `Symbiosis`.
            std::cout << "All holobionts of this symbiosis will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Holobiont*>(this->holobiont_pointer_vector, this->number_of_holobionts);

            // destroy all `SymbiontMaterial`s of this `Symbiosis`.
            std::cout << "All symbiont materials of this symbiosis will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::SymbiontMaterial*>(this->symbiont_material_pointer_vector, this->number_of_symbiont_materials);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Symbiosis::~Symbiosis`: `shader` is `nullptr`!\n";
                return;
            }

            // set pointer to this `Symbiosis` to `nullptr`.
            shader->unbind_symbiosis(this->childID);
        }

        void Symbiosis::render()
        {
            if (this->should_be_rendered && this->vram_buffer_in_use)
            {
                this->prerender();

                // render this `Symbiosis` by calling `render()` function of each `Holobiont`.
                yli::ontology::render_children<yli::ontology::Holobiont*>(this->holobiont_pointer_vector);

                this->postrender();
            }
        }

        std::size_t Symbiosis::get_number_of_symbiont_materials() const
        {
            return this->number_of_symbiont_materials;
        }

        std::size_t Symbiosis::get_number_of_symbiont_species() const
        {
            std::size_t number_of_symbiont_species = 0;

            for (auto symbiont_material : this->symbiont_material_pointer_vector)
            {
                number_of_symbiont_species += symbiont_material->get_number_of_children();
            }

            return number_of_symbiont_species;
        }

        yli::ontology::Entity* Symbiosis::get_parent() const
        {
            return this->parent;
        }

        std::size_t Symbiosis::get_number_of_children() const
        {
            return this->number_of_symbiont_materials + this->number_of_holobionts;
        }

        std::size_t Symbiosis::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->symbiont_material_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->holobiont_pointer_vector);
        }

        const std::string& Symbiosis::get_model_file_format() const
        {
            return this->model_file_format;
        }

        void Symbiosis::create_symbionts()
        {
            yli::load::SymbiosisLoaderStruct symbiosis_loader_struct;
            symbiosis_loader_struct.model_filename = this->model_filename;
            symbiosis_loader_struct.model_file_format = this->model_file_format;
            symbiosis_loader_struct.triangulation_type = this->triangulation_type;

            const bool is_debug_mode = true;

            if (yli::load::load_symbiosis(
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
                        this->ofbx_mesh_count,
                        this->vram_buffer_in_use,
                        is_debug_mode))
            {
                std::cout << "number of meshes: " << this->ofbx_mesh_count << "\n";

                std::vector<const ofbx::Texture*> ofbx_diffuse_texture_pointer_vector;
                ofbx_diffuse_texture_pointer_vector.reserve(this->ofbx_diffuse_texture_mesh_map.size());
                this->biontID_symbiont_material_vector.resize(this->ofbx_mesh_count);

                this->biontID_symbiont_species_vector.resize(this->ofbx_mesh_count);

                for (auto key_and_value : this->ofbx_diffuse_texture_mesh_map)
                {
                    ofbx_diffuse_texture_pointer_vector.push_back(key_and_value.first); // key.
                }

                // Create `SymbiontMaterial`s.
                for (const ofbx::Texture* ofbx_texture : ofbx_diffuse_texture_pointer_vector)
                {
                    if (ofbx_texture == nullptr)
                    {
                        continue;
                    }

                    std::cout << "Creating yli::ontology::SymbiontMaterial* based on ofbx::Texture* at 0x" << std::hex << (uint64_t) ofbx_texture << std::dec << " ...\n";
                    yli::ontology::MaterialStruct material_struct;
                    material_struct.shader = this->parent;
                    material_struct.symbiosis = this;
                    material_struct.is_symbiont_material = true;
                    material_struct.ofbx_texture = ofbx_texture;
                    yli::ontology::SymbiontMaterial* symbiont_material = new yli::ontology::SymbiontMaterial(this->universe, material_struct);

                    std::cout << "yli::ontology::SymbiontMaterial* successfully created.\n";

                    // Create `SymbiontSpecies`s.
                    // Care only about `ofbx::Texture*`s which are DIFFUSE textures.
                    for (std::size_t mesh_i : this->ofbx_diffuse_texture_mesh_map.at(ofbx_texture))
                    {
                        yli::ontology::SpeciesStruct species_struct;
                        species_struct.is_symbiont_species = true;

                        if (this->parent != nullptr)
                        {
                            species_struct.scene = static_cast<yli::ontology::Scene*>(this->parent->get_parent());
                        }
                        else
                        {
                            species_struct.scene = nullptr;
                        }

                        species_struct.shader = this->parent;
                        species_struct.symbiont_material = symbiont_material;
                        species_struct.vertex_count = mesh_i < this->vertices.size() ? this->vertices.at(mesh_i).size() : 0;
                        species_struct.vertices = mesh_i < this->vertices.size() ? this->vertices.at(mesh_i) : std::vector<glm::vec3>();
                        species_struct.uvs = mesh_i < this->uvs.size() ? this->uvs.at(mesh_i) : std::vector<glm::vec2>();
                        species_struct.normals = mesh_i < this->normals.size() ? this->normals.at(mesh_i) : std::vector<glm::vec3>();
                        species_struct.light_position = this->light_position;
                        species_struct.vram_buffer_in_use = this->vram_buffer_in_use;

                        std::cout << "Creating yli::ontology::SymbiontSpecies*, mesh index " << mesh_i << "...\n";

                        yli::ontology::SymbiontSpecies* symbiont_species = new yli::ontology::SymbiontSpecies(this->universe, species_struct);

                        std::cout << "yli::ontology::SymbiontSpecies*, mesh index " << mesh_i << " successfully created.\n";

                        std::cout << "storing yli::ontology::SymbiontMaterial* symbiont_material into vector with mesh_i " << mesh_i << " ...\n";
                        this->biontID_symbiont_material_vector.at(mesh_i) = symbiont_material;
                        std::cout << "storing yli::ontology::SymbiontSpecies* symbiont_species into vector with mesh_i " << mesh_i << " ...\n";
                        this->biontID_symbiont_species_vector.at(mesh_i) = symbiont_species;

                        std::cout << "Success.\n";
                        // TODO: Compute the graph of each type to enable object vertex modification!
                    }
                }

                std::cout << "All symbionts successfully created.\n";
            }
        }

        yli::ontology::SymbiontMaterial* Symbiosis::get_symbiont_material(const std::size_t symbiont_material_i) const
        {
            if (symbiont_material_i >= this->symbiont_material_pointer_vector.size())
            {
                return nullptr;
            }

            return this->symbiont_material_pointer_vector[symbiont_material_i];
        }

        yli::ontology::SymbiontSpecies* Symbiosis::get_symbiont_species(const std::size_t biontID) const
        {
            if (biontID >= this->biontID_symbiont_species_vector.size())
            {
                return nullptr;
            }

            return this->biontID_symbiont_species_vector[biontID];
        }

        GLint Symbiosis::get_vertex_position_modelspaceID(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_vertex_position_modelspaceID();
        }

        GLint Symbiosis::get_vertexUVID(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_vertexUVID();
        }

        GLint Symbiosis::get_vertex_normal_modelspaceID(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_vertex_normal_modelspaceID();
        }

        uint32_t Symbiosis::get_vertexbuffer(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_vertexbuffer();
        }

        uint32_t Symbiosis::get_uvbuffer(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_uvbuffer();
        }

        uint32_t Symbiosis::get_normalbuffer(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_normalbuffer();
        }

        uint32_t Symbiosis::get_elementbuffer(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_elementbuffer();
        }

        std::vector<uint32_t> Symbiosis::get_indices(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_indices();
            // return this->indices.at(biontID);
        }

        std::size_t Symbiosis::get_indices_size(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector[biontID]->get_indices_size();
            // return this->indices.at(biontID).size();
        }

        std::size_t Symbiosis::get_number_of_ofbx_meshes() const
        {
            // the value of `ofbx_mesh_count` comes from OpenFBX.
            return this->ofbx_mesh_count;
        }

        bool Symbiosis::has_texture(const std::size_t biontID) const
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

        uint32_t Symbiosis::get_texture(const std::size_t biontID) const
        {
            return this->biontID_symbiont_material_vector.at(biontID)->get_texture();
        }

        GLint Symbiosis::get_openGL_textureID(const std::size_t biontID) const
        {
            return this->biontID_symbiont_material_vector.at(biontID)->get_openGL_textureID();
        }

        GLint Symbiosis::get_lightID(const std::size_t biontID) const
        {
            return this->biontID_symbiont_species_vector.at(biontID)->get_lightID();
        }

        const glm::vec3& Symbiosis::get_light_position(const std::size_t biontID) const
        {
            return this->light_position;
        }
    }
}
