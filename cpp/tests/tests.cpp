#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif

#ifndef __CATCH_HPP_INCLUDED
#define __CATCH_HPP_INCLUDED
#include "catch.hpp"
#endif

#include "cpp/common/globals.hpp"
#include "cpp/common/shader_loader.hpp"
#include "cpp/common/texture_loader.hpp"
#include "cpp/common/vboindexer.hpp"
#include "cpp/common/text2D.hpp"
#include "cpp/common/text3D.hpp"
#include "cpp/common/world.hpp"
#include "cpp/common/shader.hpp"
#include "cpp/common/material.hpp"
#include "cpp/common/font.hpp"
#include "cpp/common/glyph.hpp"
#include "cpp/common/species.hpp"
#include "cpp/common/object.hpp"
#include "cpp/common/triangulation.hpp"
#include "cpp/common/triangulation.cpp"
#include "cpp/common/heightmap_loader.hpp"
#include "cpp/common/heightmap_loader.cpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#include <cmath>  // std::isnan
#include <string>
#include <vector> // std::vector

TEST_CASE("ShaderStruct must be initialized appropriately", "[ShaderStruct]")
{
    ShaderStruct test_shader_struct;
    REQUIRE(test_shader_struct.parent_pointer == NULL);
    REQUIRE(test_shader_struct.vertex_shader.empty());
    REQUIRE(test_shader_struct.fragment_shader.empty());
}

TEST_CASE("MaterialStruct must be initialized appropriately", "[MaterialStruct]")
{
    MaterialStruct test_material_struct;
    REQUIRE(test_material_struct.parent_pointer == NULL);
    REQUIRE(test_material_struct.texture_file_format.empty());
    REQUIRE(test_material_struct.texture_filename.empty());
    REQUIRE(test_material_struct.image_path.empty());
}

TEST_CASE("NodeStruct must be initialized appropriately", "[NodeStruct]")
{
    NodeStruct test_node_struct;
    REQUIRE(test_node_struct.parent_pointer == NULL);
    REQUIRE(test_node_struct.coordinate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_node_struct.neighbor_nodeIDs.size() == 0);
}

TEST_CASE("ObjectStruct must be initialized appropriately", "[ObjectStruct]")
{
    ObjectStruct test_object_struct;
    REQUIRE(test_object_struct.species_parent_pointer == NULL);
    REQUIRE(test_object_struct.glyph_parent_pointer == NULL);
    REQUIRE(test_object_struct.original_scale_vector == glm::vec3(1.0f, 1.0f, 1.0f));
    REQUIRE(std::isnan(test_object_struct.rotate_angle));
    REQUIRE(test_object_struct.is_character == false);
    REQUIRE(test_object_struct.coordinate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_object_struct.rotate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_object_struct.translate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
}

TEST_CASE("SpeciesStruct must be initialized appropriately", "[SpeciesStruct]")
{
    SpeciesStruct test_species_struct;
    REQUIRE(test_species_struct.parent_pointer == NULL);
    REQUIRE(test_species_struct.is_world == false);
    REQUIRE(std::isnan(test_species_struct.world_radius));
    REQUIRE(test_species_struct.model_file_format.empty());
    REQUIRE(test_species_struct.model_filename.empty());
    REQUIRE(test_species_struct.color_channel.empty());
    REQUIRE(test_species_struct.light_position == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_species_struct.coordinate_system.empty());
}

TEST_CASE("FontStruct must be initialized appropriately", "[FontStruct]")
{
    FontStruct test_font_struct;
    REQUIRE(test_font_struct.parent_pointer == NULL);
    REQUIRE(test_font_struct.vertex_scaling_factor == DEFAULT_VERTEX_SCALING_FACTOR);
    REQUIRE(test_font_struct.font_file_format.empty());
    REQUIRE(test_font_struct.font_filename.empty());
}

TEST_CASE("GlyphStruct must be initialized appropriately", "[GlyphStruct]")
{
    GlyphStruct test_glyph_struct;
    REQUIRE(test_glyph_struct.parent_pointer == NULL);
    REQUIRE(test_glyph_struct.light_position == glm::vec3(0.0f, 0.0f, 0.0f));
}

TEST_CASE("2x2 world must be triangulated appropriately using bilinear interpolation", "[triangulate_2x2_world_bilinear]")
{
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    uint32_t world_size = image_width * image_height;

    GLuint* vertex_data;
    vertex_data = new GLuint [world_size];
    GLuint* vertex_pointer = vertex_data;
    // x, z: height (y).
#define SOUTHWEST_HEIGHT 1
#define SOUTHEAST_HEIGHT 2
#define NORTHWEST_HEIGHT 4
#define NORTHEAST_HEIGHT 8

    // 0, 0: 1.
    *vertex_data++ = SOUTHWEST_HEIGHT;
    // 1, 0: 2.
    *vertex_data++ = SOUTHEAST_HEIGHT;
    // 0, 1: 4.
    *vertex_data++ = NORTHWEST_HEIGHT;
    // 1, 1: 8.
    *vertex_data++ = NORTHEAST_HEIGHT;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.input_vertex_pointer = vertex_data;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.triangulation_type = "bilinear_interpolation";
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    bool is_success = geometry::triangulate_quads(triangulate_quads_struct, vertices, UVs, normals);
    REQUIRE(is_success == true);
    REQUIRE(vertices.size() == 12);
    REQUIRE(UVs.size() == 12);
    REQUIRE(normals.size() == 12);
}

TEST_CASE("3x3 BMP world must be loaded appropriately", "[load_3x3_BMP_world]")
{
    std::string image_path = "test3x3.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    GLuint image_width = 0;
    GLuint image_height = 0;
    std::string color_channel = "mean";

    std::string triangulation_type = "bilinear_interpolation";

    bool model_loading_result = model::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel,
            triangulation_type);
#define N_VERTICES_FOR_FACE 3
#define N_FACES_FOR_BILINEAR_TRIANGULATION 4
#define N_WIDTH_OF_IMAGE_FILE 3
#define N_HEIGHT_OF_IMAGE_FILE 3

    REQUIRE(out_vertices.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_UVs.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_normals.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));

#undef N_VERTICES_FOR_FACE
#undef N_FACES_FOR_BILINEAR_TRIANGULATION
#undef N_WIDTH_OF_IMAGE_FILE
#undef N_HEIGHT_OF_IMAGE_FILE
}

TEST_CASE("256x256 BMP world must be loaded appropriately", "[load_256x256_BMP_world]")
{
    std::string image_path = "noise256x256.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    GLuint image_width = 0;
    GLuint image_height = 0;
    std::string color_channel = "mean";
    std::string triangulation_type = "bilinear_interpolation";

    bool model_loading_result = model::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel,
            triangulation_type);
#define N_VERTICES_FOR_FACE 3
#define N_FACES_FOR_BILINEAR_TRIANGULATION 4
#define N_WIDTH_OF_IMAGE_FILE 256
#define N_HEIGHT_OF_IMAGE_FILE 256

    REQUIRE(out_vertices.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_UVs.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_normals.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));

#undef N_VERTICES_FOR_FACE
#undef N_FACES_FOR_BILINEAR_TRIANGULATION
#undef N_WIDTH_OF_IMAGE_FILE
#undef N_HEIGHT_OF_IMAGE_FILE
}
