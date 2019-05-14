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
                    this->output_filename = compute_task_struct.output_filename;
                    this->parent = compute_task_struct.parent;
                    this->end_condition_callback_engine = compute_task_struct.end_condition_callback_engine;

                    this->result_vector = nullptr;

                    this->n_max_iterations = compute_task_struct.n_max_iterations;
                    this->compute_taskID = compute_task_struct.compute_taskID;
                    this->texture_width = compute_task_struct.texture_width;
                    this->texture_height = compute_task_struct.texture_height;
                    this->n_index_characters = compute_task_struct.n_index_characters;

                    // variables related to the framebuffer.
                    this->framebuffer                  = 0; // some dummy value.
                    this->source_texture               = 0; // some dummy value.
                    this->target_texture               = 0; // some dummy value.
                    this->openGL_textureID             = 0; // some dummy value.
                    this->is_texture_loaded            = false;
                    this->is_framebuffer_initialized   = false;
                    this->is_ready                     = false;

                    this->vertex_position_modelspaceID = 0; // some dummy value.
                    this->vertexUVID                   = 0; // some dummy value.
                    this->screen_width_uniform_ID      = 0; // some dummy value.
                    this->screen_height_uniform_ID     = 0; // some dummy value.
                    this->iteration_i_uniform_ID       = 0; // some dummy value.
                    this->vertexbuffer                 = 0; // some dummy value.
                    this->uvbuffer                     = 0; // some dummy value.

                    this->format                       = compute_task_struct.format;
                    this->internal_format              = compute_task_struct.internal_format;
                    this->type                         = compute_task_struct.type;
                    this->should_ylikuutio_save_intermediate_results = compute_task_struct.should_ylikuutio_save_intermediate_results;
                    this->should_ylikuutio_flip_texture              = compute_task_struct.should_ylikuutio_flip_texture;

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
                        else
                        {
                            this->is_texture_loaded = true;
                        }
                    }
                    else if (this->texture_file_format == "dds" || this->texture_file_format == "DDS")
                    {
                        if (!yli::load::load_DDS_texture(this->texture_filename, this->texture_width, this->texture_height, this->texture_size, this->source_texture))
                        {
                            std::cerr << "ERROR: loading DDS texture failed!\n";
                        }
                        else
                        {
                            this->is_texture_loaded = true;
                        }
                    }
                    else if (this->texture_file_format == "csv" || this->texture_file_format == "CSV")
                    {
                        if (!yli::load::load_CSV_texture(
                                    this->texture_filename,
                                    this->format,
                                    this->internal_format,
                                    this->type,
                                    this->texture_width,
                                    this->texture_height,
                                    this->texture_size,
                                    this->source_texture))
                        {
                            std::cerr << "ERROR: loading CSV texture failed!\n";
                        }
                        else
                        {
                            this->is_texture_loaded = true;
                        }
                    }
                    else
                    {
                        std::cerr << "no texture was loaded!\n";
                        std::cerr << "texture file format: " << this->texture_file_format << "\n";
                    }

                    if (this->is_texture_loaded)
                    {
                        // Get a handle for our "texture_sampler" uniform.
                        this->openGL_textureID = glGetUniformLocation(this->parent->get_programID(), "texture_sampler");

                        // Initialize uniform window width.
                        // This is named `screen_width` instead of `texture_width` for compatibility with other shaders.
                        this->screen_width_uniform_ID = glGetUniformLocation(this->parent->get_programID(), "screen_width");
                        glUniform1i(this->screen_width_uniform_ID, this->texture_width);

                        // Initialize uniform window height.
                        // This is named `screen_height` instead of `texture_height` for compatibility with other shaders.
                        this->screen_height_uniform_ID = glGetUniformLocation(this->parent->get_programID(), "screen_height");
                        glUniform1i(this->screen_height_uniform_ID, this->texture_height);

                        // Initialize uniform iteration index.
                        this->iteration_i_uniform_ID = glGetUniformLocation(this->parent->get_programID(), "iteration_i");
                        glUniform1i(this->iteration_i_uniform_ID, 0);

                        // Create model (a square which consists of 2 triangles).
                        // *---*
                        // |  /|
                        // | / |
                        // |/  |
                        // *---*
                        const std::vector<glm::vec2> vertices
                        { { -1.0f, 1.0f }, { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 1.0f, -1.0f }, { 1.0f, 1.0f }, { -1.0f, -1.0f } };
                        this->vertices_size = vertices.size();

                        const std::vector<glm::vec2> uvs
                        { { 0.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f } };
                        this->uvs_size = uvs.size();

                        // Load model into a VBO.

                        // Vertices.
                        glGenBuffers(1, &this->vertexbuffer);
                        glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

                        // UVs.
                        glGenBuffers(1, &this->uvbuffer);
                        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
                        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
                    }

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

                std::string texture_file_format; // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"csv"`/`"CSV"`, `"dds"`/`"DDS"`.
                std::string texture_filename;    // Filename of the model file.
                std::string output_filename;     // Filename of the output file.

                yli::ontology::Shader* parent; // pointer to the `Shader`.

                // End iterating when `end_condition_callback_engine` returns `true`.
                std::shared_ptr<yli::callback_system::CallbackEngine> end_condition_callback_engine;

                std::shared_ptr<std::vector<uint8_t>> result_vector;

                // This is the maximum number of iterations.
                // If `end_condition_callback_engine` is `nullptr`, then this is the number of iterations.
                // If `end_condition_callback_engine` is not `nullptr`, then this is the maximum number of iterations.
                std::size_t n_max_iterations;

                std::size_t compute_taskID;

                std::size_t texture_width;
                std::size_t texture_height;
                std::size_t texture_size;

                std::size_t n_index_characters; // For intermediate results' filenames.

                std::size_t vertices_size;
                std::size_t uvs_size;

                // variables related to the framebuffer.
                uint32_t framebuffer;
                uint32_t source_texture;
                uint32_t target_texture;
                uint32_t openGL_textureID;           // Texture ID, returned by `glGetUniformLocation(this->parent->get_programID(), "texture_sampler")`.
                bool is_texture_loaded;
                bool is_framebuffer_initialized;
                bool is_ready;

                uint32_t vertex_position_modelspaceID;
                uint32_t vertexUVID;
                uint32_t screen_width_uniform_ID;          // Location of the program's window width uniform.
                uint32_t screen_height_uniform_ID;         // Location of the program's window height uniform.
                uint32_t iteration_i_uniform_ID;           // Location of the program's iteration index uniform.

                uint32_t vertexbuffer;
                uint32_t uvbuffer;

                GLenum format;
                GLenum internal_format;
                GLenum type;

                bool should_ylikuutio_save_intermediate_results;
                bool should_ylikuutio_flip_texture;

                PreIterateCallback preiterate_callback;
                PostIterateCallback postiterate_callback;
        };
    }
}

#endif
