#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "heightmap_loader.hpp"
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
#include <iomanip>  // std::setfill, std::setw
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    bool load_BMP_world(
            std::string image_path,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            uint32_t &image_width,
            uint32_t &image_height,
            std::string color_channel,
            std::string triangulation_type)
    {
        std::cout << "Loading BMP file " << image_path << " ...\n";

        // Data read from the header of the BMP file
        uint8_t header[54];
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
        if (std::fread(header, 1, 54, file) != 54)
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        // A BMP files always begins with "BM"
        if ((header[0] != 'B') || (header[1] != 'M'))
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        // Make sure this is a 24bpp file
        if (*(uint32_t*) &header[0x1e] != 0)
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        if (*(uint32_t*) &header[0x1c] != 24)
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        // Read the information about the image
        image_size = *(uint32_t*) &header[0x22];
        image_width = *(uint32_t*) &header[0x12];
        image_height = *(uint32_t*) &header[0x16];

        // Define world size.
        uint32_t world_size = image_width * image_height;

        // Some BMP files are misformatted, guess missing information
        if (image_size == 0)
        {
            image_size = image_width * image_height * 3; // 3 : one byte for each Red, Green and Blue component
        }

        // Create a buffer.
        image_data = new uint8_t[image_size];

        // Read the actual image data from the file into the buffer.
        std::fread(image_data, 1, image_size, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        uint8_t *image_pointer;
        image_pointer = image_data;

        float* vertex_data;
        vertex_data = new float[world_size];

        float* vertex_pointer;
        vertex_pointer = vertex_data;

        const char* char_color_channel = color_channel.c_str();

        // start processing image_data.
        for (int32_t z = image_height - 1; z >= 0; z--)
        {
            uint32_t image_width_in_bytes = 3 * image_width;
            image_pointer = image_data + z * image_width_in_bytes;

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

                // std::cout << color_channel << " color channel value at (" << x << ", " << z << "): " << y << ".\n";
                *vertex_pointer++ = y;
                image_pointer += 3; // R, G, & B.
            }
        }

        delete image_data;

        std::cout << "color channel in use: " << color_channel << "\n";

        TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = NAN;
        triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

        bool result = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete vertex_data;
        return result;
    }

    bool load_SRTM_world(
            std::string image_path,
            float latitude,
            float longitude,
            float world_radius,
            float divisor,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            std::string triangulation_type)
    {
        // For SRTM worlds, the right heightmap filename must be resolved first.
        // The SRTM filenames contain always the southwest coordinate of the block.
        // Each single SRTM file contains 1 degree of latitude and 1 degree of longiture. File size is 1201x1201.
        // Precision is 3 arc-seconds in both latitude and longitude.

        // In coordinates (`latitude` and `longitude`) negative values mean south for latitude and west for longitude,
        // and positive value mean north for latitude and east for longitude.
        // Therefore the SRTM heightmap filename can be resolved by rounding both latitude and longitude down (towards negative infinity).

        int32_t filename_latitude = std::floor(latitude);
        int32_t filename_longitude = std::floor(longitude);

        float southern_latitude = std::floor(latitude);
        float western_longitude = std::floor(longitude);

        float northern_latitude = southern_latitude + 1.0f;
        float eastern_longitude = western_longitude + 1.0f;

        std::string south_north_char;
        std::string west_east_char;

        if (filename_latitude < 0)
        {
            // negative latitudes mean southern hemisphere.
            south_north_char = "S";
        }
        else
        {
            // positive latitudes mean northern hemisphere.
            south_north_char = "N";
        }

        if (filename_longitude < 0)
        {
            // negative longitudes mean western hemisphere.
            west_east_char = "W";
        }
        else
        {
            // positive longitudes mean eastern hemisphere.
            west_east_char = "E";
        }

        std::stringstream latitude_stringstream;
        std::stringstream longitude_stringstream;

        uint32_t SRTM_filename_n_of_latitude_chars = 2;
        uint32_t SRTM_filename_n_of_longitude_chars = 3;

        latitude_stringstream << std::setw(SRTM_filename_n_of_latitude_chars) << std::setfill('0') << abs(filename_latitude);
        longitude_stringstream << std::setw(SRTM_filename_n_of_longitude_chars) << std::setfill('0') << abs(filename_longitude);

        std::string latitude_string = latitude_stringstream.str();
        std::string longitude_string = longitude_stringstream.str();

        std::string hgt_suffix = ".hgt";

        std::string abs_image_path = image_path + south_north_char + latitude_string + west_east_char + longitude_string + hgt_suffix;

        std::cout << "Loading SRTM file " << abs_image_path << " ...\n";

        // Actual 16-bit big-endian signed integer heightmap data.
        uint8_t* image_data;

        // Open the file
        const char* char_image_path = abs_image_path.c_str();
        std::FILE* file = std::fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << abs_image_path << " could not be opened.\n";
            return false;
        }

        uint32_t true_image_width = 1201;
        uint32_t true_image_height = 1201;
        uint32_t image_width_in_use = 1200;
        uint32_t image_height_in_use = 1200;
        uint32_t image_size = sizeof(int16_t) * true_image_width * true_image_height;

        // Create a buffer.
        image_data = new uint8_t[image_size];

        // Read the actual image data from the file into the buffer.
        std::fread(image_data, 1, image_size, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        float* vertex_data;
        vertex_data = new float[image_width_in_use * image_height_in_use];

        uint8_t *image_pointer;
        image_pointer = image_data + sizeof(int16_t) * (true_image_height - 1) * true_image_width; // start from southwestern corner.

        float* vertex_pointer;
        vertex_pointer = vertex_data;

        // start processing image_data.
        // 90 meters is for equator.

        // FIXME: this is a temporary testing code with a hardcoded start from the southwestern corner.
        // TODO: write a proper code for loading the appropriate chunks (based on real spherical coordinates) into VBOs!

        for (uint32_t z = 0; z < image_height_in_use; z++)
        {
            for (uint32_t x = 0; x < image_width_in_use; x++)
            {
                uint32_t y;
                y = static_cast<uint32_t>(*image_pointer) << 8 | static_cast<uint32_t>(*(image_pointer + 1));

                image_pointer += sizeof(int16_t);
                *vertex_pointer++ = static_cast<float>(y) / divisor;
            }
            image_pointer -= sizeof(int16_t) * (image_width_in_use + true_image_width);
        }

        delete image_data;

        SphericalWorldStruct spherical_world_struct;
        spherical_world_struct.southern_latitude = southern_latitude; // must be float, though SRTM data is split between full degrees.
        spherical_world_struct.northern_latitude = northern_latitude; // must be float, though SRTM data is split between full degrees.
        spherical_world_struct.western_longitude = western_longitude; // must be float, though SRTM data is split between full degrees.
        spherical_world_struct.eastern_longitude = eastern_longitude; // must be float, though SRTM data is split between full degrees.

        TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width_in_use;
        triangulate_quads_struct.image_height = image_height_in_use;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = world_radius;
        triangulate_quads_struct.spherical_world_struct = spherical_world_struct;

        bool result = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete vertex_data;
        return result;
    }

    bool load_LASF_data(
            std::string laser_scaling_file_name,
            std::vector<glm::vec3>& laser_points)
    {
        std::cout << "Loading LASF file " << laser_scaling_file_name << " ...\n";

        // Data read from the header of the LASF file
        uint8_t header[227];

        // Open the file
        const char* char_laser_scaling_file_name = laser_scaling_file_name.c_str();
        std::FILE* file = std::fopen(char_laser_scaling_file_name, "rb");
        if (!file)
        {
            std::cerr << laser_scaling_file_name << " could not be opened.\n";
            return false;
        }

        // Read the header, i.e. the 227 first bytes

        // If less than 54 bytes are read, it's a problem.
        if (std::fread(header, 1, 227, file) != 227)
        {
            std::cerr << "Too few bytes read when reading the file header. " << laser_scaling_file_name << " is not a correct LASF file.\n";
            return false;
        }

        // A LASF files always begins with "LASF"
        if ((header[0] != 'L') || (header[1] != 'A') || (header[2] != 'S') || (header[3] != 'F'))
        {
            std::cerr << "No LASF signature. " << laser_scaling_file_name << " is not a correct LASF file.\n";
            return false;
        }

        const uint32_t max_number_of_returns = 4;

        uint32_t sizes_of_point_record_formats[4];
        sizes_of_point_record_formats[0] = 20; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 
        sizes_of_point_record_formats[1] = 28; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2 + 8. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 
        sizes_of_point_record_formats[2] = 26; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2 + 2 + 2 + 2. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 
        sizes_of_point_record_formats[3] = 34; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2 + 8 + 2 + 2 + 2. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 

        uint16_t* pointer_to_16_bit_header_data = (uint16_t*) (header + 94);
        const uint16_t header_size_in_bytes = *pointer_to_16_bit_header_data++;

        if (header_size_in_bytes != 227)
        {
            std::cerr << "Invalid header size in file " << laser_scaling_file_name << " (" << header_size_in_bytes << " bytes). Header size must be 227 bytes.\n";
        }

        uint32_t* pointer_to_32_bit_header_data = (uint32_t*) (header + 96);

        const uint32_t offset_to_point_data = *pointer_to_32_bit_header_data++;
        const uint32_t number_of_variable_length_records = *pointer_to_32_bit_header_data++;

        uint8_t* pointer_to_8_bit_header_data = (uint8_t*) pointer_to_32_bit_header_data;

        const uint8_t point_data_formatID = *pointer_to_8_bit_header_data++;

        if (point_data_formatID > 3)
        {
            std::cerr << "invalid point data format ID: " << static_cast<int16_t>(point_data_formatID) << " in file " << laser_scaling_file_name << "\n";
            return false;
        }

        // OK, the point data format ID is valid (0, 1, 2 or 3).

        pointer_to_16_bit_header_data = (uint16_t*) pointer_to_8_bit_header_data;

        const uint8_t point_data_record_length = *pointer_to_16_bit_header_data++;

        pointer_to_32_bit_header_data = (uint32_t*) pointer_to_16_bit_header_data;

        const uint32_t number_of_point_records = *pointer_to_32_bit_header_data++;
        uint32_t number_of_points_by_record[max_number_of_returns + 1];

        for (uint32_t n_returns = 0; n_returns <= max_number_of_returns; n_returns++)
        {
            number_of_points_by_record[n_returns] = *pointer_to_32_bit_header_data++;
        }

        double* pointer_to_double_header_data = (double*) pointer_to_32_bit_header_data;

        const double x_scale_factor = *pointer_to_double_header_data++;
        const double y_scale_factor = *pointer_to_double_header_data++;
        const double z_scale_factor = *pointer_to_double_header_data++;
        const double x_offset = *pointer_to_double_header_data++;
        const double y_offset = *pointer_to_double_header_data++;
        const double z_offset = *pointer_to_double_header_data++;
        const double max_x = *pointer_to_double_header_data++;
        const double min_x = *pointer_to_double_header_data++;
        const double max_y = *pointer_to_double_header_data++;
        const double min_y = *pointer_to_double_header_data++;
        const double max_z = *pointer_to_double_header_data++;
        const double min_z = *pointer_to_double_header_data++;

        // Create a buffer.
        uint32_t size_of_point_data_record = sizes_of_point_record_formats[point_data_formatID];
        uint32_t point_data_size = number_of_point_records * size_of_point_data_record;
        uint8_t* point_data = new uint8_t[point_data_size];

        // Move file pointer to the beginning of point data.
        if (fseek(file, offset_to_point_data, SEEK_SET) != 0)
        {
            delete point_data;
            std::cerr << "moving file pointer of file " << laser_scaling_file_name << " failed!\n";
        }

        // Read the actual image data from the file into the buffer.
        std::fread(point_data, 1, point_data_size, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        // Loop through point data, convert coordinates to `float` and store them in `laser_points`.
        int32_t* pointer_to_signed_32_bit_header_data = (int32_t*) point_data;

        for (uint32_t laser_point_i = 0; laser_point_i < number_of_point_records; laser_point_i++)
        {
            int32_t x_from_record = *pointer_to_signed_32_bit_header_data++;
            int32_t y_from_record = *pointer_to_signed_32_bit_header_data++;
            int32_t z_from_record = *pointer_to_signed_32_bit_header_data++;

            float x = static_cast<float>(x_scale_factor * x_from_record + x_offset);
            float y = static_cast<float>(y_scale_factor * y_from_record + y_offset);
            float z = static_cast<float>(z_scale_factor * z_from_record + z_offset);
            laser_points.push_back(glm::vec3(x, y, z));
        }

        delete point_data;

        return true;
    }
}
