#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "symbiosis.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include <ofbx.h>

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void SymbiontMaterial::bind_symbiont_species(yli::ontology::SymbiontSpecies* const symbiont_species)
        {
            // get `childID` from `SymbiontMaterial` and set pointer to `symbiont_species`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::SymbiontSpecies*>(
                    symbiont_species,
                    this->symbiont_species_pointer_vector,
                    this->free_symbiont_speciesID_queue,
                    this->number_of_symbiont_species);
        }

        void SymbiontMaterial::bind_to_parent()
        {
            // get `childID` from `Symbiosis` and set pointer to this `SymbiontMaterial`.
            this->parent->bind_symbiont_material(this);
        }

        SymbiontMaterial::~SymbiontMaterial()
        {
            // destructor.
            std::cout << "SymbiontMaterial with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all symbiont species of this symbiont material.
            std::cout << "All symbiont species of this symbiont material will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::SymbiontSpecies*>(this->symbiont_species_pointer_vector, this->number_of_symbiont_species);

            glDeleteTextures(1, &this->texture);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Symbiosis* const symbiosis = this->parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `SymbiontMaterial::~SymbiontMaterial`: `symbiosis` is `nullptr`!\n";
                return;
            }

            // set pointer to this symbiont_material to nullptr.
            symbiosis->unbind_symbiont_material(this->childID);
        }

        void SymbiontMaterial::render()
        {
            this->prerender();

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture);
            // Set our "myTextureSampler" sampler to user Texture Unit 0.
            glUniform1i(this->openGL_textureID, 0);

            // render this `SymbiontMaterial` by calling `render()` function of each `SymbiontSpecies`.
            yli::ontology::render_children<yli::ontology::SymbiontSpecies*>(this->symbiont_species_pointer_vector);

            this->postrender();
        }

        yli::ontology::Entity* SymbiontMaterial::get_parent() const
        {
            return this->parent;
        }

        std::size_t SymbiontMaterial::get_number_of_children() const
        {
            return this->number_of_symbiont_species;
        }

        std::size_t SymbiontMaterial::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->symbiont_species_pointer_vector);
        }

        void SymbiontMaterial::set_symbiont_species_pointer(const std::size_t childID, yli::ontology::SymbiontSpecies* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(
                    childID, child_pointer,
                    this->symbiont_species_pointer_vector,
                    this->free_symbiont_speciesID_queue,
                    this->number_of_symbiont_species);
        }

        void SymbiontMaterial::load_texture()
        {
            this->texture = yli::loaders::load_FBX_texture(this->ofbx_texture);

            // Get a handle for our "myTextureSampler" uniform.
            yli::ontology::Symbiosis* symbiosis = static_cast<yli::ontology::Symbiosis*>(this->parent);
            yli::ontology::Shader* shader = static_cast<yli::ontology::Shader*>(symbiosis->get_parent());
            this->openGL_textureID = glGetUniformLocation(shader->get_programID(), "myTextureSampler");
        }

        GLuint SymbiontMaterial::get_texture() const
        {
            return this->texture;
        }

        GLuint SymbiontMaterial::get_openGL_textureID() const
        {
            return this->openGL_textureID;
        }
    }
}
