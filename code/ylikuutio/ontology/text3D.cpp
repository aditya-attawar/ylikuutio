#include "text3D.hpp"
#include "vector_font.hpp"
#include "object.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace ylikuutio
{
    namespace ontology
    {
        class Object;

        void Text3D::bind_to_parent()
        {
            // get `childID` from `VectorFont` and set pointer to this `Text3D`.
            this->parent->bind_text3D(this);
        }

        Text3D::~Text3D()
        {
            // destructor.
            std::cout << "This 3D text (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";

            // destroy all objects of this `Text3D`.
            std::cout << "All objects (" << this->object_pointer_vector.size() << " pieces) of this 3D text will be destroyed.\n";
            hierarchy::delete_children<ylikuutio::ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

            this->parent->set_text3D_pointer(this->childID, nullptr);
        }

        ylikuutio::ontology::Entity* Text3D::get_parent() const
        {
            return this->parent;
        }

        int32_t Text3D::get_number_of_children() const
        {
            return this->number_of_objects;
        }

        int32_t Text3D::get_number_of_descendants() const
        {
            return -1;
        }

        void Text3D::set_object_pointer(const int32_t childID, ylikuutio::ontology::Object* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
        }
    }
}
