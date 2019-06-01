// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#include "font_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstdio>     // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>    // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <inttypes.h> // PRId32, PRId64, PRIu32, PRIu64, PRIx32, PRIx64
#include <iostream>   // std::cout, std::cin, std::cerr
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli
{
    namespace load
    {
        bool check_if_we_are_inside_block(const char* SVG_base_pointer, char*& SVG_data_pointer, const uint64_t data_size)
        {
            // This function returns `true` if we are inside block, `false` otherwise.

            // All possible block identifier strings.
            const std::vector<std::string> identifier_strings_vector
            { "<?xml ", "<!DOCTYPE ", "<svg>", "<metadata>", "</metadata>", "<defs>", "<font ", "<font-face", "<missing-glyph" };

            return yli::string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, data_size, identifier_strings_vector);
        }

        int32_t extract_value_from_string_with_standard_endings(
                const char* const vertex_base_pointer,
                char*& vertex_data_pointer,
                const uint64_t vertex_data_size,
                const char* const description,
                const bool is_debug_mode)
        {
            return yli::string::extract_int32_t_value_from_string(
                    vertex_base_pointer,
                    vertex_data_pointer,
                    vertex_data_size,
                    (const char* const) " Mmhvz\">",
                    is_debug_mode ? description : nullptr);
        }

        bool find_first_glyph_in_SVG(const char* SVG_base_pointer, char*& SVG_data_pointer, uint64_t data_size)
        {
            // This function advances `SVG_data_pointer` to the start of the first glyph.
            // Returns true if a glyph was found.
            // Returns false if no glyph was found.

            if (SVG_base_pointer == nullptr || SVG_data_pointer == nullptr)
            {
                return false;
            }

            bool is_inside_block = false;

            // Read bytes of SVG data until `"<glyph "` is encountered!
            while (true)
            {
                if (!is_inside_block)
                {
                    // OK, were are not inside a block.
                    if (SVG_data_pointer == nullptr)
                    {
                        return false;
                    }

                    if (yli::string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, data_size, std::vector<std::string> { "<glyph" }))
                    {
                        return true;
                    }
                    if (yli::string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, data_size, std::vector<std::string> { "</svg>" }))
                    {
                        return false;
                    }

                    is_inside_block = yli::load::check_if_we_are_inside_block(SVG_base_pointer, SVG_data_pointer, data_size);
                    SVG_data_pointer++;
                }
                else
                {
                    // OK, we are inside a block.
                    SVG_data_pointer = std::strchr(SVG_data_pointer, '>');
                    yli::string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, data_size, std::vector<std::string> { ">" });
                    is_inside_block = false;
                }
            }
        }

        bool load_vertex_data(
                const char* const SVG_base_pointer,
                char*& SVG_data_pointer,
                uint64_t data_size,
                std::vector<std::vector<glm::vec2>>& current_glyph_vertices,
                const bool is_debug_mode)
        {
            // This function returns a pointer to vertex data of a single glyph and advances `SVG_data_pointer`.

            std::vector<glm::vec2> vertices_of_current_edge_section;    // vertices of the current edge section.
            // d=" was found.
            // Follow the path and create the vertices accordingly.

            // Find the memory address of the opening double quote.
            char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
            if (opening_double_quote_pointer == nullptr)
            {
                std::cerr << "error: no opening double quote found for d=!\n";
                return false;
            }

            // Find the memory address of the closing double quote.
            char* closing_double_quote_pointer = strchr(++opening_double_quote_pointer, '"');
            if (closing_double_quote_pointer == nullptr)
            {
                std::cerr << "error: no closing double quote found for d=!\n";
                return false;
            }

            glm::vec2 current_vertex;
            char char_path[1024];

            // copy from opening double quote to the next `"/"`.
            yli::string::extract_string(SVG_base_pointer, opening_double_quote_pointer, data_size, char_path, char_path, sizeof(char_path), (char*) "/");

            if (is_debug_mode)
            {
                std::printf("d: %s\n", char_path);
            }

            // Loop through vertices and push them to `current_glyph_vertices`.
            char* vertex_data_pointer;
            vertex_data_pointer = char_path;

            while (true)
            {
                if (std::strncmp(vertex_data_pointer, "M", std::strlen("M")) == 0)
                {
                    current_vertex.x = yli::load::extract_value_from_string_with_standard_endings(
                            char_path,
                            ++vertex_data_pointer,
                            sizeof(char_path),
                            (const char* const) "M (moveto)",
                            is_debug_mode);

                    while (std::strncmp(vertex_data_pointer++, " ", std::strlen(" ")) != 0);

                    current_vertex.y = yli::load::extract_value_from_string_with_standard_endings(
                            char_path,
                            vertex_data_pointer,
                            sizeof(char_path),
                            (const char* const) "space (moveto y coordinate)",
                            is_debug_mode);

                    vertices_of_current_edge_section.push_back(current_vertex);

                } // if (std::strncmp(vertex_data_pointer, "M", std::strlen("M")) == 0)
                else if (std::strncmp(vertex_data_pointer, "h", std::strlen("h")) == 0)
                {
                    // OK, this is horizontal relative lineto.
                    int32_t horizontal_lineto_value = yli::load::extract_value_from_string_with_standard_endings(
                            char_path,
                            ++vertex_data_pointer,
                            sizeof(char_path),
                            (const char* const) "h (horizontal relative lineto)",
                            is_debug_mode);

                    current_vertex.x += horizontal_lineto_value;
                    vertices_of_current_edge_section.push_back(current_vertex);
                } // else if (std::strncmp(vertex_data_pointer, "h", std::strlen("h")) == 0)
                else if (std::strncmp(vertex_data_pointer, "v", std::strlen("v")) == 0)
                {
                    // OK, this is vertical relative lineto.
                    int32_t vertical_lineto_value = yli::load::extract_value_from_string_with_standard_endings(
                            char_path,
                            ++vertex_data_pointer,
                            sizeof(char_path),
                            (const char* const) "v (vertical relative lineto)",
                            is_debug_mode);

                    current_vertex.y += vertical_lineto_value;
                    vertices_of_current_edge_section.push_back(current_vertex);
                } // else if (std::strncmp(vertex_data_pointer, "v", std::strlen("v")) == 0)
                else if (std::strncmp(vertex_data_pointer, "z", std::strlen("z")) == 0)
                {
                    if (is_debug_mode)
                    {
                        std::printf("z (closepath)\n");
                    }

                    current_glyph_vertices.push_back(vertices_of_current_edge_section); // store the vertices of the current edge section.
                    vertices_of_current_edge_section.clear();                           // clear the vector of vertices of the current edge section.
                    vertex_data_pointer++;
                } // else if (std::strncmp(vertex_data_pointer, "z", std::strlen("z")) == 0)
                else if (std::strncmp(vertex_data_pointer, "\"", std::strlen("\"")) == 0)
                {
                    if (is_debug_mode)
                    {
                        std::printf("\" (end of vertex data)\n");
                    }

                    SVG_data_pointer = ++closing_double_quote_pointer;
                    return true;
                } // else if (std::strncmp(vertex_data_pointer, "\"", std::strlen("\"")) == 0)
                else
                {
                    vertex_data_pointer++;
                }
            } // while (true)
        }

        bool load_SVG_glyph(
                const char* const SVG_base_pointer,
                char*& SVG_data_pointer,
                uint64_t data_size,
                std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
                std::vector<std::string>& glyph_names,
                std::vector<std::string>& unicode_strings,
                const bool is_debug_mode)
        {
            // This function loads the next SVG glyph.
            // SVG_base_pointer: pointer to the origin of the SVG data.
            // SVG_data_pointer: pointer to the current reading address (must point to a glyph!).
            // out_glyph_vertex_data: vector of 2D objects consisting of 1 or more edge sections consisting of glm::vec2 vectors each of which is a vertex of a glyph.
            // glyph_names: vector of glyph names.
            // unicode_strings: vector of unicode strings.

            // A glyph was found!
            if (is_debug_mode)
            {
                std::printf("<glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
            }

            char char_glyph_name[1024];
            char char_unicode[1024];
            std::vector<std::vector<glm::vec2>> current_glyph_vertices; // vertices of the current glyph.
            bool has_glyph_name = false;
            bool has_glyph_unicode = false;

            while (true)
            {
                // Keep reading the glyph.
                if (std::strncmp(SVG_data_pointer, "glyph-name=", std::strlen("glyph-name=")) == 0)
                {
                    // A glyph-name was found.
                    // TODO: If the glyph does not have a glyph name, an empty string will be stored as glyph-name.
                    if (is_debug_mode)
                    {
                        std::printf("glyph-name= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                    }

                    // Find the memory address of the opening double quote.
                    char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                    if (opening_double_quote_pointer != nullptr)
                    {
                        if (is_debug_mode)
                        {
                            std::printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);
                        }

                        opening_double_quote_pointer++;

                        // Find the memory address of the closing double quote.
                        char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                        if (closing_double_quote_pointer != nullptr)
                        {
                            if (is_debug_mode)
                            {
                                std::printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                            }

                            has_glyph_name = true;

                            closing_double_quote_pointer++;

                            yli::string::extract_string(
                                    SVG_base_pointer,
                                    opening_double_quote_pointer,
                                    data_size,
                                    char_glyph_name,
                                    char_glyph_name,
                                    sizeof(char_glyph_name),
                                    (char*) "\"");

                            if (is_debug_mode)
                            {
                                std::printf("Glyph name: %s\n", char_glyph_name);
                            }

                            SVG_data_pointer = ++closing_double_quote_pointer;
                        } // if (closing_double_quote_pointer != nullptr)
                        else
                        {
                            std::cerr << "error: no closing double quote found for glyph-name=!\n";
                            return false;
                        }
                    } // if (opening_double_quote_pointer != nullptr)
                    else
                    {
                        std::cerr << "error: no opening double quote found for glyph-name=!\n";
                        return false;
                    }
                } // if (std::strncmp(SVG_data_pointer, "glyph-name=", std::strlen("glyph-name=")) == 0)
                else if (std::strncmp(SVG_data_pointer, "unicode=", std::strlen("unicode=")) == 0)
                {
                    // Unicode was found.
                    // TODO: If the glyph does not have unicode, the glyph will be discarded (as there is no way to refer to it).
                    if (is_debug_mode)
                    {
                        std::printf("unicode= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                    }

                    // Find the memory address of the opening double quote.
                    char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                    if (opening_double_quote_pointer != nullptr)
                    {
                        if (is_debug_mode)
                        {
                            std::printf("Opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);
                        }

                        opening_double_quote_pointer++;

                        // Find the memory address of the closing double quote.
                        char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                        if (closing_double_quote_pointer != nullptr)
                        {
                            if (is_debug_mode)
                            {
                                std::printf("Closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                            }

                            has_glyph_unicode = true;

                            yli::string::extract_string(
                                    SVG_base_pointer,
                                    opening_double_quote_pointer,
                                    data_size,
                                    char_unicode,
                                    char_unicode,
                                    sizeof(char_unicode),
                                    (char*) "\"");

                            if (is_debug_mode)
                            {
                                std::printf("Unicode: %s\n", char_unicode);
                            }

                            SVG_data_pointer = ++closing_double_quote_pointer;
                        } // if (closing_double_quote_pointer != nullptr)
                        else
                        {
                            std::cerr << "error: no closing double quote found for unicode=!\n";
                            return false;
                        }
                    } // if (opening_double_quote_pointer != nullptr)
                    else
                    {
                        std::cerr << "error: no opening double quote found for unicode=!\n";
                        return false;
                    }
                } // else if (std::strncmp(SVG_data_pointer, "unicode=", std::strlen("unicode=")) == 0)
                else if (std::strncmp(SVG_data_pointer, "d=", std::strlen("d=")) == 0)
                {
                    bool result = yli::load::load_vertex_data(SVG_base_pointer, SVG_data_pointer, data_size, current_glyph_vertices, is_debug_mode);
                    if (result == false)
                    {
                        return false;
                    }
                } // else if (std::strncmp(SVG_data_pointer, "d=", std::strlen("d=")) == 0)
                else if (std::strncmp(SVG_data_pointer, "/>", std::strlen("/>")) == 0)
                {
                    // OK, this is the end of this glyph.
                    if (has_glyph_unicode)
                    {
                        // OK, this glyph has an unicode, so it can be stored.
                        std::string glyph_unicode_string;
                        glyph_unicode_string = char_unicode;
                        unicode_strings.push_back(glyph_unicode_string);

                        std::string glyph_name_string;

                        if (!has_glyph_name)
                        {
                            glyph_name_string = "";
                        }
                        else
                        {
                            glyph_name_string = char_glyph_name;
                        }
                        glyph_names.push_back(glyph_name_string);

                        // TODO: Create default vertex vector (no vertices), if needed.
                        if (is_debug_mode)
                        {
                            std::printf("Number of vertices: %lu\n", current_glyph_vertices.size());
                        }

                        // Store the vertices of the current vector to the glyph vertex vector
                        // which contains the vertices of all the glyphs.
                        out_glyph_vertex_data.push_back(current_glyph_vertices);
                    } // if (has_glyph_unicode)
                    SVG_data_pointer += std::strlen("/>");
                    return true;
                } // else if (std::strncmp(SVG_data_pointer, ">", std::strlen(">")) == 0)
                else
                {
                    SVG_data_pointer++; // Advance to the next byte inside the glyph.
                }
            } // while (true)
        }

        bool load_SVG_font(
                const std::string font_file_path,
                std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
                std::vector<std::string>& glyph_names,
                std::vector<std::string>& unicode_strings,
                const bool is_debug_mode)
        {
            std::string file_content = yli::file::slurp(font_file_path);
            const uint64_t file_size = file_content.size();
            char* SVG_data = new char[file_size];

            if (SVG_data == nullptr)
            {
                std::cerr << "Reserving memory for SVG font data failed.\n";
                return false;
            }

            std::strncpy(SVG_data, file_content.c_str(), file_size);

            bool is_first_glyph_found;

            const char* SVG_base_pointer;
            char* SVG_data_pointer;
            SVG_base_pointer = SVG_data;
            SVG_data_pointer = SVG_data;

            // SVG files are XML files, so we just need to read until we find the data we need.
            is_first_glyph_found = yli::load::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer, file_size);

            if (!is_first_glyph_found || SVG_data_pointer == nullptr)
            {
                std::cerr << "no glyphs were found!\n";
                delete[] SVG_data;
                return false;
            }

            uint64_t offset = (uint64_t) SVG_data_pointer - (uint64_t) SVG_base_pointer;
            if (is_debug_mode)
            {
                std::printf("First glyph found at file offset 0x%" PRIx64 " (memory address 0x%" PRIx64 ").\n", offset, (uint64_t) SVG_data_pointer);
            }

            // Create the vertex data for each glyph in a loop.
            while (true)
            {
                if (std::strncmp(SVG_data_pointer, "<glyph", std::strlen("<glyph")) == 0)
                {
                    bool result = yli::load::load_SVG_glyph(
                            SVG_base_pointer,
                            SVG_data_pointer,
                            file_size,
                            out_glyph_vertex_data,
                            glyph_names,
                            unicode_strings,
                            is_debug_mode);

                    if (!result)
                    {
                        delete[] SVG_data;
                        return false;
                    }
                } // End of glyph.
                else
                {
                    const std::vector<std::string> string_vector { "</font>", "</defs>", "</svg>" };

                    if (yli::string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, file_size, string_vector))
                    {
                        delete[] SVG_data;
                        return true;
                    }
                    SVG_data_pointer++;
                }
            } // while (true)
        }
    }
}
