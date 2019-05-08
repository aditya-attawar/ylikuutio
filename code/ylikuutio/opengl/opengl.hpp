#ifndef __OPENGL_HPP_INCLUDED
#define __OPENGL_HPP_INCLUDED

#include "code/ylikuutio/memory/memory_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli
{
    namespace opengl
    {
        bool init_glew();
        void enable_depth_test();
        void disable_depth_test();
        void set_depth_func_to_less();
        void cull_triangles();
        void set_background_color(const float red, const float green, const float blue, const float alpha);
        void set_filtering_parameters();
        void set_wireframe(const bool wireframe);
        std::size_t get_n_color_channels(const GLenum format);
        std::size_t get_size_of_component(const GLenum type);

        template<class T1>
            std::shared_ptr<std::vector<T1>> copy_data_from_gpu_texture_to_cpu_array(
                    const GLenum format,
                    const GLenum type,
                    const std::size_t texture_width,
                    const std::size_t texture_height,
                    const bool should_ylikuutio_flip_texture)
            {
                // Transfer data from the GPU texture to a CPU array.
                const std::size_t n_color_channels = yli::opengl::get_n_color_channels(format);
                const std::size_t size_of_texel_in_bytes = n_color_channels * yli::opengl::get_size_of_component(type);
                const std::size_t n_texels = texture_width * texture_height;
                const std::size_t size_of_texture_in_bytes = size_of_texel_in_bytes * n_texels;
                T1* const result_array = new T1[size_of_texture_in_bytes];

                glReadBuffer(GL_COLOR_ATTACHMENT0);
                glReadPixels(0, 0, texture_width, texture_height, format, type, result_array);

                if (should_ylikuutio_flip_texture)
                {
                    yli::memory::flip_vertically(result_array, size_of_texel_in_bytes * texture_width, texture_height);
                }

                std::shared_ptr<std::vector<T1>> result_vector = std::make_shared<std::vector<T1>>(result_array, result_array + size_of_texture_in_bytes);

                delete[] result_array;

                return result_vector;
            }
    }
}

#endif
