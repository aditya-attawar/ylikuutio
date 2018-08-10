#ifndef __TENSOR3_HPP_INCLUDED
#define __TENSOR3_HPP_INCLUDED

#include "matrix.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli
{
    namespace linear_algebra
    {
        class Tensor3
        {
            // `class Tensor3` uses the coordinate order x, y, z:
            // x = 0 is the leftmost slice.
            // y = 0 is the uppermost slice
            // z = 0 is the front slice.

            public:
                // constructor.
                Tensor3(std::size_t width, std::size_t height, std::size_t depth);

                // copy constructor.
                Tensor3(const yli::linear_algebra::Tensor3& old_tensor3);
                Tensor3(std::shared_ptr<yli::linear_algebra::Tensor3> old_matrix)
                    : Tensor3(*old_matrix) { }

                // constructor.
                Tensor3(const yli::linear_algebra::Matrix& old_matrix);

                // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
                class Proxy2D
                {
                    public:
                        Proxy2D(const std::vector<std::vector<float>>& array_of_arrays) : array_of_arrays(array_of_arrays) { }

                        class Proxy
                        {
                            public:
                                Proxy(std::vector<float>& proxy_array) : proxy_array(proxy_array) { }

                                float& operator[](const std::size_t index)
                                {
                                    return proxy_array[index];
                                }

                            private:
                                std::vector<float>& proxy_array;
                        };

                        Proxy operator[](const std::size_t index)
                        {
                            return array_of_arrays[index];
                        }

                    private:
                        std::vector<std::vector<float>> array_of_arrays;
                };

                void operator<<(const float rhs);
                void operator<<(const std::vector<float>& rhs);
                bool operator==(const yli::linear_algebra::Tensor3& rhs);
                bool operator!=(const yli::linear_algebra::Tensor3& rhs);
                Proxy2D operator[](const std::size_t index)
                {
                    return Proxy2D(this->array_of_arrays_of_arrays[index]);
                }

                bool is_cube;
                std::size_t width;
                std::size_t height;
                std::size_t depth;

            private:
                bool is_fully_populated;

                // For populating, the order of coordinates from
                // the one changing fastest to the one changing slowest is:
                // x, y, z
                std::size_t next_x_to_populate;
                std::size_t next_y_to_populate;
                std::size_t next_z_to_populate;

                std::vector<std::vector<std::vector<float>>> array_of_arrays_of_arrays;
        };
    }
}

#endif
