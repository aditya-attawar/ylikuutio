#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "bmp_heightmap_loader.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/common/global_variables.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    bool load_BMP_world(
            std::string image_path,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            uint32_t &image_width,
            uint32_t &image_height,
            std::string color_channel,
            uint32_t x_step,
            uint32_t z_step,
            std::string triangulation_type)
    {
        std::cout << "Loading BMP file " << image_path << " ...\n";

        uint8_t header_size = 54;

        // Data read from the header of the BMP file
        uint8_t header[header_size];
        uint32_t image_size;
        // Actual RGB image data.
        uint8_t *image_data;

        // Open the file
        const char* char_image_path = image_path.c_str();
        std::FILE* file = std::fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << image_path << " could not be opened.\n";
            return false;
        }

        // Read the header, i.e. the 54 first bytes

        // If less than 54 bytes are read, it's a problem.
        if (std::fread(header, 1, header_size, file) != header_size)
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return false;
        }

        // The start offset of pixel array in file.
        uint32_t pixel_array_start_offset = header[0x0a];

        // A BMP files always begins with "BM"
        if ((header[0] != 'B') || (header[1] != 'M'))
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return false;
        }

        // Make sure this is a 24bpp file
        if (*(uint32_t*) &header[0x1e] != 0)
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return false;
        }

        if (*(uint32_t*) &header[0x1c] != 24)
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return false;
        }

        // Read the information about the image
        image_size = *(uint32_t*) &header[0x22];
        image_width = *(int32_t*) &header[0x12];
        image_height = *(int32_t*) &header[0x16];

        // Define world size.
        uint32_t world_size = image_width * image_height;

        uint32_t line_size_in_bytes = image_size / image_height;

        std::cout << "image size is " << image_size << " bytes.\n";

        // Some BMP files are misformatted, guess missing information
        if (image_size == 0)
        {
            image_size = image_width * image_height * 3; // 3 : one byte for each Red, Green and Blue component
        }

        // Create a buffer.
        image_data = new uint8_t[image_size];

        if (image_data == nullptr)
        {
            std::cerr << "Reserving memory for image data failed.\n";
            std::fclose(file);
            return false;
        }

        // Move file pointer to the start of the pixel array.
        if (std::fseek(file, pixel_array_start_offset, SEEK_SET) != 0)
        {
            std::cerr << "Moving BMP file position indicator failed.\n";
            std::fclose(file);
            delete image_data;
            return false;
        }

        // Read the actual image data from the file into the buffer.
        if (std::fread(image_data, 1, image_size, file) != image_size)
        {
            std::cerr << "Reading image data from file failed.\n";
            std::fclose(file);
            delete image_data;
            return false;
        }

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        uint8_t *image_pointer;
        image_pointer = image_data;

        float* vertex_data;
        vertex_data = new float[world_size];

        if (vertex_data == nullptr)
        {
            std::cerr << "Reserving memory for vertex data failed.\n";
            delete image_data;
            return false;
        }

        float* vertex_pointer;
        vertex_pointer = vertex_data;

        const char* char_color_channel = color_channel.c_str();

        // start processing image_data.
        for (uint32_t z = 0; z < image_height; z++)
        {
            image_pointer = image_data + z * line_size_in_bytes;

            for (int32_t x = 0; x < image_width; x++)
            {
                uint32_t y;

                if (std::strcmp(char_color_channel, "blue") == 0)
                {
                    y = static_cast<float>(*image_pointer);       // y-coordinate is the blue (B) value.
                }
                else if (std::strcmp(char_color_channel, "green") == 0)
                {
                    y = static_cast<float>(*(image_pointer + 1)); // y-coordinate is the green (G) value.
                }
                else if (std::strcmp(char_color_channel, "red") == 0)
                {
                    y = static_cast<float>(*(image_pointer + 2)); // y-coordinate is the red (R) value.
                }
                // y-coordinate is the mean of R, G, & B.
                else if ((std::strcmp(char_color_channel, "mean") == 0) || (std::strcmp(char_color_channel, "all") == 0))
                {
                    y = (static_cast<float>(*image_pointer) + static_cast<float>(*(image_pointer + 1)) + static_cast<float>(*(image_pointer + 2))) / 3.0f;
                }
                else
                {
                    std::cerr << "invalid color channel!\n";
                    delete image_data;
                    delete vertex_data;
                    return false;
                }

                *vertex_pointer++ = y;
                image_pointer += 3; // R, G, & B.
            }
        }

        delete image_data;

        std::cout << "color channel in use: " << color_channel << "\n";

        TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height;
        triangulate_quads_struct.x_step = x_step;
        triangulate_quads_struct.z_step = z_step;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = NAN;
        triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

        bool result = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete vertex_data;
        return result;
    }
}
