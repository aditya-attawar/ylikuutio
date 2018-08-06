#include "holobiont.hpp"
#include "symbiosis.hpp"
#include "biont.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;

        void Holobiont::bind_biont(yli::ontology::Biont* const biont)
        {
            // get `childID` from `Holobiont` and set pointer to `object`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Biont*>(
                    biont,
                    this->biont_pointer_vector,
                    this->free_biontID_queue,
                    &this->number_of_bionts);
        }

        void Holobiont::unbind_biont(const std::size_t childID)
        {
            yli::ontology::Biont* dummy_child_pointer = nullptr;
            yli::hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->biont_pointer_vector,
                    this->free_biontID_queue,
                    &this->number_of_bionts);
        }

        void Holobiont::bind_to_parent()
        {
            // requirements:
            // `this->symbiosis_parent` must not be `nullptr`.
            yli::ontology::Symbiosis* const symbiosis = this->symbiosis_parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::bind_to_parent`: `symbiosis` is `nullptr`!\n";
                return;
            }

            // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
            symbiosis->bind_holobiont(this);
        }

        void Holobiont::bind_to_new_parent(yli::ontology::Symbiosis* const new_parent)
        {
            // this method sets pointer to this `Holobiont` to `nullptr`, sets `symbiosis_parent` according to the input,
            // and requests a new `childID` from the new `Symbiosis`.
            //
            // requirements:
            // `this->symbiosis_parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Symbiosis* const symbiosis = this->symbiosis_parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::bind_to_new_parent`: `symbiosis` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Holobiont::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Symbiosis`.
            symbiosis->unbind_holobiont(this->childID);

            // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
            this->symbiosis_parent = new_parent;
            this->symbiosis_parent->bind_holobiont(this);
        }

        Holobiont::~Holobiont()
        {
            // destructor.
            std::cout << "Holobiont with childID " << std::dec << this->childID << " will be destroyed.\n";

            std::cout << "All bionts of this holobiont will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Biont*>(this->biont_pointer_vector, &this->number_of_bionts);

            // set pointer to this `Holobiont` to nullptr.
            this->symbiosis_parent->set_holobiont_pointer(this->childID, nullptr);
        }

        void Holobiont::render()
        {
            // render this `Holobiont`.

            if (this->should_ylikuutio_render_this_holobiont)
            {
                this->prerender();

                // render this `Holobiont` by calling `render()` function of each `Biont`.
                yli::ontology::render_children<yli::ontology::Biont*>(this->biont_pointer_vector);

                this->postrender();
            }
        }

        void Holobiont::create_bionts()
        {
            std::cout << "Creating bionts for Holobiont located at 0x" << std::hex << (uint64_t) this << std::dec << " ...\n";
            // Create `Biont` entities so that
            // they bind this `Holobiont`.
            const std::size_t correct_number_of_bionts = this->symbiosis_parent->get_number_of_symbionts();
            std::cout << "Number of bionts to be created: " << correct_number_of_bionts << "\n";

            for (std::size_t biontID = 0; biontID < correct_number_of_bionts; biontID++)
            {
                if (!this->symbiosis_parent->has_texture(biontID))
                {
                    std::cout << "There is no texture for biont with biontID " << biontID << "\n";
                    continue;
                }

                BiontStruct biont_struct;
                biont_struct.biontID               = biontID;
                biont_struct.holobiont_parent      = this;
                biont_struct.symbiont_species      = this->symbiosis_parent->get_symbiont_species(biontID);
                biont_struct.original_scale_vector = this->original_scale_vector;
                biont_struct.rotate_angle          = this->rotate_angle;
                biont_struct.rotate_vector         = this->rotate_vector;
                biont_struct.initial_rotate_angle  = this->initial_rotate_angle;
                biont_struct.initial_rotate_vector = this->initial_rotate_vector;
                biont_struct.quaternions_in_use    = this->quaternions_in_use;
                biont_struct.cartesian_coordinates = this->cartesian_coordinates;
                biont_struct.translate_vector      = this->translate_vector;

                std::cout << "Creating biont with biontID " << biontID << " ...\n";

                new yli::ontology::Biont(this->universe, biont_struct);
            }
        }

        void Holobiont::update_x(float x)
        {
            this->cartesian_coordinates.x = x;
            this->model_matrix[3][0] = x;

            for (yli::ontology::Biont* biont : this->biont_pointer_vector)
            {
                if (biont != nullptr)
                {
                    biont->cartesian_coordinates.x = x;
                    biont->model_matrix[3][0] = x;
                }
            }
        }

        void Holobiont::update_y(float y)
        {
            this->cartesian_coordinates.y = y;
            this->model_matrix[3][1] = y;

            for (yli::ontology::Biont* biont : this->biont_pointer_vector)
            {
                if (biont != nullptr)
                {
                    biont->cartesian_coordinates.y = y;
                    biont->model_matrix[3][1] = y;
                }
            }
        }

        void Holobiont::update_z(float z)
        {
            this->cartesian_coordinates.z = z;
            this->model_matrix[3][2] = z;

            for (yli::ontology::Biont* biont : this->biont_pointer_vector)
            {
                if (biont != nullptr)
                {
                    biont->cartesian_coordinates.z = z;
                    biont->model_matrix[3][2] = z;
                }
            }
        }

        yli::ontology::Entity* Holobiont::get_parent() const
        {
            return this->symbiosis_parent;
        }

        std::size_t Holobiont::get_number_of_children() const
        {
            return this->number_of_bionts;
        }

        std::size_t Holobiont::get_number_of_descendants() const
        {
            return 0; // TODO; write the code!
        }

        void Holobiont::set_biont_pointer(const std::size_t childID, yli::ontology::Biont* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->biont_pointer_vector, this->free_biontID_queue, &this->number_of_bionts);
        }
    }
}
