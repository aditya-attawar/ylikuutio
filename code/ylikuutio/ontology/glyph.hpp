#ifndef __GLYPH_HPP_INCLUDED
#define __GLYPH_HPP_INCLUDED

#include "species_or_glyph.hpp"
#include "model.hpp"
#include "glyph_struct.hpp"
#include "gl_attrib_locations.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/triangulation/triangulate_polygons_struct.hpp"
#include "code/ylikuutio/triangulation/polygon_triangulation.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class VectorFont;
    class Object;

    class Glyph: public ontology::Model
    {
        public:
            // destructor.
            // glyphs should be destroyed only by destroying the entire `VectorFont`.
            virtual ~Glyph();

            ontology::Entity* get_parent() const override;

            // this method sets a object pointer.
            void set_object_pointer(const int32_t childID, ontology::Object* const child_pointer);

            const char* get_unicode_char_pointer();

            friend class VectorFont;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);
            template<class T1>
                friend void render_children(const std::vector<T1>& child_pointer_vector);

        private:
            // constructor.
            Glyph(const GlyphStruct& glyph_struct)
                : Model(glyph_struct.universe)
            {
                // constructor.
                this->parent = glyph_struct.parent;

                this->glyph_vertex_data = glyph_struct.glyph_vertex_data;
                this->glyph_name_pointer = glyph_struct.glyph_name_pointer;
                this->unicode_char_pointer = glyph_struct.unicode_char_pointer;
                this->light_position = glyph_struct.light_position;

                // get `childID` from `VectorFont` and set pointer to this `Glyph`.
                this->bind_to_parent();

                // TODO: implement triangulation of `Glyph` objects!
                ylikuutio::geometry::TriangulatePolygonsStruct triangulate_polygons_struct;
                triangulate_polygons_struct.input_vertices = this->glyph_vertex_data;
                bool triangulating_result = ylikuutio::geometry::triangulate_polygons(
                        triangulate_polygons_struct,
                        this->vertices,
                        this->uvs,
                        this->normals);

                if (!triangulating_result)
                {
                    std::cerr << "triangulation failed!\n";
                }

                // Get a handle for our buffers.
                ontology::store_gl_attrib_locations(glyph_struct.shader_pointer, this);

                // TODO: triangulate the vertex data!

                // TODO: load the vertex data the same way as in `ontology::Species::Species(SpeciesStruct species_struct)`!

                this->type = "ontology::Glyph*";
            }

            void bind_to_parent();

            // this method renders all `Object`s of this `Glyph`.
            void render();

            ontology::VectorFont* parent;  // pointer to `VectorFont`.

            std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
            const char* glyph_name_pointer;        // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
            const char* unicode_char_pointer;      // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    };
}

#endif
