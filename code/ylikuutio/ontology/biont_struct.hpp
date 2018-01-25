#ifndef __BIONT_STRUCT_HPP_INCLUDED
#define __BIONT_STRUCT_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ontology
{
    class Holobiont;
}

typedef struct BiontStruct
{
    BiontStruct()
        : holobiont_parent(nullptr),
        biontID(-1),
        original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
        rotate_angle(0.0f),
        initial_rotate_angle(PI),
        quaternions_in_use(false),
        cartesian_coordinates(nullptr),
        rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
        initial_rotate_vector(glm::vec3(0.0f, 1.0f, 1.0f)),
        translate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
        texture(0)
    {
        // constructor.
    }
    ontology::Holobiont* holobiont_parent; // pointer to the parent `Holobiont`.
    int32_t biontID;
    glm::vec3 original_scale_vector; // original scale vector.
    float rotate_angle;              // rotate angle.
    float initial_rotate_angle;      // initial rotate angle.
    bool quaternions_in_use;
    std::shared_ptr<glm::vec3> cartesian_coordinates; // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 initial_rotate_vector; // initial rotate vector.
    glm::vec3 translate_vector;      // translate vector.
    GLuint texture;
} BiontStruct;

#endif
