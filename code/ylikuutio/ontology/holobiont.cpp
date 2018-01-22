#include "holobiont.hpp"
#include "symbiosis.hpp"
#include "biont.hpp"
#include "entity_templates.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace ontology
{
    class Entity;

    void Holobiont::bind_biont(ontology::Biont* const biont)
    {
        // get `childID` from `Holobiont` and set pointer to `object`.
        hierarchy::bind_child_to_parent<ontology::Biont*>(
                biont,
                this->biont_pointer_vector,
                this->free_biontID_queue,
                &this->number_of_bionts);
    }

    void Holobiont::unbind_biont(const int32_t childID)
    {
        ontology::Biont* dummy_child_pointer = nullptr;
        hierarchy::set_child_pointer(
                childID,
                dummy_child_pointer,
                this->biont_pointer_vector,
                this->free_biontID_queue,
                &this->number_of_bionts);
    }

    void Holobiont::bind_to_parent()
    {
        // get `childID` from `Symbiosis` and set pointer to this `Holobiont`.
        this->symbiosis_parent->bind_holobiont(this);
    }

    void Holobiont::bind_to_new_parent(ontology::Symbiosis* const new_parent)
    {
        // this method sets pointer to this `Object` to nullptr, sets `parent` according to the input,
        // and requests a new `childID` from the new `Symbiosis`.

        // unbind from the old parent `Model`.
        this->symbiosis_parent->unbind_holobiont(this->childID);

        // get `childID` from `Model` and set pointer to this `Object`.
        new_parent->bind_holobiont(this);
    }

    Holobiont::~Holobiont()
    {
        // destructor.

        // set pointer to this `Holobiont` to nullptr.
        std::cout << "Holobiont with childID " << std::dec << this->childID << " will be destroyed.\n";
        this->symbiosis_parent->set_holobiont_pointer(this->childID, nullptr);
    }

    void Holobiont::render()
    {
        // render this `Holobiont`.

        if (this->should_ylikuutio_render_this_holobiont)
        {
            this->prerender();

            // render this `Scene` by calling `render()` function of each `Biont`.
            ontology::render_children<ontology::Biont*>(this->biont_pointer_vector);

            this->postrender();
        }
    }

    void Holobiont::create_bionts()
    {
        std::cout << "Creating bionts for Holobiont located at 0x" << std::hex << (uint64_t) this << std::dec << " ...\n";
        // Create `Biont` entities so that
        // they bind this `Holobiont`.
        int32_t correct_number_of_bionts = this->symbiosis_parent->get_number_of_symbionts();
        std::cout << "Number of bionts to be created: " << correct_number_of_bionts << "\n";

        for (int32_t biontID = 0; biontID < correct_number_of_bionts; biontID++)
        {
            BiontStruct biont_struct;
            biont_struct.biontID               = biontID;
            biont_struct.holobiont_parent      = this;
            biont_struct.original_scale_vector = this->original_scale_vector;
            biont_struct.rotate_angle          = this->rotate_angle;
            biont_struct.rotate_vector         = this->rotate_vector;
            biont_struct.initial_rotate_angle  = this->initial_rotate_angle;
            biont_struct.initial_rotate_vector = this->initial_rotate_vector;
            biont_struct.quaternions_in_use    = this->quaternions_in_use;
            biont_struct.cartesian_coordinates = std::make_shared<glm::vec3>(*this->cartesian_coordinates);
            biont_struct.translate_vector      = this->translate_vector;
            biont_struct.texture               = this->symbiosis_parent->get_texture(biontID);

            std::cout << "Creating biont with biontID " << biontID << " ...\n";

            ontology::Biont* biont = new ontology::Biont(this->universe, biont_struct);
        }
    }

    ontology::Entity* Holobiont::get_parent() const
    {
        return this->symbiosis_parent;
    }

    int32_t Holobiont::get_number_of_children() const
    {
        return this->number_of_bionts;
    }

    int32_t Holobiont::get_number_of_descendants() const
    {
        return 0;
    }

    void Holobiont::set_biont_pointer(const int32_t childID, ontology::Biont* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->biont_pointer_vector, this->free_biontID_queue, &this->number_of_bionts);
    }

    void Holobiont::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }
}
