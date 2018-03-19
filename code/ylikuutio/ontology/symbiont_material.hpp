#ifndef __SYMBIONT_MATERIAL_HPP_INCLUDED
#define __SYMBIONT_MATERIAL_HPP_INCLUDED

#include "material.hpp"
#include "symbiosis.hpp"
#include "material_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/loaders/texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"
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
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class SymbiontSpecies;

    class SymbiontMaterial: public ontology::Material
    {
        public:
            // destructor.
            virtual ~SymbiontMaterial();

        private:
            void bind(ontology::SymbiontSpecies* const symbiont_species);

            // constructor.
            SymbiontMaterial(ontology::Universe* const universe, const MaterialStruct& material_struct)
                : Material(universe, material_struct)
            {
                // constructor.
                this->parent = material_struct.symbiosis;

                this->ofbx_texture = material_struct.ofbx_texture;

                this->number_of_symbiont_species = 0;

                // get `childID` from the `Symbiosis` and set pointer to this `SymbiontMaterial`.
                this->bind_to_parent();

                this->load_texture();

                this->child_vector_pointers_vector.push_back(&this->symbiont_species_pointer_vector);
                this->type = "ontology::SymbiontMaterial*";
            }

            // this method sets pointer to this `SymbiontMaterial` to `nullptr`,
            // sets `parent` according to the input, and
            // requests a new `childID` from the new `Symbiosis`.
            void set_name(const std::string& name);

            // this method sets `SymbiontSpecies` pointer.
            void set_symbiont_species_pointer(const int32_t childID, ontology::SymbiontSpecies* const child_pointer);

            GLuint get_texture() const;
            GLuint get_openGL_textureID() const;

            friend class Symbiosis;
            friend class SymbiontSpecies;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1>
                friend void render_children(const std::vector<T1>& child_pointer_vector);

            void bind_to_parent();

            void load_texture();

            // this method renders all `SymbiontSpecies` using this `SymbiontMaterial`.
            void render();

            ontology::Entity* get_parent() const override;
            int32_t get_number_of_children() const override;
            int32_t get_number_of_descendants() const override;

            ontology::Symbiosis* parent;           // pointer to `Symbiosis`.

            const ofbx::Texture* ofbx_texture;

            GLuint texture;                        // Texture of this `SymbiontMaterial`.
            GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

            std::vector<ontology::SymbiontSpecies*> symbiont_species_pointer_vector;
            std::queue<int32_t> free_symbiont_speciesID_queue;
            int32_t number_of_symbiont_species;
    };
}

#endif
