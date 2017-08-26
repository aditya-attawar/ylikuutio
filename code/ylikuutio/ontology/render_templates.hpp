#ifndef __RENDER_TEMPLATES_HPP_INCLUDED
#define __RENDER_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    template<class T1>
        void render_children(std::vector<T1>& child_pointer_vector)
        {
            for (uint32_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                T1 child_pointer;
                child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                if (child_pointer != nullptr)
                {
                    child_pointer->render();
                }
            }
        }
}

#endif