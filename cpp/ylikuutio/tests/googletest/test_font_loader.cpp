#include "gtest/gtest.h"
#include "cpp/ylikuutio/model/font_loader.hpp"
#include "cpp/ylikuutio/file/file_loader.hpp"

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

// Include standard headers
#include <cstring> // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <string>  // std::string
#include <vector>  // std::vector

TEST(glyphs_must_be_found_appropriately, kongtext_svg)
{
    std::string font_filename = "kongtext.svg";

    std::string file_content = file::slurp(font_filename);
    const uint32_t file_size = file_content.size();
    char* SVG_data = new char[file_size];
    std::strncpy(SVG_data, file_content.c_str(), file_size);

    const char* SVG_base_pointer;
    char* SVG_data_pointer;
    SVG_base_pointer = SVG_data;
    SVG_data_pointer = SVG_data;

    // SVG files are XML files, so we just need to read until we find the data we need.
    bool is_first_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_first_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x2e0);
    SVG_data_pointer++;

    bool is_second_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_second_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x320);
    SVG_data_pointer++;

    bool is_third_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_third_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x353);
    SVG_data_pointer++;

    bool is_fourth_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_fourth_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x386);
    SVG_data_pointer++;

    bool is_fifth_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_fifth_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x3b4);
    SVG_data_pointer++;

    bool is_sixth_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_sixth_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x3f2);
    SVG_data_pointer++;

    bool is_seventh_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_seventh_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x421);
    SVG_data_pointer++;

    bool is_eigth_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_eigth_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x48b);
    SVG_data_pointer++;

    bool is_ninth_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_ninth_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x4fc);
    SVG_data_pointer++;

    bool is_tenth_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);
    ASSERT_TRUE(is_tenth_glyph_found);
    ASSERT_EQ(SVG_data_pointer, SVG_base_pointer + 0x5d6);
}
TEST(font_must_be_loaded_appropriately, kongtext_svg)
{
    std::string font_filename = "kongtext.svg";

    std::vector<std::vector<std::vector<glm::vec3>>> glyph_vertex_data;
    std::vector<std::string> glyph_names;
    std::vector<std::string> unicode_strings;
    GLfloat vertex_scaling_factor = 1.0f;

    bool font_loading_result = model::load_SVG_font(
            font_filename,
            glyph_vertex_data,
            glyph_names,
            unicode_strings,
            vertex_scaling_factor);

    /*
    std::cout << "test at(0).c_str(): " << glyph_names.at(0).c_str() << "\n";
    ASSERT_EQ(std::strcmp(glyph_names.at(0).c_str(), "exclam"), 0);
    ASSERT_EQ(glyph_vertex_data.at(0).size(), 2); // 2 edge sections. d="M384 768h256v-512h-256v512zM384 128h256v-128h-256v128z"
    ASSERT_EQ(glyph_vertex_data.at(0).at(0).size(), 5); // d="M384 768h256v-512h-256v512z
    ASSERT_EQ(glyph_vertex_data.at(0).at(1).size(), 5); // M384 128h256v-128h-256v128z"
    */

    ASSERT_EQ(glyph_names.size(), 217);
    ASSERT_EQ(glyph_vertex_data.size(), 217);

    ASSERT_EQ(std::strcmp(glyph_names.at(0).c_str(), "nonmarkingreturn"), 0);
    ASSERT_EQ(glyph_vertex_data.at(0).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(1).c_str(), "space"), 0);
    ASSERT_EQ(glyph_vertex_data.at(1).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(3).c_str(), "quotedbl"), 0);
    ASSERT_EQ(glyph_vertex_data.at(3).size(), 2);        // 2 edge sections. d="M256 768h128v-384h-128v384zM640 768h128v-384h-128v384z"
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).size(), 5);  // d="M256 768h128v-384h-128v384z
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).size(), 5);  // M640 768h128v-384h-128v384z"

    ASSERT_EQ(std::strcmp(glyph_names.at(4).c_str(), "numbersign"), 0);
    ASSERT_EQ(glyph_vertex_data.at(4).size(), 2);        // 2 edge sections. d="M256 768h128v-128h256v128h128v-128h128v-128h-128v-128h128v-128h-128v-128h-128v128h-256v-128h-128v128h-128v128h128v128h-128v128h128v128zM384 512v-128h256v128h-256z"
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).size(), 29); // d="M256 768h128v-128h256v128h128v-128h128v-128h-128v-128h128v-128h-128v-128h-128v128h-256v-128h-128v128h-128v128h128v128h-128v128h128v128z
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).size(), 5);  // M384 512v-128h256v128h-256z"

    ASSERT_EQ(std::strcmp(glyph_names.at(5).c_str(), "dollar"), 0);
    ASSERT_EQ(glyph_vertex_data.at(5).size(), 1);        // complex polygon!
    ASSERT_EQ(glyph_vertex_data.at(5).at(0).size(), 29); // complex polygon!

    ASSERT_EQ(std::strcmp(glyph_names.at(6).c_str(), "percent"), 0);
    ASSERT_EQ(glyph_vertex_data.at(6).size(), 3);        // 3 edge sections. d="M128 896h256v-256h-256v256zM768 896h128v-256h-128v-128h-128v-128h-128v-128h-128v-128h-128v-128h-256v128h128v128h128v128h128v128h128v128h128v128h128v128zM640 256h256v-256h-256v256z"
    ASSERT_EQ(glyph_vertex_data.at(6).at(0).size(), 5);  // d="M128 896h256v-256h-256v256z
    ASSERT_EQ(glyph_vertex_data.at(6).at(1).size(), 27); // M768 896h128v-256h-128v-128h-128v-128h-128v-128h-128v-128h-128v-128h-256v128h128v128h128v128h128v128h128v128h128v128h128v128z
    ASSERT_EQ(glyph_vertex_data.at(6).at(2).size(), 5);  // M640 256h256v-256h-256v256z"

    ASSERT_EQ(std::strcmp(glyph_names.at(7).c_str(), "ampersand"), 0);
    ASSERT_EQ(glyph_vertex_data.at(7).size(), 4); // 3 edge sections. d="M256 768h384v-128h128v-128h256v-128h-128v-256h128v-128h-256v128h-128v-128h-512v128h-128v128h128v128h128v128h-128v128h128v128zM384 640v-128h128v128h-128zM640 512v-128h128v128h-128zM384 384v-128h-128v-128h384v128h-128v128h-128z"
    ASSERT_EQ(glyph_vertex_data.at(7).at(0).size(), 27); // d="M256 768h384v-128h128v-128h256v-128h-128v-256h128v-128h-256v128h-128v-128h-512v128h-128v128h128v128h128v128h-128v128h128v128z
    ASSERT_EQ(glyph_vertex_data.at(7).at(1).size(), 5);  // M384 640v-128h128v128h-128z
    ASSERT_EQ(glyph_vertex_data.at(7).at(2).size(), 5);  // M640 512v-128h128v128h-128z
    ASSERT_EQ(glyph_vertex_data.at(7).at(3).size(), 9);  // M384 384v-128h-128v-128h384v128h-128v128h-128z"

    ASSERT_EQ(std::strcmp(glyph_names.at(8).c_str(), "quotesingle"), 0);
    ASSERT_EQ(glyph_vertex_data.at(8).size(), 1);
    ASSERT_EQ(glyph_vertex_data.at(8).at(0).size(), 9);

    ASSERT_EQ(std::strcmp(glyph_names.at(9).c_str(), "parenleft"), 0);
    ASSERT_EQ(glyph_vertex_data.at(9).size(), 1);
    ASSERT_EQ(glyph_vertex_data.at(9).at(0).size(), 13);

    ASSERT_EQ(std::strcmp(glyph_names.at(207).c_str(), "quotedblbase"), 0);
    ASSERT_EQ(glyph_vertex_data.at(207).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(208).c_str(), "dagger"), 0);
    ASSERT_EQ(glyph_vertex_data.at(208).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(209).c_str(), "daggerdbl"), 0);
    ASSERT_EQ(glyph_vertex_data.at(209).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(210).c_str(), "bullet"), 0);
    ASSERT_EQ(glyph_vertex_data.at(210).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(211).c_str(), "ellipsis"), 0);
    ASSERT_EQ(glyph_vertex_data.at(211).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(212).c_str(), "perthousand"), 0);
    ASSERT_EQ(glyph_vertex_data.at(212).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(213).c_str(), "guilsinglleft"), 0);
    ASSERT_EQ(glyph_vertex_data.at(213).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(214).c_str(), "guilsinglright"), 0);
    ASSERT_EQ(glyph_vertex_data.at(214).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(215).c_str(), "Euro"), 0);
    ASSERT_EQ(glyph_vertex_data.at(215).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(216).c_str(), "trademark"), 0);
    ASSERT_EQ(glyph_vertex_data.at(216).size(), 2);        // 2 edge sections. d="M0 896h384v-128h-128v-256h-128v256h-128v128zM384 640h640v-384h-128v256h-128v-128h-128v128h-128v-256h-128v384z"
    ASSERT_EQ(glyph_vertex_data.at(216).at(0).size(), 9);  // d="M0 896h384v-128h-128v-256h-128v256h-128v128z
    ASSERT_EQ(glyph_vertex_data.at(216).at(1).size(), 13); // M384 640h640v-384h-128v256h-128v-128h-128v128h-128v-256h-128v384z"
}
