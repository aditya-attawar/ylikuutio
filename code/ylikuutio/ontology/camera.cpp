#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#include "camera.hpp"
#include "scene.hpp"
#include "ground_level.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace ontology
{
    void Camera::bind_to_parent()
    {
        // get `childID` from `Scene` and set pointer to this `Camera`.
        this->parent->bind_camera(this);
    }

    Camera::~Camera()
    {
        // destructor.

        if (this->parent->get_active_camera() == this)
        {
            // Make this `Camera` no more the active `Camera`.
            this->parent->set_active_camera(nullptr);
        }

        // set pointer to this `Camera` to `nullptr`.
        this->parent->set_camera_pointer(this->childID, nullptr);
    }

    ontology::Entity* Camera::get_parent() const
    {
        return this->parent;
    }

    int32_t Camera::get_number_of_children() const
    {
        return 0;
    }

    int32_t Camera::get_number_of_descendants() const
    {
        return 0;
    }

    glm::mat4& Camera::get_projection_matrix()
    {
        return this->projection_matrix;
    }

    glm::mat4& Camera::get_view_matrix()
    {
        return this->view_matrix;
    }

    float Camera::get_horizontal_angle() const
    {
        return this->horizontal_angle;
    }

    float Camera::get_vertical_angle() const
    {
        return this->vertical_angle;
    }

    bool Camera::compute_matrices_from_inputs()
    {
        if (!this->universe->is_flight_mode_in_use)
        {
            this->universe->fall_speed += this->universe->gravity;
            this->cartesian_coordinates.y -= this->universe->fall_speed;
        }

        GLfloat FoV = this->universe->get_initialFoV();

        // adjust position according to the ground.
        if (!this->universe->is_flight_mode_in_use)
        {
            if (this->universe->get_terrain_species() != nullptr)
            {
                GLfloat ground_y = ontology::get_floor_level(
                        static_cast<ontology::Species*>(this->universe->get_terrain_species()),
                        this->cartesian_coordinates);

                if (!std::isnan(ground_y) && this->cartesian_coordinates.y < ground_y)
                {
                    this->cartesian_coordinates.y = ground_y;
                    this->universe->fall_speed = 0.0f;
                }
            }
        }

        if (this->universe->testing_spherical_terrain_in_use)
        {
            // compute spherical coordinates.
            this->spherical_coordinates.rho = sqrt(
                    (this->cartesian_coordinates.x * this->cartesian_coordinates.x) +
                    (this->cartesian_coordinates.y * this->cartesian_coordinates.y) +
                    (this->cartesian_coordinates.z * this->cartesian_coordinates.z));
            this->spherical_coordinates.theta = RADIANS_TO_DEGREES(atan2(sqrt(
                            (this->cartesian_coordinates.x * this->cartesian_coordinates.x) +
                            (this->cartesian_coordinates.y * this->cartesian_coordinates.y)),
                        this->cartesian_coordinates.z));
            this->spherical_coordinates.phi = RADIANS_TO_DEGREES(atan2(
                        this->cartesian_coordinates.y,
                        this->cartesian_coordinates.x));
        }

        glm::vec3 camera_cartesian_coordinates;
        camera_cartesian_coordinates.x = this->cartesian_coordinates.x;
        camera_cartesian_coordinates.y = this->cartesian_coordinates.y;
        camera_cartesian_coordinates.z = this->cartesian_coordinates.z;
        camera_cartesian_coordinates.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        this->projection_matrix = glm::perspective(
                DEGREES_TO_RADIANS(FoV),
                this->universe->get_aspect_ratio(),
                0.001f,
                5000.0f + 2.0f * static_cast<GLfloat>(this->universe->get_planet_radius()));
        // Camera matrix
        this->view_matrix = glm::lookAt(
                camera_cartesian_coordinates,                   // Camera is here
                camera_cartesian_coordinates + this->direction, // and looks here : at the same position, plus "direction"
                this->up                                        // Head is up (set to 0,-1,0 to look upside-down)
                );

        return true;
    }

    glm::vec3 Camera::get_direction() const
    {
        return this->direction;
    }

    glm::vec3 Camera::get_right() const
    {
        return this->right;
    }

    glm::vec3 Camera::get_up() const
    {
        return this->up;
    }
}
