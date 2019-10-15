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

#include "biont.hpp"
#include "shader.hpp"
#include "holobiont.hpp"
#include "symbiosis.hpp"
#include "symbiont_species.hpp"
#include "biont_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;

        void Biont::bind_to_parent()
        {
            // Requirements:
            // `this->holobiont_parent` must not be `nullptr`.

            yli::ontology::Holobiont* const holobiont = this->holobiont_parent;

            if (holobiont == nullptr)
            {
                std::cerr << "ERROR: `Biont::bind_to_parent`: `holobiont` is `nullptr`!\n";
                return;
            }

            // Get `childID` from `Holobiont` and set pointer to this `Biont`.
            holobiont->bind_Biont(this);
        }

        void Biont::bind_to_SymbiontSpecies()
        {
            // Requirements:
            // `this->holobiont_parent` must not be `nullptr`.
            // `this->holobiont_parent->get_parent()` must not be `nullptr`.
            // `this->symbiont_species` must not be `nullptr`.

            const yli::ontology::Holobiont* const holobiont = this->holobiont_parent;

            if (holobiont == nullptr)
            {
                std::cerr << "ERROR: `Biont::bind_to_SymbiontSpecies`: `holobiont` is `nullptr`!\n";
                return;
            }

            const yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(holobiont->get_parent());

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Biont::bind_to_SymbiontSpecies`: `symbiosis` is `nullptr`!\n";
                return;
            }

            yli::ontology::SymbiontSpecies* const symbiont_species = this->symbiont_species;

            if (symbiont_species == nullptr)
            {
                std::cerr << "ERROR: `Biont::bind_to_SymbiontSpecies`: `symbiont_species` is `nullptr`!\n";
                return;
            }

            symbiont_species->bind_Biont(this);
        }

        void Biont::bind_to_new_parent(yli::ontology::Holobiont* const new_holobiont_parent)
        {
            // This method sets pointer to this `Biont` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Holobiont`.
            //
            // Requirements:
            // `this->holobiont_parent` must not be `nullptr`.
            // `new_holobiont_parent` must not be `nullptr`.

            // Unbind from the old parent `Holobiont`.
            if (this->holobiont_parent == nullptr)
            {
                std::cerr << "ERROR: `Biont::bind_to_new_parent`: `this->holobiont_parent` is `nullptr`!\n";
                return;
            }

            if (new_holobiont_parent == nullptr)
            {
                std::cerr << "ERROR: `Biont::bind_to_new_parent`: `new_holobiont_parent` is `nullptr`!\n";
                return;
            }

            this->holobiont_parent->unbind_Biont(this->childID);

            // Get `childID` from `Holobiont` and set pointer to this `Biont`.
            this->holobiont_parent = new_holobiont_parent;
            this->holobiont_parent->bind_Biont(this);
        }

        Biont::~Biont()
        {
            // destructor.
            //
            // Requirements:
            // `this->holobiont_parent` must not be `nullptr`.
            // `this->symbiont_species` must not be `nullptr`.

            std::cout << "Biont with childID " << std::dec << this->childID << " will be destroyed.\n";

            yli::ontology::Holobiont* const holobiont = this->holobiont_parent;

            if (holobiont == nullptr)
            {
                std::cerr << "ERROR: `Biont::~Biont`: `holobiont` is `nullptr`!\n";
                return;
            }

            yli::ontology::SymbiontSpecies* const symbiont_species = this->symbiont_species;

            if (symbiont_species == nullptr)
            {
                std::cerr << "ERROR: `Biont::~Biont`: `symbiont_species` is `nullptr`!\n";
                return;
            }

            // Set pointer to this `Biont` to `nullptr`.
            symbiont_species->unbind_Biont(this->childID);
            holobiont->unbind_Biont(this->childID);
        }

        void Biont::render()
        {
            // Render this `Biont`.
            //
            // Requirements:
            // `this->holobiont_parent` must not be `nullptr`.
            // `this->holobiont_parent->get_parent()` must not be `nullptr`.

            const yli::ontology::Holobiont* const holobiont = this->holobiont_parent;

            if (holobiont == nullptr)
            {
                std::cerr << "ERROR: `Biont::render`: `holobiont` is `nullptr`!\n";
                return;
            }

            const yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(holobiont->get_parent());

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Biont::render`: `symbiosis` is `nullptr`!\n";
                return;
            }

            if (this->should_ylikuutio_render_this_biont)
            {
                this->prerender();
                this->render_this_biont(static_cast<yli::ontology::Shader*>(symbiosis->get_parent()));
                this->postrender();
            }
        }

        void Biont::render_this_biont(const yli::ontology::Shader* const shader)
        {
            // Requirements:
            // `this->universe` must not be `nullptr`.
            // `shader` must not be `nullptr`.
            // `this->holobiont_parent` must not be `nullptr`.
            // `this->symbiont_species` must not be `nullptr`.

            yli::ontology::Universe* const universe = this->universe;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `Biont::render_this_biont`: `universe` is `nullptr`!\n";
                return;
            }

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Biont::render_this_biont`: `shader` is `nullptr`!\n";
                return;
            }

            const yli::ontology::Holobiont* const holobiont = this->holobiont_parent;

            if (holobiont == nullptr)
            {
                std::cerr << "ERROR: `Biont::render_this_biont`: `holobiont` is `nullptr`!\n";
                return;
            }

            yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(holobiont->get_parent());

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Biont::render_this_biont`: `symbiosis` is `nullptr`!\n";
                return;
            }

            const yli::ontology::SymbiontSpecies* const symbiont_species = this->symbiont_species;

            if (symbiont_species == nullptr)
            {
                std::cerr << "ERROR: `Biont::render_this_biont`: `symbiont_species` is `nullptr`!\n";
                return;
            }

            this->model_matrix = glm::mat4(1.0f);

            const std::string model_file_format = symbiosis->get_model_file_format();

            if (model_file_format == "fbx" || model_file_format == "FBX")
            {
                // Only FBX objects need initial rotation.
                this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angle, this->initial_rotate_vector);
            }

            this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);
            glm::vec3 euler_angles { 0.0f, holobiont->horizontal_angle, holobiont->vertical_angle };
            glm::quat my_quaternion = glm::quat(euler_angles);
            glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
            this->model_matrix[3][0] = 0.0f;
            this->model_matrix[3][1] = 0.0f;
            this->model_matrix[3][2] = 0.0f;
            this->model_matrix = rotation_matrix * this->model_matrix;
            this->model_matrix[3][0] = holobiont->cartesian_coordinates.x;
            this->model_matrix[3][1] = holobiont->cartesian_coordinates.y;
            this->model_matrix[3][2] = holobiont->cartesian_coordinates.z;

            this->MVP_matrix = universe->get_projection_matrix() * universe->get_view_matrix() * this->model_matrix;

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, symbiosis->get_texture(this->biontID));
            // Set our "texture_sampler" sampler to user Texture Unit 0.
            yli::opengl::uniform_1i(symbiosis->get_openGL_textureID(this->biontID), 0);

            // '`Material`' part ends here.

            // '`Species`' part begins here.

            // Compute the MVP matrix from keyboard and mouse input.
            const glm::vec3& light_position = symbiosis->get_light_position(this->biontID);
            glUniform3f(
                    symbiosis->get_lightID(this->biontID),
                    light_position.x,
                    light_position.y,
                    light_position.z);

            // 1st attribute buffer : vertices.
            yli::opengl::enable_vertex_attrib_array(symbiont_species->get_vertex_position_modelspaceID());

            // 2nd attribute buffer : UVs.
            yli::opengl::enable_vertex_attrib_array(symbiont_species->get_vertexUVID());

            // 3rd attribute buffer : normals.
            yli::opengl::enable_vertex_attrib_array(symbiont_species->get_vertex_normal_modelspaceID());

            // '`Species`' part ends here.

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            glUniformMatrix4fv(shader->get_matrixID(), 1, GL_FALSE, &this->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader->get_model_matrixID(), 1, GL_FALSE, &this->model_matrix[0][0]);

            uint32_t vertexbuffer = symbiont_species->get_vertexbuffer();
            uint32_t vertex_position_modelspaceID = symbiont_species->get_vertex_position_modelspaceID();
            uint32_t uvbuffer = symbiont_species->get_uvbuffer();
            uint32_t vertexUVID = symbiont_species->get_vertexUVID();
            uint32_t normalbuffer = symbiont_species->get_normalbuffer();
            uint32_t vertex_normal_modelspaceID = symbiont_species->get_vertex_normal_modelspaceID();
            uint32_t elementbuffer = symbiont_species->get_elementbuffer();
            uint32_t indices_size = symbiont_species->get_indices_size();

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertex_position_modelspaceID, // The attribute we want to configure
                    3,                            // size
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    (void*) 0                     // array buffer offset
                    );

            // 2nd attribute buffer : UVs.
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                    vertexUVID,                   // The attribute we want to configure
                    2,                            // size : U+V => 2
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    (void*) 0                     // array buffer offset
                    );

            // 3rd attribute buffer : normals.
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glVertexAttribPointer(
                    vertex_normal_modelspaceID,   // The attribute we want to configure
                    3,                            // size
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    (void*) 0                     // array buffer offset
                    );

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,                 // mode
                    indices_size,                 // count
                    GL_UNSIGNED_INT,              // type
                    (void*) 0                     // element array buffer offset
                    );
        }

        yli::ontology::Entity* Biont::get_parent() const
        {
            return this->holobiont_parent;
        }

        std::size_t Biont::get_number_of_children() const
        {
            return 0; // `Biont` has no children.
        }

        std::size_t Biont::get_number_of_descendants() const
        {
            return 0; // `Biont` has no children.
        }
    }
}
