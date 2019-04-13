#ifndef __COMPUTE_TASK_HPP_INCLUDED
#define __COMPUTE_TASK_HPP_INCLUDED

#include "entity.hpp"
#include "compute_task_struct.hpp"
#include "pre_iterate_callback.hpp"
#include "post_iterate_callback.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

// `yli::ontology::ComputeTask` is a class which contains the data for a single
// computing task. `ComputeTask` does not have the OpenGL shaders used to process
// the data. Instead, the shaders are contained by the parent `Entity` which is
// an `yli::ontology::ComputeTask` instance.
//
// For example, `yli::ontology::Shader` can have vertex and fragment shaders for
// computing the distances between nodes of a graph. Then, each `ComputeTask`
// would contain the graph data, eg. as a distance matrix. Then, rendering a
// `ComputeTask` means computing that task.
//
// Rendering a `ComputeTask` is done by iterating the task until either
// `end_condition_callback_engine->execute()` returns `true`, or until
// `n_max_iterations` is reached. If `end_condition_callback_engine` is `nullptr`
// or `end_condition_callback_engine->execute()` does not not return an `AnyValue`
// which contains `datatypes::BOOL`, then `end_condition_callback_engine` is ignored
// and `n_max_iterations` is the exact number of iterations to be done. However,
// even if `end_condition_callback_engine->execute()` would return an invalid return
// value, that is, not an `AnyValue` which contains `datatypes::BOOL`,
// `end_condition_callback_engine->execute()` is still called and taken into account
// in every iteration.
//
// When iterating, there is a `PreIterateCallback` which is executed before each iteration,
// and also a `PostIterateCallback` which is executed correspondingly after each iteration.
// Of course `PreRenderCallback` and `PostRenderCallback` can be used as well.
// `PreRenderCallback` gets executed before the first `PreIterateCallback` call, and
// `PostRenderCallback` gets executed after the last `PostRenderCallback` call.
// All these callbacks are optional and can be left to `nullptr` if they are not needed.

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
    }

    namespace ontology
    {
        class Shader;

        class ComputeTask: public yli::ontology::Entity
        {
            public:
                ComputeTask(yli::ontology::Universe* const universe, const ComputeTaskStruct& compute_task_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = compute_task_struct.parent;
                    this->end_condition_callback_engine = compute_task_struct.end_condition_callback_engine;
                    this->n_max_iterations = compute_task_struct.n_max_iterations;
                    this->compute_taskID = compute_task_struct.compute_taskID;
                    this->texture_width = compute_task_struct.texture_width;
                    this->texture_height = compute_task_struct.texture_height;

                    this->framebuffer                  = 0;
                    this->texture                      = 0;
                    this->render_buffer                = 0;
                    this->vertex_position_modelspaceID = 0;
                    this->vertexUVID                   = 0;
                    this->vertexbuffer                 = 0;
                    this->uvbuffer                     = 0;

                    this->format                       = compute_task_struct.format;
                    this->type                         = compute_task_struct.type;

                    this->preiterate_callback = compute_task_struct.preiterate_callback;
                    this->postiterate_callback = compute_task_struct.postiterate_callback;

                    // Get `childID` from `Shader` and set pointer to this `ComputeTask`.
                    this->bind_to_parent();

                    // Create model (a square which consists of 2 triangles).
                    // *---*
                    // |  /|
                    // | / |
                    // |/  |
                    // *---*
                    const std::vector<glm::vec3> vertices
                    { { 1.0f, 1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f }, { -1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };

                    const std::vector<glm::vec2> uvs
                    { { 1.0f, 1.0f }, { 1.0f, -1.0f }, { -1.0f, -1.0f }, { -1.0f, -1.0f }, { -1.0f, 1.0f }, { 1.0f, 1.0f } };

                    // Load model into a VBO.

                    // Vertices.
                    glGenBuffers(1, &this->vertexbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

                    // UVs.
                    glGenBuffers(1, &this->uvbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
                    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

                    // Create FBO (off-screen framebuffer object).
                    glGenFramebuffers(1, &this->framebuffer);

                    // Bind offscreen buffer.
                    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

                    // Create texture.
                    glGenTextures(1, &this->texture);
                    glBindTexture(GL_TEXTURE_2D, this->texture);

                    // Define texture.
                    glTexImage2D(GL_TEXTURE_2D, 0, this->format, this->texture_width, this->texture_height, 0, this->format, this->type, NULL);

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
                        std::cerr << "ERROR: `ComputeTask::ComputeTask`: framebuffer is not complete!\n";
                    }

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::ComputeTask*";
                    this->can_be_erased = true;
                }

                // destructor.
                ~ComputeTask();

                yli::ontology::Entity* get_parent() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend std::size_t yli::ontology::get_number_of_descendants(const std::vector<T1>& child_pointer_vector);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // This method renders this `ComputeTask`, that is, computes this task.
                void render();

                void preiterate() const;
                void postiterate() const;

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                yli::ontology::Shader* parent; // pointer to the `Shader`.

                // End iterating when `end_condition_callback_engine` returns `true`.
                std::shared_ptr<yli::callback_system::CallbackEngine> end_condition_callback_engine;

                // This is the maximum number of iterations.
                // If `end_condition_callback_engine` is `nullptr`, then this is the number of iterations.
                // If `end_condition_callback_engine` is not `nullptr`, then this is the maximum number of iterations.
                std::size_t n_max_iterations;

                std::size_t compute_taskID;

                std::size_t texture_width;
                std::size_t texture_height;

                uint32_t framebuffer;
                uint32_t texture;
                uint32_t render_buffer;

                uint32_t vertex_position_modelspaceID;
                uint32_t vertexUVID;

                uint32_t vertexbuffer;
                uint32_t uvbuffer;

                GLenum format;
                GLenum type;

                PreIterateCallback preiterate_callback;
                PostIterateCallback postiterate_callback;
        };
    }
}

#endif
