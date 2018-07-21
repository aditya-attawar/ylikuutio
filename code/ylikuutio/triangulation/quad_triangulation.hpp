#ifndef __QUAD_TRIANGULATION_HPP_INCLUDED
#define __QUAD_TRIANGULATION_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "triangulate_quads_struct.hpp"
#include "face_normals.hpp"
#include "vertex_normals.hpp"
#include "vertices.hpp"
#include "triangulation_enums.hpp"
#include "triangulation_templates.hpp"
#include "triangulation_templates.hpp"
#include "indexing.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/geometry/transformation_struct.hpp"
#include "code/ylikuutio/geometry/transformation.hpp"
#include "code/ylikuutio/geometry/transformation.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        template<class T1>
            bool triangulate_quads(
                    const T1* input_vertex_pointer,
                    const yli::geometry::TriangulateQuadsStruct triangulate_quads_struct,
                    std::vector<glm::vec3>& out_vertices,
                    std::vector<glm::vec2>& out_UVs,
                    std::vector<glm::vec3>& out_normals)
            {
                const std::size_t image_width = triangulate_quads_struct.image_width;
                const std::size_t image_height = triangulate_quads_struct.image_height;
                const std::size_t x_step = triangulate_quads_struct.x_step;
                const std::size_t z_step = triangulate_quads_struct.z_step;

                // Input vertices (`T1* input_vertex_pointer`)
                // can be `float`, `int32_t` or `uint32_t`.
                if (image_width < 2 || image_height < 2)
                {
                    return false;
                }

                if (x_step < 1 || z_step < 1)
                {
                    return false;
                }

                const std::size_t actual_image_width = (image_width - 1) / x_step + 1;
                const std::size_t actual_image_height = (image_height - 1) / z_step + 1;

                if (actual_image_width < 2 || actual_image_height < 2)
                {
                    return false;
                }

                const std::string triangulation_type = triangulate_quads_struct.triangulation_type;
                const double sphere_radius = triangulate_quads_struct.sphere_radius;
                const yli::geometry::SphericalTerrainStruct spherical_terrain_struct = triangulate_quads_struct.spherical_terrain_struct;

                const char* char_triangulation_type = triangulation_type.c_str();

                bool is_bilinear_interpolation_in_use = false;
                bool is_southwest_northeast_edges_in_use = false;
                bool is_southeast_northwest_edges_in_use = false;
                bool is_triangulation_type_valid = false;
                int32_t n_faces_for_each_vertex = 2; // split each quad into 2 triangles.

                if (std::strcmp(char_triangulation_type, "bilinear_interpolation") == 0)
                {
                    // *---*
                    // |\ /|
                    // | * |
                    // |/ \|
                    // *---*
                    is_bilinear_interpolation_in_use = true;
                    is_triangulation_type_valid = true;
                    n_faces_for_each_vertex = 4;
                }
                else if ((std::strcmp(char_triangulation_type, "southwest_northeast_edges") == 0) || (std::strcmp(char_triangulation_type, "northeast_southwest_edges") == 0))
                {
                    // *---*
                    // |  /|
                    // | / |
                    // |/  |
                    // *---*
                    is_southwest_northeast_edges_in_use = true;
                    is_triangulation_type_valid = true;
                }
                else if ((std::strcmp(char_triangulation_type, "southeast_northwest_edges") == 0) || (std::strcmp(char_triangulation_type, "northwest_southeast_edges") == 0))
                {
                    // *---*
                    // |\  |
                    // | \ |
                    // |  \|
                    // *---*
                    is_southeast_northwest_edges_in_use = true;
                    is_triangulation_type_valid = true;
                }

                std::cout << "triangulation type in use: " << triangulation_type << "\n";

                if (!is_triangulation_type_valid)
                {
                    std::cerr << "invalid triangulation type!\n";
                    return false;
                }

                std::vector<glm::vec3> temp_vertices;
                std::vector<glm::vec2> temp_UVs;
                std::vector<glm::vec3> temp_normals;

                // Processing stages:
                // 1. Define the (float) vertices for vertices loaded from file, `push_back` to `temp_vertices` and `temp_UVs`.
                // 2. Interpolate the (float) vertices between, using bilinear interpolation, `push_back` to `temp_vertices` and `temp_UVs`.
                // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
                // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
                // 4. Compute the face normals, `push_back` to `face_normals`.
                // 5. Compute the vertex normals for vertices loaded from file and for interpolated vertices (for `"bilinear_interpolation"`), `push_back` to `temp_normals`.
                // 6. Loop through all vertices and `yli::geometry::output_triangle_vertices`.
                //
                // stg. `"bilinear_interpolation"`                                      `"southwest_northeast_edges"`               `"southeast_northwest_edges"`
                // 1.   `define_vertices`                                               `define_vertices`                           `define_vertices`
                // 2.   `interpolate_and_define_vertices_using_bilinear_interpolation`  N/A                                         N/A
                // 3.   `transform_coordinates_to_curved_surface`                       `transform_coordinates_to_curved_surface`   `transform_coordinates_to_curved_surface`
                // 4.   `compute_face_normals`                                          `compute_face_normals`                      `compute_face_normals`
                // 5.   `compute_vertex_normals`                                        `compute_vertex_normals`                    `compute_vertex_normals`
                // 6.   `define_vertices_UVs_and_normals`                               `define_vertices_UVs_and_normals`           `define_vertices_UVs_and_normals`
                //
                // stg. = stage

                // 1. Define the vertices for vertices loaded from file, `push_back` to `temp_vertices`.

                if (!yli::geometry::define_vertices(
                            input_vertex_pointer,
                            image_width,
                            image_height,
                            x_step,
                            z_step,
                            triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates,
                            temp_vertices,
                            temp_UVs))
                {
                    return false;
                }

                std::cout << "image width: " << image_width << " pixels.\n";
                std::cout << "image height: " << image_height << " pixels.\n";

                std::cout << "actual image width: " << actual_image_width << " pixels.\n";
                std::cout << "actual image height: " << actual_image_height << " pixels.\n";

                const std::size_t n_faces = n_faces_for_each_vertex * (actual_image_width - 1) * (actual_image_height - 1);

                std::cout << "number of faces: " << n_faces << ".\n";

                uint32_t vertex_index[3], uv_index[3], normal_index[3];

                if (is_bilinear_interpolation_in_use)
                {
                    // 2. Interpolate the vertices between, using bilinear interpolation, `push_back` to `temp_vertices`.
                    if (!yli::geometry::interpolate_and_define_vertices_using_bilinear_interpolation(
                                input_vertex_pointer,
                                image_width,
                                image_height,
                                x_step,
                                z_step,
                                triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates,
                                temp_vertices,
                                temp_UVs))
                    {
                        return false;
                    }
                }

                if (!std::isnan(sphere_radius))
                {
                    // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
                    // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
                    //
                    // Wikipedia:
                    // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
                    //
                    // x = rho * sin(theta) * cos(phi)
                    // y = rho * sin(theta) * sin(phi)
                    // z = rho * cos(theta)

                    yli::geometry::TransformationStruct transformation_struct;
                    transformation_struct.image_width = image_width;
                    transformation_struct.image_height = image_height;
                    transformation_struct.sphere_radius = sphere_radius;
                    transformation_struct.is_bilinear_interpolation_in_use = is_bilinear_interpolation_in_use;
                    transformation_struct.spherical_terrain_struct = spherical_terrain_struct;
                    yli::geometry::transform_coordinates_to_curved_surface(transformation_struct, temp_vertices);
                }
                else
                {
                    std::cout << "no coordinate transformation is needed.\n";
                }

                // 4. Compute the face normals, `push_back` to `face_normals`.
                // Triangle order: S - W - N - E.
                //
                // First triangle: center, southeast, southwest.
                // Second triangle: center, southwest, northwest.
                // Third triangle: center, northwest, northeast.
                // Fourth triangle: center, northeast, southeast.
                std::cout << "computing face normals.\n";

                std::vector<glm::vec3> face_normal_vector_vec3;

                if (!yli::geometry::compute_face_normals(
                            temp_vertices,
                            face_normal_vector_vec3,
                            actual_image_width,
                            actual_image_height,
                            is_bilinear_interpolation_in_use,
                            is_southwest_northeast_edges_in_use,
                            is_southeast_northwest_edges_in_use))
                {
                    return false;
                }

                // 5. Compute the vertex normals for vertices loaded from file, `push_back` to `temp_normals`.
                if (!yli::geometry::compute_vertex_normals(
                            temp_normals,
                            face_normal_vector_vec3,
                            actual_image_width,
                            actual_image_height,
                            is_bilinear_interpolation_in_use,
                            is_southwest_northeast_edges_in_use,
                            is_southeast_northwest_edges_in_use))
                {
                    return false;
                }

                // 6. Loop through all vertices and `yli::geometry::output_triangle_vertices`.

                if (!yli::geometry::define_vertices_UVs_and_normals(
                            triangulate_quads_struct,
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertex_index,
                            uv_index,
                            normal_index,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            actual_image_width,
                            actual_image_height,
                            is_bilinear_interpolation_in_use,
                            is_southwest_northeast_edges_in_use,
                            is_southeast_northwest_edges_in_use))
                {
                    return false;
                }

                std::cout << "number of vertices: " << out_vertices.size() << ".\n";
                std::cout << "number of UVs: " << out_UVs.size() << ".\n";
                std::cout << "number of normals: " << out_normals.size() << ".\n";

                return true;
            }
    }
}

#endif
