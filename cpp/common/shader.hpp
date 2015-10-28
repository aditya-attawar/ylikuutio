#ifndef __SHADER_HPP_INCLUDED
#define __SHADER_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "globals.hpp"
#include "shader_loader.hpp"
#include "model_common_functions.hpp"
#include "model_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <vector>    // std::vector
#include <queue>     // std::queue

namespace model
{
    class World;
    class Object;

    class Shader
    {
        public:
            // constructor.
            Shader(ShaderStruct shader_struct);

            // destructor.
            ~Shader();

            // this method sets pointer to this shader to NULL, sets `parent_pointer` according to the input, and requests a new `childID` from the new world.
            void bind_to_new_parent(model::World *new_world_pointer);

            friend class World;
            friend class Texture;
            friend class Glyph;
            friend class Species;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
            template<class T1, class T2>
                friend void bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<GLuint> &old_free_childID_queue);
            template<class T1>
                friend void render_this_object(model::Object* object_pointer, model::Shader* shader_pointer);

        private:
            // this method renders all textures using this shader.
            void render();

            // this method sets a texture pointer.
            void set_texture_pointer(GLuint childID, void* parent_pointer);

            // this method sets a world species pointer.
            void set_terrain_species_pointer(void* terrain_species_pointer);

            model::World *parent_pointer;         // pointer to the world.

            GLuint programID;                     // shaders' programID, returned by `LoadShaders`.

            GLuint MatrixID;
            GLuint ViewMatrixID;
            GLuint ModelMatrixID;

            void bind_to_parent();

            void* terrain_species_pointer;          // pointer to world species (used in collision detection).

            GLuint childID;                       // shader ID, returned by `model::World->get_shaderID()`.

            std::string vertex_shader;            // filename of vertex shader.
            std::string fragment_shader;          // filename of fragment shader.

            std::vector<void*> texture_pointer_vector;
            std::queue<GLuint> free_textureID_queue;

            const char* char_vertex_shader;
            const char* char_fragment_shader;
    };
}

#endif
