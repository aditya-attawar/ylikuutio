// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#include "globals.hpp"

glm::mat4 ProjectionMatrix;
glm::mat4 ViewMatrix;
glm::vec3 position;
GLfloat gravity = 9.81f / 60.0f;
bool is_flight_mode_in_use;
bool in_help_mode = true;
GLfloat fallSpeed = gravity;
SphericalCoordinatesStruct spherical_position;
double horizontalAngle;
double verticalAngle;
GLfloat initialFoV;
double earth_radius;

bool hasMouseEverMoved;
bool is_invert_mouse_in_use;
bool is_key_I_released;
bool is_key_F_released;
bool is_key_F1_released;
bool is_world_loaded; // no more than one world object can be loaded. TODO: check that no more than one world is loaded!
bool is_world_spherical;

GLfloat speed = 5.0f; // 5 units / second
#ifdef TESTING_SPHERICAL_WORLD_IN_USE
GLfloat turbo_factor = 100.0f;
GLfloat twin_turbo_factor = 50000.0f;
#else
GLfloat turbo_factor = 5.0f;
GLfloat twin_turbo_factor = 100.0f;
#endif
GLfloat mouseSpeed = 0.005f;

glm::vec3 camera_position;
