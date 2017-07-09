#ifndef __FONT_LOADER_HPP_INCLUDED
#define __FONT_LOADER_HPP_INCLUDED

// Include standard headers
#include <string>    // std::string
#include <vector>    // std::vector

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace loaders
{
    bool load_SVG_font(std::string font_file_path,
            std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
            std::vector<std::string>& glyph_names,
            std::vector<std::string>& unicode_strings);

    int32_t extract_value_from_string_with_standard_endings(char*& vertex_data_pointer, const char* const description);

    bool find_first_glyph_in_SVG(const char* SVG_base_pointer, char*& SVG_data_pointer);

    bool load_vertex_data(
            const char* SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<glm::vec2>>& current_glyph_vertices);

    bool load_SVG_glyph(
            const char* const SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
            std::vector<std::string>& glyph_names,
            std::vector<std::string>& unicode_strings);

    bool load_SVG_font(
            const std::string font_file_path,
            std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
            std::vector<std::string>& glyph_names,
            std::vector<std::string>& unicode_strings);
}

#endif
