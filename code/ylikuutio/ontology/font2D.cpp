#include "font2D.hpp"
#include "universe.hpp"
#include "text2D.hpp"
#include "text_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        void Font2D::bind_text2D(yli::ontology::Text2D* const text2D)
        {
            // get `childID` from `Font2D` and set pointer to `text2D`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Text2D*>(
                    text2D,
                    this->text2D_pointer_vector,
                    this->free_text2D_ID_queue,
                    this->number_of_text2Ds);
        }

        void Font2D::unbind_text2D(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->text2D_pointer_vector,
                    this->free_text2D_ID_queue,
                    this->number_of_text2Ds);
        }

        void Font2D::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `Font2D::bind_to_parent`: `universe` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `Universe` and set pointer to this `Font2D`.
            universe->bind_font2D(this);
        }

        Font2D::~Font2D()
        {
            // destructor.

            // Delete buffers
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);

            // Delete texture
            glDeleteTextures(1, &this->texture);

            // Delete shader
            glDeleteProgram(this->programID);
        }

        yli::ontology::Entity* Font2D::get_parent() const
        {
            return this->parent;
        }

        std::size_t Font2D::get_number_of_children() const
        {
            return this->number_of_text2Ds;
        }

        std::size_t Font2D::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->text2D_pointer_vector);
        }

        const std::string& Font2D::get_font_texture_file_format() const
        {
            return this->font_texture_file_format;
        }

        void Font2D::prepare_to_print()
        {
            // Bind shader
            glUseProgram(this->programID);

            // Bind texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture);
            // Set our "myTextureSampler" sampler to user Material Unit 0
            glUniform1i(this->Text2DUniformID, 0);

            // Set screen width.
            glUniform1i(this->screen_width_uniform_ID, this->screen_width);

            // Set screen height.
            glUniform1i(this->screen_height_uniform_ID, this->screen_height);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        void Font2D::print_text2D(
                std::size_t x,
                std::size_t y,
                std::size_t text_size,
                std::size_t font_size,
                const std::string text,
                const std::string font_texture_file_format,
                const std::string horizontal_alignment,
                const std::string vertical_alignment) const
        {
            // If horizontal alignment is `"left"`, each line begins from the same x coordinate.
            // If horizontal alignment is `"left"` and vertical alignment is `"top"`,
            // then there is no need to check the text beforehand for newlines.
            // Otherwise newlines need to be checked beforehand.
            //
            // If horizontal alignment is right, each line ends in the same x coordinate.
            // Newlines need to be checked beforehand.
            const std::size_t length = text.size();

            // Count the number of lines.
            std::size_t number_of_lines = 1;

            std::size_t i = 0;

            while (i < length)
            {
                char character = text[i++];

                if (i >= length)
                {
                    // Backslash `\` is the last character of string.
                    // End processing to avoid buffer over-read.
                    break;
                }

                if (character == (char) '\\')
                {
                    // OK, this character was backslash, so read the next character.
                    character = text[i++];

                    if (character == 'n')
                    {
                        number_of_lines++;
                    }
                }
            }

            std::size_t current_left_x;
            std::size_t current_top_y;

            if (horizontal_alignment == "left")
            {
                current_left_x = x;
            }
            else if (horizontal_alignment == "center")
            {
                current_left_x = x - 0.5f * length * text_size;
            }
            else if (horizontal_alignment == "right")
            {
                current_left_x = x - length * text_size;
            }
            else
            {
                std::cerr << "Invalid horizontal alignment: " << horizontal_alignment << "\n";
                return;
            }

            if (vertical_alignment == "top")
            {
                current_top_y = y;
            }
            else if (vertical_alignment == "center")
            {
                current_top_y = y + 0.5f * number_of_lines * text_size;
            }
            else if (vertical_alignment == "bottom")
            {
                current_top_y = y + number_of_lines * text_size;
            }
            else
            {
                std::cerr << "Invalid vertical alignment: " << vertical_alignment << "\n";
                return;
            }

            // Fill buffers
            std::vector<glm::vec2> vertices;
            std::vector<glm::vec2> UVs;

            i = 0;

            while (i < length)
            {
                // Print to the right side of X (so far there is no check for input length).
                // Print up of Y.
                std::size_t vertex_up_left_x;
                std::size_t vertex_up_left_y;
                std::size_t vertex_up_right_x;
                std::size_t vertex_up_right_y;
                std::size_t vertex_down_left_x;
                std::size_t vertex_down_left_y;
                std::size_t vertex_down_right_x;
                std::size_t vertex_down_right_y;

                char character = text[i++];

                if (character == (char) '\\')
                {
                    // OK, this character was backslash, so read the next character.
                    character = text[i++];

                    if (i >= length)
                    {
                        // Backslash `\` is the last character of string.
                        // End processing to avoid buffer over-read.
                        break;
                    }

                    if (character == 'n')
                    {
                        // jump to the beginning of the next line.
                        // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                        // TODO: implement newline for other horizontal and vertical alignments too!
                        current_left_x = x;
                        current_top_y -= text_size;
                        continue;
                    }
                }

                vertex_up_left_x = vertex_down_left_x = current_left_x;
                vertex_up_right_x = vertex_down_right_x = current_left_x + text_size;
                current_left_x += text_size;

                vertex_down_left_y = vertex_down_right_y = current_top_y - text_size;
                vertex_up_left_y = vertex_up_right_y = current_top_y;

                glm::vec2 vertex_up_left = glm::vec2(vertex_up_left_x, vertex_up_left_y);
                glm::vec2 vertex_up_right = glm::vec2(vertex_up_right_x, vertex_up_right_y);
                glm::vec2 vertex_down_left = glm::vec2(vertex_down_left_x, vertex_down_left_y);
                glm::vec2 vertex_down_right = glm::vec2(vertex_down_right_x, vertex_down_right_y);

                vertices.push_back(vertex_up_left);
                vertices.push_back(vertex_down_left);
                vertices.push_back(vertex_up_right);

                vertices.push_back(vertex_down_right);
                vertices.push_back(vertex_up_right);
                vertices.push_back(vertex_down_left);

                float uv_x = (character % font_size) / static_cast<float>(font_size);
                float uv_y;

                if (font_texture_file_format == "dds" || font_texture_file_format == "DDS")
                {
                    uv_y = (character / font_size) / static_cast<float>(font_size);
                }
                else if (font_texture_file_format == "bmp" || font_texture_file_format == "BMP")
                {
                    // BMP is stored in the file beginning from the bottom line.
                    uv_y = 1 - (character / font_size) / static_cast<float>(font_size);
                }
                else
                {
                    std::cerr << "invalid font_texture_file_format " << std::string(font_texture_file_format) << "\n";
                    return;
                }

                glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
                glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(font_size)), uv_y);
                glm::vec2 uv_down_right;
                glm::vec2 uv_down_left;

                if (font_texture_file_format == "dds" || font_texture_file_format == "DDS")
                {
                    uv_down_right = glm::vec2(uv_x + (1.0f / static_cast<float>(font_size)), (uv_y + 1.0f / static_cast<float>(font_size)));
                    uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(font_size)));
                }
                else if (font_texture_file_format == "bmp" || font_texture_file_format == "BMP")
                {
                    // BMP is stored in the file beginning from the bottom line.
                    uv_down_right = glm::vec2(uv_x + (1.0f / static_cast<float>(font_size)), (uv_y - 1.0f / static_cast<float>(font_size)));
                    uv_down_left = glm::vec2(uv_x, (uv_y - 1.0f / static_cast<float>(font_size)));
                }
                UVs.push_back(uv_up_left);
                UVs.push_back(uv_down_left);
                UVs.push_back(uv_up_right);

                UVs.push_back(uv_down_right);
                UVs.push_back(uv_up_right);
                UVs.push_back(uv_down_left);
            }

            glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

            // 1st attribute buffer : vertices
            glEnableVertexAttribArray(this->vertex_position_in_screenspaceID);
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
            glVertexAttribPointer(this->vertex_position_in_screenspaceID, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            // 2nd attribute buffer : UVs
            glEnableVertexAttribArray(this->vertexUVID);
            glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
            glVertexAttribPointer(this->vertexUVID, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

            // Draw call
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glDisableVertexAttribArray(this->vertex_position_in_screenspaceID);
            glDisableVertexAttribArray(this->vertexUVID);

            glDisable(GL_BLEND);
        }

        void Font2D::print_text2D(const TextStruct& text_struct) const
        {
            if (text_struct.text.empty())
            {
                this->print_text2D(
                        text_struct.x,
                        text_struct.y,
                        text_struct.text_size,
                        text_struct.font_size,
                        text_struct.text,
                        text_struct.font_texture_file_format,
                        text_struct.horizontal_alignment,
                        text_struct.vertical_alignment);
            }
            else
            {
                this->print_text2D(
                        text_struct.x,
                        text_struct.y,
                        text_struct.text_size,
                        text_struct.font_size,
                        text_struct.text,
                        text_struct.font_texture_file_format,
                        text_struct.horizontal_alignment,
                        text_struct.vertical_alignment);
            }
        }

        void Font2D::print_text2D(
                std::size_t x,
                std::size_t y,
                std::size_t text_size,
                std::size_t font_size,
                const std::string text,
                const std::string font_texture_file_format) const
        {
            this->print_text2D(x, y, text_size, font_size, text, font_texture_file_format, "left", "bottom");
        }
    }
}
