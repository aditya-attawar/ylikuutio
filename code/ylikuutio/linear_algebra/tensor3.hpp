#ifndef __TENSOR3_HPP_INCLUDED
#define __TENSOR3_HPP_INCLUDED

#include "matrix.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    class Tensor3
    {
        // `class Tensor3` uses the same coordinate order as MATLAB,
        // to make testing easier. So: y, x, z.
        // y = 0 is the uppermost slice
        // x = 0 is the leftmost slice.
        // z = 0 is the front slice.

        public:
            // constructor.
            Tensor3(uint32_t height, uint32_t width, uint32_t depth);

            // copy constructor.
            Tensor3(linear_algebra::Tensor3& old_tensor3);
            Tensor3(std::shared_ptr<linear_algebra::Tensor3> old_matrix)
                : Tensor3(*old_matrix) { }

            // constructor.
            Tensor3(linear_algebra::Matrix& old_matrix);

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy2D
            {
                public:
                    Proxy2D(std::vector<std::vector<float>>& array_of_arrays) : array_of_arrays(array_of_arrays) { }

                    class Proxy
                    {
                        public:
                            Proxy(std::vector<float>& proxy_array) : proxy_array(proxy_array) { }

                            float& operator[](const uint32_t index)
                            {
                                return proxy_array[index];
                            }

                        private:
                            std::vector<float>& proxy_array;
                    };

                    Proxy operator[](const uint32_t index)
                    {
                        return array_of_arrays[index];
                    }

                private:
                    std::vector<std::vector<float>> array_of_arrays;
            };

            void operator<<(const float rhs);
            void operator<<(const std::vector<float>& rhs);
            bool operator==(linear_algebra::Tensor3& rhs);
            bool operator!=(linear_algebra::Tensor3& rhs);
            Proxy2D operator[](const uint32_t index)
            {
                return Proxy2D(array_of_arrays_of_arrays[index]);
            }

            bool is_cube;
            uint32_t width;
            uint32_t height;
            uint32_t depth;

        private:
            bool is_fully_populated;

            // For populating, the order of coordinates from
            // the one changing fastest to the one changing slowest is:
            // x, y, z
            int32_t next_x_to_populate;
            int32_t next_y_to_populate;
            int32_t next_z_to_populate;

            std::vector<std::vector<std::vector<float>>> array_of_arrays_of_arrays;
    };
}

#endif
