#ifndef __COMPUTE_TASK_HPP_INCLUDED
#define __COMPUTE_TASK_HPP_INCLUDED

#include "entity.hpp"
#include "shader.hpp"
#include "compute_task_struct.hpp"
#include "pre_iterate_callback.hpp"
#include "post_iterate_callback.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/texture_loader.hpp"
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
                    this->texture_file_format = compute_task_struct.texture_file_format;
                    this->texture_filename = compute_task_struct.texture_filename;
                    this->parent = compute_task_struct.parent;
                    this->end_condition_callback_engine = compute_task_struct.end_condition_callback_engine;
                    this->n_max_iterations = compute_task_struct.n_max_iterations;
                    this->compute_taskID = compute_task_struct.compute_taskID;
                    this->texture_width = compute_task_struct.texture_width;
                    this->texture_height = compute_task_struct.texture_height;

                    // variables related to the framebuffer.
                    this->framebuffer                  = 0; // some dummy value.
                    this->source_texture               = 0; // some dummy value.
                    this->target_texture               = 0; // some dummy value.
                    this->openGL_textureID             = 0; // some dummy value.
                    this->is_framebuffer_initialized   = false;

                    this->vertex_position_modelspaceID = 0; // some dummy value.
                    this->vertexUVID                   = 0; // some dummy value.
                    this->vertexbuffer                 = 0; // some dummy value.
                    this->uvbuffer                     = 0; // some dummy value.

                    this->format                       = compute_task_struct.format;
                    this->type                         = compute_task_struct.type;

                    this->preiterate_callback = compute_task_struct.preiterate_callback;
                    this->postiterate_callback = compute_task_struct.postiterate_callback;

                    // Get `childID` from `Shader` and set pointer to this `ComputeTask`.
                    this->bind_to_parent();

                    // Get a handle for our buffers.
                    this->vertex_position_modelspaceID = glGetAttribLocation(this->parent->get_programID(), "vertex_position_modelspace");
                    this->vertexUVID = glGetAttribLocation(this->parent->get_programID(), "vertexUV");

                    glUseProgram(this->parent->get_programID());

                    // Load the source texture, just like in `yli::ontology::Material` constructor.
                    if (this->texture_file_format == "bmp" || this->texture_file_format == "BMP")
                    {
                        if (!yli::load::load_BMP_texture(this->texture_filename, this->texture_width, this->texture_height, this->texture_size, this->source_texture))
                        {
                            std::cerr << "ERROR: loading BMP texture failed!\n";
                        }
                    }
                    else if (this->texture_file_format == "dds" || this->texture_file_format == "DDS")
                    {
                        if (!yli::load::load_DDS_texture(this->texture_filename, this->texture_width, this->texture_height, this->texture_size, this->source_texture))
                        {
                            std::cerr << "ERROR: loading DDS texture failed!\n";
                        }
                    }
                    else
                    {
                        std::cerr << "no texture was loaded!\n";
                        std::cerr << "texture file format: " << this->texture_file_format << "\n";
                    }

                    // Get a handle for our "my_texture_sampler" uniform.
                    this->openGL_textureID = glGetUniformLocation(this->parent->get_programID(), "my_texture_sampler");

                    // Create model (a square which consists of 2 triangles).
                    // *---*
                    // |  /|
                    // | / |
                    // |/  |
                    // *---*
                    const std::vector<glm::vec3> vertices
                    { { 1.0f, 1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f }, { -1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
                    this->vertices_size = vertices.size();

                    const std::vector<glm::vec2> uvs
                    { { 1.0f, 1.0f }, { 1.0f, -1.0f }, { -1.0f, -1.0f }, { -1.0f, -1.0f }, { -1.0f, 1.0f }, { 1.0f, 1.0f } };
                    this->uvs_size = uvs.size();

                    // Load model into a VBO.

                    // Vertices.
                    glGenBuffers(1, &this->vertexbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

                    // UVs.
                    glGenBuffers(1, &this->uvbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
                    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::ComputeTask*";
                    this->can_be_erased = true;
                }

                ComputeTask(const ComputeTask&) = delete;            // Delete copy constructor.
                ComputeTask &operator=(const ComputeTask&) = delete; // Delete copy assignment.

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

                std::string texture_file_format; // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
                std::string texture_filename;    // Filename of the model file.

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
                std::size_t texture_size;

                std::size_t vertices_size;
                std::size_t uvs_size;

                // variables related to the framebuffer.
                uint32_t framebuffer;
                uint32_t source_texture;
                uint32_t target_texture;
                uint32_t openGL_textureID;           // Texture ID, returned by `glGetUniformLocation(this->parent->get_programID(), "my_texture_sampler")`.
                bool is_framebuffer_initialized;

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
