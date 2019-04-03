#ifndef __TEXTURE_HPP_INCLUDED
#define __TEXTURE_HPP_INCLUDED

#include "entity.hpp"
#include "texture_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        class Shader;

        class Texture: public yli::ontology::Entity
        {
            public:
                Texture(yli::ontology::Universe* const universe, const TextureStruct& texture_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = texture_struct.parent;
                    this->textureID = texture_struct.textureID;
                    this->framebuffer = 0;
                    this->texture = 0;
                    this->render_buffer = 0;

                    this->texture_width = texture_struct.texture_width;
                    this->texture_height = texture_struct.texture_height;

                    // Create FBO (off-screen framebuffer object).
                    glGenFramebuffers(1, &this->framebuffer);

                    // Bind offscreen buffer.
                    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

                    // Create texture.
                    glGenTextures(1, &this->texture);
                    glBindTexture(GL_TEXTURE_2D, this->texture);

                    // Define texture.
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texture_width, this->texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                    yli::opengl::set_filtering_parameters();

                    // Attach texture.
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);

                    // Create and bind render buffer with depth and stencil attachments.
                    glGenRenderbuffers(1, &this->render_buffer);
                    glBindRenderbuffer(GL_RENDERBUFFER, this->render_buffer);
                    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->texture_width, this->texture_height);
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer);

                    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                    {
                        std::cerr << "ERROR: `Texture::Texture`: framebuffer is not complete!\n";
                    }

                    // Get `childID` from `Shader` and set pointer to this `Texture`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Texture*";
                }

                // destructor.
                ~Texture();

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Shader* parent; // pointer to the `Shader`.

                std::size_t textureID;

                uint32_t framebuffer;
                uint32_t texture;
                uint32_t render_buffer;

                std::size_t texture_width;
                std::size_t texture_height;
        };
    }
}

#endif
