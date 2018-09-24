#include "ground_level.hpp"
#include "species.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>  // NAN, std::isnan, std::pow
#include <math.h> // fmax
#include <vector> // std::vector

namespace yli
{
    namespace ontology
    {
        float get_ground_level(
                const yli::ontology::Species* const terrain_species,
                const glm::vec3& position)
        {
            if (!terrain_species->is_terrain)
            {
                // if the current species is not a terrain `Species`, no collision detection to the ground will be performed.
                return NAN;
            }

            if ((position.x < 0.0f) || (position.x >= terrain_species->get_image_width()))
            {
                // if the x coordinate is out of range, no collision detection to the ground will be performed.
                return NAN;
            }

            if ((position.z < 0.0f) || (position.z >= terrain_species->get_image_height()))
            {
                // if the z coordinate is out of range, no collision detection to the ground will be performed.
                return NAN;
            }

            const float x = position.x / terrain_species->get_x_step();
            const float z = position.z / terrain_species->get_z_step();

            const std::size_t image_width = terrain_species->get_image_width();

            // compute the indices of closest vertices.
            const std::size_t southwest_i = static_cast<std::size_t>(floor(z) * image_width + floor(x));
            const std::size_t southeast_i = static_cast<std::size_t>(floor(z) * image_width + ceil(x));
            const std::size_t northwest_i = static_cast<std::size_t>(ceil(z) * image_width + floor(x));
            const std::size_t northeast_i = static_cast<std::size_t>(ceil(z) * image_width + ceil(x));

            const std::vector<glm::vec3>& vertices = terrain_species->get_vertices();

            // read closest the heights of closest integer coordinates to be used in bilinear interpolation.
            const float southwest_height = vertices[southwest_i].y;
            const float southeast_height = vertices[southeast_i].y;
            const float northwest_height = vertices[northwest_i].y;
            const float northeast_height = vertices[northeast_i].y;

            // these are not actually means but interpolations.
            // the result of the interpolation is mean if and only if (ceil(x) - x == 0.5) & (x - floor(x) == 0.5) , likewise for the z coordinate.
            float south_mean;
            float north_mean;
            float mean;

            if ((x - floor(x) < 0.01f) || (ceil(x) - x < 0.01f))
            {
                // if the x coordinate is too close to integer, the height of the closest vertex is used instead.
                south_mean = southwest_height;
                north_mean = northwest_height;
            }
            else
            {
                // the height is computed using bilinear interpolation.
                south_mean = ((ceil(x) - x) * southwest_height) + ((x - floor(x)) * southeast_height);
                north_mean = ((ceil(x) - x) * northwest_height) + ((x - floor(x)) * northeast_height);
            }

            if ((z - floor(z) < 0.01f) || (ceil(z) - z < 0.01f))
            {
                // if the z coordinate is too close to integer, the mean is used instead of bilinear interpolation.
                mean = (south_mean + north_mean) / 2.0f;
            }
            else
            {
                // the height is computed using bilinear interpolation.
                mean = ((ceil(z) - z) * south_mean) + ((z - floor(z)) * north_mean);
            }

            return mean;
        }

        float get_floor_level(
                const yli::ontology::Species* const terrain_species,
                const glm::vec3& position)
        {
            if (!terrain_species->is_terrain)
            {
                // if the current species is not a world species, no collision detection to the ground will be performed.
                return NAN;
            }

#define CHARACTER_RADIUS 1.0f
            float current_ground_level = get_ground_level(terrain_species, position);
            float x = position.x;
            float y = position.y;
            float z = position.z;

            // Get ground level at current location and +/- 1.0f.
            glm::vec3 south_position;
            south_position.x = x;
            south_position.y = y;
            south_position.z = z;
            south_position.z -= CHARACTER_RADIUS;
            float south_ground_level = get_ground_level(terrain_species, south_position);

            glm::vec3 west_position;
            west_position.x = x;
            west_position.y = y;
            west_position.z = z;
            west_position.x -= CHARACTER_RADIUS;
            float west_ground_level = get_ground_level(terrain_species, west_position);

            glm::vec3 north_position;
            north_position.x = x;
            north_position.y = y;
            north_position.z = z;
            north_position.z += CHARACTER_RADIUS;
            float north_ground_level = get_ground_level(terrain_species, north_position);

            glm::vec3 east_position;
            east_position.x = x;
            east_position.y = y;
            east_position.z = z;
            east_position.x += CHARACTER_RADIUS;
            float east_ground_level = get_ground_level(terrain_species, east_position);

            glm::vec3 southwest_position;
            southwest_position.x = south_position.x;
            southwest_position.y = south_position.y;
            southwest_position.z = south_position.z;
            southwest_position.x -= CHARACTER_RADIUS;
            float southwest_ground_level = get_ground_level(terrain_species, southwest_position);

            glm::vec3 southeast_position;
            southeast_position.x = south_position.x;
            southeast_position.y = south_position.y;
            southeast_position.z = south_position.z;
            southeast_position.x += CHARACTER_RADIUS;
            float southeast_ground_level = get_ground_level(terrain_species, southeast_position);

            glm::vec3 northwest_position = north_position;
            northwest_position.x = north_position.x;
            northwest_position.y = north_position.y;
            northwest_position.z = north_position.z;
            northwest_position.x -= CHARACTER_RADIUS;
            float northwest_ground_level = get_ground_level(terrain_species, northwest_position);

            glm::vec3 northeast_position = north_position;
            northeast_position.x = north_position.x;
            northeast_position.y = north_position.y;
            northeast_position.z = north_position.z;
            northeast_position.x += CHARACTER_RADIUS;
            float northeast_ground_level = get_ground_level(terrain_species, northeast_position);

            float temp_max_between_southwest_and_southeast = std::fmax(southwest_ground_level, southeast_ground_level);
            float temp_max_south = std::fmax(temp_max_between_southwest_and_southeast, south_ground_level);
            float temp_max_between_northwest_and_northeast = std::fmax(northwest_ground_level, northeast_ground_level);
            float temp_max_north = std::fmax(temp_max_between_northwest_and_northeast, north_ground_level);
            float temp_max_between_south_and_north = std::fmax(temp_max_south, temp_max_north);
            float temp_max_between_west_and_east = std::fmax(west_ground_level, east_ground_level);
            float temp_max_around_character = std::fmax(temp_max_between_south_and_north, temp_max_between_west_and_east);
            return std::fmax(temp_max_around_character, current_ground_level);
        }
    }
}
