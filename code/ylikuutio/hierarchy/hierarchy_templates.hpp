#ifndef __HIERARCHY_TEMPLATES_HPP_INCLUDED
#define __HIERARCHY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <queue>         // std::queue
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace hierarchy
    {
        template<class T1>
            void set_child_pointer(
                    const std::size_t childID,
                    const T1 child_pointer,
                    std::vector<T1>& child_pointer_vector,
                    std::queue<std::size_t>& free_childID_queue,
                    std::size_t& number_of_children)
            {
                // requirements:
                // `childID` must not be `std::numeric_limits<std::size_t>::max()`.
                //     (`std::numeric_limits<std::size_t>::max()` as `childID` value means that `childID` is uninitialized).

                if (childID == std::numeric_limits<std::size_t>::max())
                {
                    return;
                }

                child_pointer_vector[childID] = child_pointer;

                if (child_pointer == nullptr)
                {
                    if (childID == child_pointer_vector.size() - 1)
                    {
                        // OK, this is the biggest childID of all childID's of this 'object'.
                        // We can reduce the size of the child pointer vector at least by 1.
                        while ((!child_pointer_vector.empty()) && (child_pointer_vector.back() == nullptr))
                        {
                            // Reduce the size of child pointer vector by 1.
                            child_pointer_vector.pop_back();
                        }
                    }

                    // 1 child less.
                    if (number_of_children > 0)
                    {
                        number_of_children--;
                    }
                }
                else
                {
                    // 1 child more.
                    number_of_children++;
                }
            }

        template<class T1>
            std::size_t get_childID(std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue)
            {
                // This function is called eg. from `bind_child_to_parent`,
                // so that child instance gets an appropriate `childID`.
                std::size_t childID;

                while (!free_childID_queue.empty())
                {
                    // return the first (oldest) free childID.
                    childID = free_childID_queue.front();
                    free_childID_queue.pop();

                    // check that the child index does not exceed current child pointer vector.
                    if (childID < child_pointer_vector.size())
                    {
                        // OK, it does not exceed current child pointer vector.
                        return childID;
                    }
                }

                // OK, the queue is empty.
                // A new child index must be created.
                childID = child_pointer_vector.size();

                // child pointer vector must also be extended with an appropriate nullptr pointer.
                child_pointer_vector.push_back(nullptr);

                return childID;
            }

        template<class T1>
            void bind_child_to_parent(
                    const T1 child_pointer,
                    std::vector<T1>& child_pointer_vector,
                    std::queue<std::size_t>& free_childID_queue,
                    std::size_t& number_of_children)
            {
                // If a class' instances have parents, this function must be
                // called in the constructor. The call must be done only once
                // in each constructor, usually after setting
                // `this->parent`. So, get `childID` from the parent,
                // because every child deserves a unique ID!
                //
                // requirements:
                // `child_pointer` must not be `nullptr` (use `this` as the first argument).
                child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
                // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
                set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue, number_of_children);
            }

        template<class T1>
            void bind_child_to_parent(
                    const std::string child_name,
                    std::unordered_map<std::string, T1>& child_hash_map,
                    const T1 child_pointer,
                    std::vector<T1>& child_pointer_vector,
                    std::queue<std::size_t>& free_childID_queue,
                    std::size_t& number_of_children)
            {
                // If a class' instances have parents, this function must be
                // called in the constructor. The call must be done only once
                // in each constructor, usually after setting
                // `this->parent`. So, get `childID` from the parent,
                // because every child deserves a unique ID!

                if (!child_name.empty())
                {
                    // if the child has a name, let the parent know it!
                    child_hash_map[child_name] = child_pointer;
                }

                child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
                // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
                set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue, number_of_children);
            }

        template <class T1>
            void unbind_child_from_parent(
                    const std::size_t childID,
                    std::vector<T1>& child_pointer_vector,
                    std::queue<std::size_t>& free_childID_queue,
                    std::size_t& number_of_children)
            {
                // requirements:
                // `child_pointer->childID` must not be `std::numeric_limits<std::size_t>::max()`.
                //     (`std::numeric_limits<std::size_t>::max()` as `childID` value means that `childID` is uninitialized).

                if (childID == std::numeric_limits<std::size_t>::max())
                {
                    return;
                }

                // Set pointer to this child to `nullptr` in the old parent.
                set_child_pointer(childID, static_cast<T1>(nullptr), child_pointer_vector, free_childID_queue, number_of_children);
            }

        template<class T1>
            void delete_children(std::vector<T1>& child_pointer_vector, std::size_t& number_of_children)
            {
                for (std::size_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
                {
                    delete child_pointer_vector[child_i];
                }

                number_of_children = 0; // no children any more.
            }
    }
}

#endif
