#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

// GCC (at least g++ 4.7.2) and Visual Studio 2015 do support
// setting default values of a struct using C++11 syntax.
// Clang 3.7.0 and Visual Studio 2013 do not support
// setting default values of a struct using C++11 syntax.
// Visual Studio 2013 fails to compile, whereas Clang-compiled
// executable with code with setting default values of a struct
// causes Segmentation fault upon execution of the program.
// Compilers that don't support setting default values of a struct
// are handled by setting the default values in a macro.
// http://stackoverflow.com/questions/16782103/initializing-default-values-in-a-struct/16783513#16783513
#ifdef __clang__
#elif defined(__GNUC__)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#elif defined(_WIN32)
#if (_MSC_VER >= 1900)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#endif
#endif

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector
#include <stdint.h> // uint32_t etc.

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH (1600.0f)
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT (900.0f)
#endif

#ifndef ASPECT_RATIO
#define ASPECT_RATIO (WINDOW_WIDTH / WINDOW_HEIGHT)
#endif

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef EARTH_RADIUS
#define EARTH_RADIUS 6371000.0f
#endif

#ifndef TEXT_SIZE
#define TEXT_SIZE 40
#endif

#ifndef FONT_SIZE
#define FONT_SIZE 16
#endif

#ifndef MAX_FPS
#define MAX_FPS 60
#endif

extern glm::mat4 ProjectionMatrix;
extern glm::mat4 ViewMatrix;
extern glm::vec3 position;
extern GLfloat gravity;
extern bool is_flight_mode_in_use;
extern bool in_help_mode;
extern GLfloat fallSpeed;
extern double horizontalAngle;
extern double verticalAngle;
extern GLfloat initialFoV;
extern double earth_radius;
extern bool hasMouseEverMoved;
extern bool is_invert_mouse_in_use;
extern bool is_key_I_released;
extern bool is_key_F_released;
extern bool is_key_F1_released;
extern bool is_world_loaded;        // no more than one world object can be loaded. TODO: check that no more than one world is loaded!
extern bool is_world_spherical;

extern GLfloat speed;
extern GLfloat turbo_factor;
extern GLfloat twin_turbo_factor;
extern GLfloat mouseSpeed;

extern glm::vec3 camera_position;

namespace model
{
    class World;
    class Shader;
    class Graph;
    class Material;
    class Font;
    class Species;
    class Glyph;
}

typedef struct
{
    model::World* parent_pointer; // pointer to the world (draw list).
    std::string vertex_shader;    // filename of vertex shader.
    std::string fragment_shader;  // filename of fragment shader.
} ShaderStruct;

#define SHADERSTRUCT(x) ShaderStruct x; x.parent_pointer = NULL

typedef struct
{
    model::Shader* parent_pointer;   // pointer to the shader.
    std::string texture_file_format; // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;    // filename of the model file.
    std::string image_path;
} MaterialStruct;

#define MATERIALSTRUCT(x) MaterialStruct x; x.parent_pointer = NULL

typedef struct
{
    GLuint nodeID;
    model::Graph* parent_pointer;
    glm::vec3 coordinate_vector;
    std::vector<uint32_t> neighbor_nodeIDs;
} NodeStruct;

#define NODESTRUCT(x) NodeStruct x; x.parent_pointer = NULL

typedef struct
{
    model::Species* species_parent_pointer; // pointer to the parent species.
    model::Glyph* glyph_parent_pointer;     // pointer to the parent glyph.
    glm::vec3 original_scale_vector; // original scale vector.
    GLfloat rotate_angle;            // rotate angle.
    bool is_character;               // The parent of a character object is a Glyph. The parent of a regular object is a Species.
    glm::vec3 coordinate_vector;     // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 translate_vector;      // translate vector.
} ObjectStruct;

#define OBJECTSTRUCT(x) ObjectStruct x; \
x.species_parent_pointer = NULL; \
x.glyph_parent_pointer = NULL; \
x.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f); \
x.rotate_angle = NAN; \
x.is_character = false

typedef struct
{
    // used for all files (for all species).
    model::Material* parent_pointer;         // pointer to the material object.
    bool is_world;                           // worlds currently do not rotate nor translate.
    double world_radius;                     // radius of sea level in meters. used only for worlds.
    std::string model_file_format;           // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
                                             // TODO: add support for `"SRTM"`.
    std::string model_filename;              // filename of the model file.
    // for `"bmp"` model files.
    std::string color_channel;               // color channel to use for altitude data.

    glm::vec3 light_position;                // light position.
    std::string coordinate_system;           // used only for worlds (`is_world` == `true`). valid values: `"cartesian"`.
                                             // TODO: add support for `"spherical"`. `"spherical"` is used eg. in SRTM heightmaps.
    std::string triangulation_type;
} SpeciesStruct;

#define SPECIESSTRUCT(x) SpeciesStruct x; x.parent_pointer = NULL; x.is_world = false; x.world_radius = NAN; x.triangulation_type = "bilinear_interpolation"

#define DEFAULT_VERTEX_SCALING_FACTOR (0.001f)

typedef struct
{
    // used for all files (for all font).
    model::Material* parent_pointer;        // pointer to the material object.
    GLfloat vertex_scaling_factor;
    std::string font_file_format;           // type of the font file. supported file formats so far: `"svg"`/`"SVG"`.
    std::string font_filename;              // filename of the font file.
} FontStruct;

#define FONTSTRUCT(x) FontStruct x; x.parent_pointer = NULL; x.vertex_scaling_factor = DEFAULT_VERTEX_SCALING_FACTOR

typedef struct
{
    // used for all files (for all glyph).
    model::Font* parent_pointer;             // pointer to the font object.
    glm::vec3 light_position;                // light position.
} GlyphStruct;

#define GLYPHSTRUCT(x) GlyphStruct x; x.parent_pointer = NULL

typedef struct
{
    GLuint screen_width;
    GLuint screen_height;
    GLuint x;
    GLuint y;
    GLuint text_size;
    GLuint font_size;
    const char* text;
    const char* char_font_texture_file_format;
    const char* horizontal_alignment;
    const char* vertical_alignment;
} PrintingStruct;

typedef struct
{
    double rho;
    double theta;
    double phi;
} SphericalCoordinatesStruct;

typedef struct
{
    double southern_latitude;
    double northern_latitude;
    double western_longitude;
    double eastern_longitude;
} SphericalWorldStruct;

typedef struct
{
    GLuint* input_vertex_pointer;
    uint32_t image_width;
    uint32_t image_height;
    std::string triangulation_type;
    double sphere_radius;
    SphericalWorldStruct spherical_world_struct;
} TriangulateQuadsStruct;

extern SphericalCoordinatesStruct spherical_position;

#endif
