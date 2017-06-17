#include "gtest/gtest.h"
#include "code/ylikuutio/triangulation/triangulation_enums.hpp"
#include "code/ylikuutio/triangulation/triangulation_templates.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/loaders/bmp_heightmap_loader.hpp"
#include "code/ylikuutio/loaders/bmp_heightmap_loader.cpp"
#include "code/ylikuutio/loaders/srtm_heightmap_loader.hpp"
#include "code/ylikuutio/loaders/srtm_heightmap_loader.cpp"
#include "code/ylikuutio/common/global_variables.hpp"
#include "code/ylikuutio/common/global_variables.cpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST(vertices_must_be_defined_and_interpolated_appropriately, a_3x3_world)
{
    uint32_t image_width = 3;
    uint32_t image_height = 3;
    bool should_ylikuutio_use_real_texture_coordinates = true;

    float* input_vertex_data = new float[image_width * image_height];
    ASSERT_NE(input_vertex_data, nullptr);
    float* input_vertex_pointer = input_vertex_data;

    // Fill input vertex data with values.
    // |  32 64 128 |
    // |   4  8  16 |
    // |   0  1   2 |
    *input_vertex_pointer++ = 0.0f;
    *input_vertex_pointer++ = 1.0f;
    *input_vertex_pointer++ = 2.0f;
    *input_vertex_pointer++ = 4.0f;
    *input_vertex_pointer++ = 8.0f;
    *input_vertex_pointer++ = 16.0f;
    *input_vertex_pointer++ = 32.0f;
    *input_vertex_pointer++ = 64.0f;
    *input_vertex_pointer++ = 128.0f;

    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_UVs;
    std::vector<glm::vec3> temp_normals;

    uint32_t x_step = 1;
    uint32_t z_step = 1;

    geometry::define_vertices(
            input_vertex_data,
            image_width,
            image_height,
            x_step,
            z_step,
            should_ylikuutio_use_real_texture_coordinates,
            temp_vertices,
            temp_UVs);

    geometry::interpolate_and_define_vertices_using_bilinear_interpolation(
            input_vertex_data,
            image_width,
            image_height,
            x_step,
            z_step,
            should_ylikuutio_use_real_texture_coordinates,
            temp_vertices,
            temp_UVs);

    // Predefined vertices.

    // x = 0, z = 0, y = 0.
    ASSERT_EQ(temp_vertices[0].x, 0.0f);
    ASSERT_EQ(temp_vertices[0].z, 0.0f);
    ASSERT_EQ(temp_vertices[0].y, 0.0f);
    ASSERT_EQ(temp_UVs[0].x, 0.0f);
    ASSERT_EQ(temp_UVs[0].y, 0.0f);

    // x = 1, z = 0, y = 1.
    ASSERT_EQ(temp_vertices[1].x, 1.0f);
    ASSERT_EQ(temp_vertices[1].z, 0.0f);
    ASSERT_EQ(temp_vertices[1].y, 1.0f);
    ASSERT_EQ(temp_UVs[1].x, 1.0f);
    ASSERT_EQ(temp_UVs[1].y, 0.0f);

    // x = 2, z = 0, y = 2.
    ASSERT_EQ(temp_vertices[2].x, 2.0f);
    ASSERT_EQ(temp_vertices[2].z, 0.0f);
    ASSERT_EQ(temp_vertices[2].y, 2.0f);
    ASSERT_EQ(temp_UVs[2].x, 0.0f);
    ASSERT_EQ(temp_UVs[2].y, 0.0f);

    // x = 0, z = 1, y = 4.
    ASSERT_EQ(temp_vertices[3].x, 0.0f);
    ASSERT_EQ(temp_vertices[3].z, 1.0f);
    ASSERT_EQ(temp_vertices[3].y, 4.0f);
    ASSERT_EQ(temp_UVs[3].x, 0.0f);
    ASSERT_EQ(temp_UVs[3].y, 1.0f);

    // x = 1, z = 1, y = 8.
    ASSERT_EQ(temp_vertices[4].x, 1.0f);
    ASSERT_EQ(temp_vertices[4].z, 1.0f);
    ASSERT_EQ(temp_vertices[4].y, 8.0f);
    ASSERT_EQ(temp_UVs[4].x, 1.0f);
    ASSERT_EQ(temp_UVs[4].y, 1.0f);

    // x = 2, z = 1, y = 16.
    ASSERT_EQ(temp_vertices[5].x, 2.0f);
    ASSERT_EQ(temp_vertices[5].z, 1.0f);
    ASSERT_EQ(temp_vertices[5].y, 16.0f);
    ASSERT_EQ(temp_UVs[5].x, 0.0f);
    ASSERT_EQ(temp_UVs[5].y, 1.0f);

    // x = 0, z = 2, y = 32.
    ASSERT_EQ(temp_vertices[6].x, 0.0f);
    ASSERT_EQ(temp_vertices[6].z, 2.0f);
    ASSERT_EQ(temp_vertices[6].y, 32.0f);
    ASSERT_EQ(temp_UVs[6].x, 0.0f);
    ASSERT_EQ(temp_UVs[6].y, 0.0f);

    // x = 1, z = 2, y = 64.
    ASSERT_EQ(temp_vertices[7].x, 1.0f);
    ASSERT_EQ(temp_vertices[7].z, 2.0f);
    ASSERT_EQ(temp_vertices[7].y, 64.0f);
    ASSERT_EQ(temp_UVs[7].x, 1.0f);
    ASSERT_EQ(temp_UVs[7].y, 0.0f);

    // x = 2, z = 2, y = 128.
    ASSERT_EQ(temp_vertices[8].x, 2.0f);
    ASSERT_EQ(temp_vertices[8].z, 2.0f);
    ASSERT_EQ(temp_vertices[8].y, 128.0f);
    ASSERT_EQ(temp_UVs[8].x, 0.0f);
    ASSERT_EQ(temp_UVs[8].y, 0.0f);

    // Interpolated vertices.

    // x = 0.5, z = 0.5, y = 3.25.
    ASSERT_EQ(temp_vertices[9].x, 0.5f);
    ASSERT_EQ(temp_vertices[9].z, 0.5f);
    ASSERT_EQ(temp_vertices[9].y, 3.25f);
    ASSERT_EQ(temp_UVs[9].x, 0.5f);
    ASSERT_EQ(temp_UVs[9].y, 0.5f);

    // x = 1.5, z = 0.5, y = 6.75.
    ASSERT_EQ(temp_vertices[10].x, 1.5f);
    ASSERT_EQ(temp_vertices[10].z, 0.5f);
    ASSERT_EQ(temp_vertices[10].y, 6.75f);
    ASSERT_EQ(temp_UVs[10].x, 0.5f);
    ASSERT_EQ(temp_UVs[10].y, 0.5f);

    // x = 0.5, z = 1.5, y = 27.
    ASSERT_EQ(temp_vertices[11].x, 0.5f);
    ASSERT_EQ(temp_vertices[11].z, 1.5f);
    ASSERT_EQ(temp_vertices[11].y, 27.0f);
    ASSERT_EQ(temp_UVs[11].x, 0.5f);
    ASSERT_EQ(temp_UVs[11].y, 0.5f);

    // x = 1.5, z = 1.5, y = 54.
    ASSERT_EQ(temp_vertices[12].x, 1.5f);
    ASSERT_EQ(temp_vertices[12].z, 1.5f);
    ASSERT_EQ(temp_vertices[12].y, 54.0f);
    ASSERT_EQ(temp_UVs[12].x, 0.5f);
    ASSERT_EQ(temp_UVs[12].y, 0.5f);

    std::vector<glm::vec3> face_normal_vector_vec3;
    bool is_bilinear_interpolation_in_use = true;
    bool is_southwest_northeast_edges_in_use = false;
    bool is_southeast_northwest_edges_in_use = false;

    ASSERT_TRUE(geometry::compute_face_normals(
                temp_vertices,
                face_normal_vector_vec3,
                image_width,
                image_height,
                is_bilinear_interpolation_in_use,
                is_southwest_northeast_edges_in_use,
                is_southeast_northwest_edges_in_use));

    // Predefined vertices.
    glm::vec3 i0_x0_z0 = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 i1_x1_z0 = glm::vec3(1.0f, 1.0f, 0.0f);
    glm::vec3 i2_x2_z0 = glm::vec3(2.0f, 2.0f, 0.0f);
    glm::vec3 i3_x0_z1 = glm::vec3(0.0f, 4.0f, 1.0f);
    glm::vec3 i4_x1_z1 = glm::vec3(1.0f, 8.0f, 1.0f);
    glm::vec3 i5_x2_z1 = glm::vec3(2.0f, 16.0f, 1.0f);
    glm::vec3 i6_x0_z2 = glm::vec3(0.0f, 32.0f, 2.0f);
    glm::vec3 i7_x1_z2 = glm::vec3(1.0f, 64.0f, 2.0f);
    glm::vec3 i8_x2_z2 = glm::vec3(2.0f, 128.0f, 2.0f);

    // Interpolated vertices.
    glm::vec3 i9_x0_5_z0_5 = glm::vec3(0.5f, 3.25f, 0.5f);
    glm::vec3 i10_x1_5_z0_5 = glm::vec3(1.5f, 6.75f, 0.5f);
    glm::vec3 i11_x0_5_z1_5 = glm::vec3(0.5f, 27.0f, 1.5f);
    glm::vec3 i12_x1_5_z1_5 = glm::vec3(1.5f, 54.0f, 1.5f);

    // Predefined vertices.
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[0], i0_x0_z0)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[1], i1_x1_z0)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[2], i2_x2_z0)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[3], i3_x0_z1)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[4], i4_x1_z1)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[5], i5_x2_z1)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[6], i6_x0_z2)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[7], i7_x1_z2)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[8], i8_x2_z2)));

    // Interpolated vertices.
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[9], i9_x0_5_z0_5)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[10], i10_x1_5_z0_5)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[11], i11_x0_5_z1_5)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[12], i12_x1_5_z1_5)));

    // Face normals.
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[0], glm::normalize(glm::cross(i1_x1_z0 - i9_x0_5_z0_5, i0_x0_z0 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[1], glm::normalize(glm::cross(i0_x0_z0 - i9_x0_5_z0_5, i3_x0_z1 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[2], glm::normalize(glm::cross(i3_x0_z1 - i9_x0_5_z0_5, i4_x1_z1 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[3], glm::normalize(glm::cross(i4_x1_z1 - i9_x0_5_z0_5, i1_x1_z0 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[4], glm::normalize(glm::cross(i2_x2_z0 - i10_x1_5_z0_5, i1_x1_z0 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[5], glm::normalize(glm::cross(i1_x1_z0 - i10_x1_5_z0_5, i4_x1_z1 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[6], glm::normalize(glm::cross(i4_x1_z1 - i10_x1_5_z0_5, i5_x2_z1 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[7], glm::normalize(glm::cross(i5_x2_z1 - i10_x1_5_z0_5, i2_x2_z0 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[8], glm::normalize(glm::cross(i4_x1_z1 - i11_x0_5_z1_5, i3_x0_z1 - i11_x0_5_z1_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[9], glm::normalize(glm::cross(i3_x0_z1 - i11_x0_5_z1_5, i6_x0_z2 - i11_x0_5_z1_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[10], glm::normalize(glm::cross(i6_x0_z2 - i11_x0_5_z1_5, i7_x1_z2 - i11_x0_5_z1_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[11], glm::normalize(glm::cross(i7_x1_z2 - i11_x0_5_z1_5, i4_x1_z1 - i11_x0_5_z1_5)))));
}
TEST(face_indices_must_be_computed_appropriately, a_4x4_world)
{
    // Face indices example for a 4x4 image file using bilinear interpolation.
    //
    //  +-------+-------+-------+
    //  |\ 26  /|\ 30  /|\ 34  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |25 x 27|29 x 31|33 x 35|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/ 24  \|/ 28  \|/ 32  \|
    //  +-------+-------+-------+
    //  |\ 14  /|\ 18  /|\ 22  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |13 x 15|17 x 19|21 x 23|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/ 12  \|/ 16  \|/ 20  \|
    //  +-------+-------+-------+
    //  |\  2  /|\  6  /|\ 10  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |1  x  3|5  x  7|9  x 11|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/  0  \|/  4  \|/  8  \|
    //  +-------+-------+-------+

    const uint32_t example_width = 4;
    // x = 0, z = 0.
    ASSERT_EQ(geometry::get_face_normal_i(0, 0, geometry::ENE, example_width), 0);
    ASSERT_EQ(geometry::get_face_normal_i(0, 0, geometry::NNE, example_width), 1);

    // x = 1, z = 0.
    ASSERT_EQ(geometry::get_face_normal_i(1, 0, geometry::WNW, example_width), 0);
    ASSERT_EQ(geometry::get_face_normal_i(1, 0, geometry::NNW, example_width), 3);
    ASSERT_EQ(geometry::get_face_normal_i(1, 0, geometry::NNE, example_width), 5);
    ASSERT_EQ(geometry::get_face_normal_i(1, 0, geometry::ENE, example_width), 4);

    // x = 2, z = 0.
    ASSERT_EQ(geometry::get_face_normal_i(2, 0, geometry::WNW, example_width), 4);
    ASSERT_EQ(geometry::get_face_normal_i(2, 0, geometry::NNW, example_width), 7);
    ASSERT_EQ(geometry::get_face_normal_i(2, 0, geometry::NNE, example_width), 9);
    ASSERT_EQ(geometry::get_face_normal_i(2, 0, geometry::ENE, example_width), 8);

    // x = 3, z = 0.
    ASSERT_EQ(geometry::get_face_normal_i(3, 0, geometry::WNW, example_width), 8);
    ASSERT_EQ(geometry::get_face_normal_i(3, 0, geometry::NNW, example_width), 11);

    // x = 0, z = 1.
    ASSERT_EQ(geometry::get_face_normal_i(0, 1, geometry::NNE, example_width), 13);
    ASSERT_EQ(geometry::get_face_normal_i(0, 1, geometry::ENE, example_width), 12);
    ASSERT_EQ(geometry::get_face_normal_i(0, 1, geometry::ESE, example_width), 2);
    ASSERT_EQ(geometry::get_face_normal_i(0, 1, geometry::SSE, example_width), 1);

    // x = 1, z = 1.
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::NNE, example_width), 17);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::ENE, example_width), 16);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::ESE, example_width), 6);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::SSE, example_width), 5);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::SSW, example_width), 3);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::WSW, example_width), 2);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::WNW, example_width), 12);
    ASSERT_EQ(geometry::get_face_normal_i(1, 1, geometry::NNW, example_width), 15);

    // x = 2, z = 1.
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::NNE, example_width), 21);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::ENE, example_width), 20);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::ESE, example_width), 10);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::SSE, example_width), 9);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::SSW, example_width), 7);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::WSW, example_width), 6);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::WNW, example_width), 16);
    ASSERT_EQ(geometry::get_face_normal_i(2, 1, geometry::NNW, example_width), 19);

    // x = 3, z = 1.
    ASSERT_EQ(geometry::get_face_normal_i(3, 1, geometry::SSW, example_width), 11);
    ASSERT_EQ(geometry::get_face_normal_i(3, 1, geometry::WSW, example_width), 10);
    ASSERT_EQ(geometry::get_face_normal_i(3, 1, geometry::WNW, example_width), 20);
    ASSERT_EQ(geometry::get_face_normal_i(3, 1, geometry::NNW, example_width), 23);

    // x = 0, z = 2.
    ASSERT_EQ(geometry::get_face_normal_i(0, 2, geometry::NNE, example_width), 25);
    ASSERT_EQ(geometry::get_face_normal_i(0, 2, geometry::ENE, example_width), 24);
    ASSERT_EQ(geometry::get_face_normal_i(0, 2, geometry::ESE, example_width), 14);
    ASSERT_EQ(geometry::get_face_normal_i(0, 2, geometry::SSE, example_width), 13);

    // x = 1, z = 2.
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::NNE, example_width), 29);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::ENE, example_width), 28);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::ESE, example_width), 18);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::SSE, example_width), 17);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::SSW, example_width), 15);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::WSW, example_width), 14);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::WNW, example_width), 24);
    ASSERT_EQ(geometry::get_face_normal_i(1, 2, geometry::NNW, example_width), 27);

    // x = 2, z = 2.
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::NNE, example_width), 33);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::ENE, example_width), 32);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::ESE, example_width), 22);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::SSE, example_width), 21);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::SSW, example_width), 19);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::WSW, example_width), 18);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::WNW, example_width), 28);
    ASSERT_EQ(geometry::get_face_normal_i(2, 2, geometry::NNW, example_width), 31);

    // x = 3, z = 2.
    ASSERT_EQ(geometry::get_face_normal_i(3, 2, geometry::SSW, example_width), 23);
    ASSERT_EQ(geometry::get_face_normal_i(3, 2, geometry::WSW, example_width), 22);
    ASSERT_EQ(geometry::get_face_normal_i(3, 2, geometry::WNW, example_width), 32);
    ASSERT_EQ(geometry::get_face_normal_i(3, 2, geometry::NNW, example_width), 35);
}
TEST(a_BMP_world_must_be_loaded_appropriately, load_3x3_BMP_world)
{
    std::string image_path = "test3x3.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    uint32_t image_width = 0;
    uint32_t image_height = 0;
    std::string color_channel = "mean";
    uint32_t x_step = 1;
    uint32_t z_step = 1;
    std::string triangulation_type = "bilinear_interpolation";

    bool model_loading_result = loaders::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel,
            x_step,
            z_step,
            triangulation_type);

    ASSERT_TRUE(model_loading_result);

    const uint32_t n_vertices_for_face = 3;
    const uint32_t n_faces_for_bilinear_triangulation = 4;
    const uint32_t n_width_of_image_file = 3;
    const uint32_t n_height_of_image_file = 3;

    //                         48 =                  3 *                                  4 * (                    3 - 1) * (                     3 - 1)
    ASSERT_EQ(out_vertices.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));

    //                    48 =                  3  *                                 4 * (                    3 - 1) * (                     3 - 1)
    ASSERT_EQ(out_UVs.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));

    //                        48 =                  3  *                                 4 * (                    3 - 1) * (                     3 - 1)
    ASSERT_EQ(out_normals.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));

    // test3x3.bmp colors:
    // | 32,32,32  64,64,64  128,128,128 |
    // |  4, 4, 4   8, 8, 8   16, 16, 16 |
    // |  0, 0, 0   1, 1, 1    2,  2,  2 |
    //
    // Or simply as graycolor (BMP):
    // |  32 64 128 |
    // |   4  8  16 |
    // |   0  1   2 |

    ASSERT_EQ(out_vertices[0].x, 0.5f); // first vertex (center) of first (south) triangle.
    ASSERT_EQ(out_vertices[0].z, 0.5f);

    ASSERT_EQ(out_vertices[1].x, 1.0f); // second vertex (southeast) of first (south) triangle.
    ASSERT_EQ(out_vertices[1].z, 0.0f);

    ASSERT_EQ(out_vertices[2].x, 0.0f); // third vertex (southwest) of first (south) triangle.
    ASSERT_EQ(out_vertices[2].z, 0.0f);

    ASSERT_EQ(out_vertices[3].x, 0.5f); // first vertex (center) of second (west) triangle.
    ASSERT_EQ(out_vertices[3].z, 0.5f);

    ASSERT_EQ(out_vertices[4].x, 0.0f); // second vertex (southwest) of second (west) triangle.
    ASSERT_EQ(out_vertices[4].z, 0.0f);

    ASSERT_EQ(out_vertices[5].x, 0.0f); // third vertex (northwest) of second (west) triangle.
    ASSERT_EQ(out_vertices[5].z, 1.0f);

    ASSERT_EQ(out_vertices[6].x, 0.5f); // first vertex (center) of third (north) triangle.
    ASSERT_EQ(out_vertices[6].z, 0.5f);

    ASSERT_EQ(out_vertices[7].x, 0.0f); // second vertex (northwest) of third (north) triangle.
    ASSERT_EQ(out_vertices[7].z, 1.0f);

    ASSERT_EQ(out_vertices[8].x, 1.0f); // third vertex (northeast) of third (north) triangle.
    ASSERT_EQ(out_vertices[8].z, 1.0f);

    ASSERT_EQ(out_vertices[9].x, 0.5f); // first vertex (center) of fourth (east) triangle.
    ASSERT_EQ(out_vertices[9].z, 0.5f);

    ASSERT_EQ(out_vertices[10].x, 1.0f); // second vertex (northeast) of fourth (east) triangle.
    ASSERT_EQ(out_vertices[10].z, 1.0f);

    ASSERT_EQ(out_vertices[11].x, 1.0f); // third vertex (southeast) of fourth (east) triangle.
    ASSERT_EQ(out_vertices[11].z, 0.0f);

    ASSERT_EQ(out_vertices[12].x, 1.5f); // first vertex (center) of fifth (south) triangle.
    ASSERT_EQ(out_vertices[12].z, 0.5f);

    ASSERT_EQ(out_vertices[13].x, 2.0f); // second vertex (southeast) of fifth (south) triangle.
    ASSERT_EQ(out_vertices[13].z, 0.0f);

    ASSERT_EQ(out_vertices[14].x, 1.0f); // third vertex (southwest) of fifth (south) triangle.
    ASSERT_EQ(out_vertices[14].z, 0.0f);

    ASSERT_EQ(out_vertices[15].x, 1.5f); // first vertex (center) of sixth (west) triangle.
    ASSERT_EQ(out_vertices[15].z, 0.5f);

    ASSERT_EQ(out_vertices[16].x, 1.0f); // second vertex (southwest) of sixth (west) triangle.
    ASSERT_EQ(out_vertices[16].z, 0.0f);

    ASSERT_EQ(out_vertices[17].x, 1.0f); // third vertex (northwest) of sixth (west) triangle.
    ASSERT_EQ(out_vertices[17].z, 1.0f);

    ASSERT_EQ(out_vertices[18].x, 1.5f); // first vertex (center) of seventh (north) triangle.
    ASSERT_EQ(out_vertices[18].z, 0.5f);

    ASSERT_EQ(out_vertices[19].x, 1.0f); // second vertex (northwest) of seventh (north) triangle.
    ASSERT_EQ(out_vertices[19].z, 1.0f);

    ASSERT_EQ(out_vertices[20].x, 2.0f); // third vertex (northeast) of seventh (north) triangle.
    ASSERT_EQ(out_vertices[20].z, 1.0f);

    ASSERT_EQ(out_vertices[21].x, 1.5f); // first vertex (center) of eigth (east) triangle.
    ASSERT_EQ(out_vertices[21].z, 0.5f);

    ASSERT_EQ(out_vertices[22].x, 2.0f); // second vertex (northeast) of eigth (east) triangle.
    ASSERT_EQ(out_vertices[22].z, 1.0f);

    ASSERT_EQ(out_vertices[23].x, 2.0f); // third vertex (southeast) of eigth (east) triangle.
    ASSERT_EQ(out_vertices[23].z, 0.0f);

    ASSERT_EQ(out_vertices[24].x, 0.5f); // first vertex (center) of ninth (south) triangle.
    ASSERT_EQ(out_vertices[24].z, 1.5f);

    ASSERT_EQ(out_vertices[25].x, 1.0f); // second vertex (southeast) of ninth (south) triangle.
    ASSERT_EQ(out_vertices[25].z, 1.0f);

    ASSERT_EQ(out_vertices[26].x, 0.0f); // third vertex (southwest) of ninth (south) triangle.
    ASSERT_EQ(out_vertices[26].z, 1.0f);

    ASSERT_EQ(out_vertices[27].x, 0.5f); // first vertex (center) of tenth (west) triangle.
    ASSERT_EQ(out_vertices[27].z, 1.5f);

    ASSERT_EQ(out_vertices[28].x, 0.0f); // second vertex (southwest) of tenth (west) triangle.
    ASSERT_EQ(out_vertices[28].z, 1.0f);

    ASSERT_EQ(out_vertices[29].x, 0.0f); // third vertex (northwest) of tenth (west) triangle.
    ASSERT_EQ(out_vertices[29].z, 2.0f);

    ASSERT_EQ(out_vertices[30].x, 0.5f); // first vertex (center) of 11th (north) triangle.
    ASSERT_EQ(out_vertices[30].z, 1.5f);

    ASSERT_EQ(out_vertices[31].x, 0.0f); // second vertex (northwest) of 11th (north) triangle.
    ASSERT_EQ(out_vertices[31].z, 2.0f);

    ASSERT_EQ(out_vertices[32].x, 1.0f); // third vertex (northeast) of 11th (north) triangle.
    ASSERT_EQ(out_vertices[32].z, 2.0f);

    ASSERT_EQ(out_vertices[33].x, 0.5f); // first vertex (center) of 12th (east) triangle.
    ASSERT_EQ(out_vertices[33].z, 1.5f);

    ASSERT_EQ(out_vertices[34].x, 1.0f); // second vertex (northeast) of 12th (east) triangle.
    ASSERT_EQ(out_vertices[34].z, 2.0f);

    ASSERT_EQ(out_vertices[35].x, 1.0f); // third vertex (southeast) of 12th (east) triangle.
    ASSERT_EQ(out_vertices[35].z, 1.0f);

    ASSERT_EQ(out_vertices[36].x, 1.5f); // first vertex (center) of 13th (south) triangle.
    ASSERT_EQ(out_vertices[36].z, 1.5f);

    ASSERT_EQ(out_vertices[37].x, 2.0f); // second vertex (southeast) of 13th (south) triangle.
    ASSERT_EQ(out_vertices[37].z, 1.0f);

    ASSERT_EQ(out_vertices[38].x, 1.0f); // third vertex (southwest) of 13th (south) triangle.
    ASSERT_EQ(out_vertices[38].z, 1.0f);

    ASSERT_EQ(out_vertices[39].x, 1.5f); // first vertex (center) of 14th (west) triangle.
    ASSERT_EQ(out_vertices[39].z, 1.5f);

    ASSERT_EQ(out_vertices[40].x, 1.0f); // second vertex (southwest) of 14th (west) triangle.
    ASSERT_EQ(out_vertices[40].z, 1.0f);

    ASSERT_EQ(out_vertices[41].x, 1.0f); // third vertex (northwest) of 14th (west) triangle.
    ASSERT_EQ(out_vertices[41].z, 2.0f);

    ASSERT_EQ(out_vertices[42].x, 1.5f); // first vertex (center) of 15th (north) triangle.
    ASSERT_EQ(out_vertices[42].z, 1.5f);

    ASSERT_EQ(out_vertices[43].x, 1.0f); // second vertex (northwest) of 15th (north) triangle.
    ASSERT_EQ(out_vertices[43].z, 2.0f);

    ASSERT_EQ(out_vertices[44].x, 2.0f); // third vertex (northeast) of 15th (north) triangle.
    ASSERT_EQ(out_vertices[44].z, 2.0f);

    ASSERT_EQ(out_vertices[45].x, 1.5f); // first vertex (center) of 16th (east) triangle.
    ASSERT_EQ(out_vertices[45].z, 1.5f);

    ASSERT_EQ(out_vertices[46].x, 2.0f); // second vertex (northeast) of 16th (east) triangle.
    ASSERT_EQ(out_vertices[46].z, 2.0f);

    ASSERT_EQ(out_vertices[47].x, 2.0f); // third vertex (southeast) of 16th (east) triangle.
    ASSERT_EQ(out_vertices[47].z, 1.0f);

    // TODO: add assertions for vertices, UVs and normals!
}
TEST(a_BMP_world_must_be_loaded_appropriately, load_256x256_BMP_world)
{
    std::string image_path = "noise256x256.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    uint32_t image_width = 0;
    uint32_t image_height = 0;
    std::string color_channel = "mean";
    uint32_t x_step = 1;
    uint32_t z_step = 1;
    std::string triangulation_type = "bilinear_interpolation";

    bool model_loading_result = loaders::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel,
            x_step,
            z_step,
            triangulation_type);

    ASSERT_TRUE(model_loading_result);

    const uint32_t n_vertices_for_face = 3;
    const uint32_t n_faces_for_bilinear_triangulation = 4;
    const uint32_t n_width_of_image_file = 256;
    const uint32_t n_height_of_image_file = 256;

    ASSERT_EQ(out_vertices.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_UVs.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_normals.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
}
TEST(a_2x2_world_must_be_triangulated_appropriately, bilinear_interpolation)
{
    // *---*
    // |\ /|
    // | * |
    // |/ \|
    // *---*
    // bilinear interpolation.
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    uint32_t world_size = image_width * image_height;

    uint32_t* vertex_data;
    vertex_data = new uint32_t[world_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    uint32_t southwest_height = 1;
    uint32_t southeast_height = 2;
    uint32_t northwest_height = 4;
    uint32_t northeast_height = 8;
    float center_x = 0.5f;
    float center_z = 0.5f;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "bilinear_interpolation";

    bool is_success = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 12);
    ASSERT_EQ(UVs.size(), 12);
    ASSERT_EQ(normals.size(), 12);

    // 1st vertex is the center vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, center_x);
    ASSERT_EQ(vertices[0].z, center_z);
    ASSERT_EQ(vertices[0].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4.0f);

    // 2nd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 1.0f);
    ASSERT_EQ(vertices[1].z, 0.0f);
    ASSERT_EQ(vertices[1].y, southeast_height);

    // 3rd vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 0.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, southwest_height);

    // 4th vertex is the center vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, center_x);
    ASSERT_EQ(vertices[3].z, center_z);
    ASSERT_EQ(vertices[3].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4.0f);

    // 5th vertex is the southwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 0.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, southwest_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, northwest_height);

    // 7th vertex is the center vertex of the 3rd triangle.
    ASSERT_EQ(vertices[6].x, center_x);
    ASSERT_EQ(vertices[6].z, center_z);
    ASSERT_EQ(vertices[6].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4.0f);

    // 8th vertex is the northwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[7].x, 0.0f);
    ASSERT_EQ(vertices[7].z, 1.0f);
    ASSERT_EQ(vertices[7].y, northwest_height);

    // 9th vertex is the northeast vertex of the 3rd triangle.
    ASSERT_EQ(vertices[8].x, 1.0f);
    ASSERT_EQ(vertices[8].z, 1.0f);
    ASSERT_EQ(vertices[8].y, northeast_height);

    // 10th vertex is the center vertex of the 4th triangle.
    ASSERT_EQ(vertices[9].x, center_x);
    ASSERT_EQ(vertices[9].z, center_z);
    ASSERT_EQ(vertices[9].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4);

    // 11th vertex is the northeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[10].x, 1.0f);
    ASSERT_EQ(vertices[10].z, 1.0f);
    ASSERT_EQ(vertices[10].y, northeast_height);

    // 12th vertex is the southeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[11].x, 1.0f);
    ASSERT_EQ(vertices[11].z, 0.0f);
    ASSERT_EQ(vertices[11].y, southeast_height);
}
TEST(a_2x2_world_must_be_triangulated_appropriately, southeast_northwest_edges)
{
    // *---*
    // |\  |
    // | \ |
    // |  \|
    // *---*
    // southeast northwest edges.
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    uint32_t world_size = image_width * image_height;

    uint32_t* vertex_data;
    vertex_data = new uint32_t[world_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    uint32_t southwest_height = 1;
    uint32_t southeast_height = 2;
    uint32_t northwest_height = 4;
    uint32_t northeast_height = 8;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southeast_northwest_edges";

    bool is_success = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 6);
    ASSERT_EQ(UVs.size(), 6);
    ASSERT_EQ(normals.size(), 6);

    // 1st vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 0.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, southwest_height);

    // 2nd vertex is the northwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 1.0f);
    ASSERT_EQ(vertices[1].y, northwest_height);

    // 3rd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, southeast_height);

    // 4th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 1.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, northeast_height);

    // 5th vertex is the southeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, southeast_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, northwest_height);
}
TEST(a_2x2_world_must_be_triangulated_appropriately, southwest_northeast_edges)
{
    // *---*
    // |  /|
    // | / |
    // |/  |
    // *---*
    // southwest northeast edges.
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    uint32_t world_size = image_width * image_height;

    uint32_t* vertex_data;
    vertex_data = new uint32_t[world_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    uint32_t southwest_height = 1;
    uint32_t southeast_height = 2;
    uint32_t northwest_height = 4;
    uint32_t northeast_height = 8;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southwest_northeast_edges";

    bool is_success = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 6);
    ASSERT_EQ(UVs.size(), 6);
    ASSERT_EQ(normals.size(), 6);

    // 1st vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 1.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, southeast_height);

    // 2nd vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 0.0f);
    ASSERT_EQ(vertices[1].y, southwest_height);

    // 3rd vertex is the northeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 1.0f);
    ASSERT_EQ(vertices[2].y, northeast_height);

    // 4th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 0.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, northwest_height);

    // 5th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 1.0f);
    ASSERT_EQ(vertices[4].y, northeast_height);

    // 6th vertex is the southwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 0.0f);
    ASSERT_EQ(vertices[5].y, southwest_height);
}
TEST(a_3x3_world_must_be_triangulated_appropriately, southeast_northwest_edges)
{
    // *---*---*
    // |\  |\  |
    // | \ | \ |
    // |  \|  \|
    // *---*---*
    // |\  |\  |
    // | \ | \ |
    // |  \|  \|
    // *---*---*
    // southeast northwest edges.
    uint32_t image_width = 3;
    uint32_t image_height = 3;
    uint32_t world_size = image_width * image_height;

    uint32_t* vertex_data;
    vertex_data = new uint32_t[world_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    uint32_t x0_z0_height = 10;
    uint32_t x1_z0_height = 20;
    uint32_t x2_z0_height = 30;
    uint32_t x0_z1_height = 40;
    uint32_t x1_z1_height = 50;
    uint32_t x2_z1_height = 60;
    uint32_t x0_z2_height = 70;
    uint32_t x1_z2_height = 80;
    uint32_t x2_z2_height = 90;

    // 0, 0: 10.
    *vertex_pointer++ = x0_z0_height;
    // 1, 0: 20.
    *vertex_pointer++ = x1_z0_height;
    // 2, 0: 30.
    *vertex_pointer++ = x2_z0_height;
    // 0, 1: 40.
    *vertex_pointer++ = x0_z1_height;
    // 1, 1: 50.
    *vertex_pointer++ = x1_z1_height;
    // 2, 1: 60.
    *vertex_pointer++ = x2_z1_height;
    // 0, 2: 70.
    *vertex_pointer++ = x0_z2_height;
    // 1, 2: 80.
    *vertex_pointer++ = x1_z2_height;
    // 2, 2: 90.
    *vertex_pointer++ = x2_z2_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southeast_northwest_edges";

    bool is_success = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 24);
    ASSERT_EQ(UVs.size(), 24);
    ASSERT_EQ(normals.size(), 24);

    // 1st vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 0.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, x0_z0_height);

    // 2nd vertex is the northwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 1.0f);
    ASSERT_EQ(vertices[1].y, x0_z1_height);

    // 3rd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, x1_z0_height);

    // 4th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 1.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, x1_z1_height);

    // 5th vertex is the southeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, x1_z0_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, x0_z1_height);

    // 7th vertex is the southwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[6].x, 1.0f);
    ASSERT_EQ(vertices[6].z, 0.0f);
    ASSERT_EQ(vertices[6].y, x1_z0_height);

    // 8th vertex is the northwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[7].x, 1.0f);
    ASSERT_EQ(vertices[7].z, 1.0f);
    ASSERT_EQ(vertices[7].y, x1_z1_height);

    // 9th vertex is the southeast vertex of the 3rd triangle.
    ASSERT_EQ(vertices[8].x, 2.0f);
    ASSERT_EQ(vertices[8].z, 0.0f);
    ASSERT_EQ(vertices[8].y, x2_z0_height);

    // 10th vertex is the northeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[9].x, 2.0f);
    ASSERT_EQ(vertices[9].z, 1.0f);
    ASSERT_EQ(vertices[9].y, x2_z1_height);

    // 11th vertex is the southeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[10].x, 2.0f);
    ASSERT_EQ(vertices[10].z, 0.0f);
    ASSERT_EQ(vertices[10].y, x2_z0_height);

    // 12th vertex is the northwest vertex of the 4th triangle.
    ASSERT_EQ(vertices[11].x, 1.0f);
    ASSERT_EQ(vertices[11].z, 1.0f);
    ASSERT_EQ(vertices[11].y, x1_z1_height);

    // 13th vertex is the southwest vertex of the 5th triangle.
    ASSERT_EQ(vertices[12].x, 0.0f);
    ASSERT_EQ(vertices[12].z, 1.0f);
    ASSERT_EQ(vertices[12].y, x0_z1_height);

    // 14th vertex is the northwest vertex of the 5th triangle.
    ASSERT_EQ(vertices[13].x, 0.0f);
    ASSERT_EQ(vertices[13].z, 2.0f);
    ASSERT_EQ(vertices[13].y, x0_z2_height);

    // 15th vertex is the southeast vertex of the 5th triangle.
    ASSERT_EQ(vertices[14].x, 1.0f);
    ASSERT_EQ(vertices[14].z, 1.0f);
    ASSERT_EQ(vertices[14].y, x1_z1_height);

    // 16th vertex is the northeast vertex of the 6th triangle.
    ASSERT_EQ(vertices[15].x, 1.0f);
    ASSERT_EQ(vertices[15].z, 2.0f);
    ASSERT_EQ(vertices[15].y, x1_z2_height);

    // 17th vertex is the southeast vertex of the 6th triangle.
    ASSERT_EQ(vertices[16].x, 1.0f);
    ASSERT_EQ(vertices[16].z, 1.0f);
    ASSERT_EQ(vertices[16].y, x1_z1_height);

    // 18th vertex is the northwest vertex of the 6th triangle.
    ASSERT_EQ(vertices[17].x, 0.0f);
    ASSERT_EQ(vertices[17].z, 2.0f);
    ASSERT_EQ(vertices[17].y, x0_z2_height);

    // 19th vertex is the southwest vertex of the 7th triangle.
    ASSERT_EQ(vertices[18].x, 1.0f);
    ASSERT_EQ(vertices[18].z, 1.0f);
    ASSERT_EQ(vertices[18].y, x1_z1_height);

    // 20th vertex is the northwest vertex of the 7th triangle.
    ASSERT_EQ(vertices[19].x, 1.0f);
    ASSERT_EQ(vertices[19].z, 2.0f);
    ASSERT_EQ(vertices[19].y, x1_z2_height);

    // 21st vertex is the southeast vertex of the 7th triangle.
    ASSERT_EQ(vertices[20].x, 2.0f);
    ASSERT_EQ(vertices[20].z, 1.0f);
    ASSERT_EQ(vertices[20].y, x2_z1_height);

    // 22nd vertex is the northeast vertex of the 8th triangle.
    ASSERT_EQ(vertices[21].x, 2.0f);
    ASSERT_EQ(vertices[21].z, 2.0f);
    ASSERT_EQ(vertices[21].y, x2_z2_height);

    // 23th vertex is the southeast vertex of the 8th triangle.
    ASSERT_EQ(vertices[22].x, 2.0f);
    ASSERT_EQ(vertices[22].z, 1.0f);
    ASSERT_EQ(vertices[22].y, x2_z1_height);

    // 24th vertex is the northwest vertex of the 8th triangle.
    ASSERT_EQ(vertices[23].x, 1.0f);
    ASSERT_EQ(vertices[23].z, 2.0f);
    ASSERT_EQ(vertices[23].y, x1_z2_height);
}
