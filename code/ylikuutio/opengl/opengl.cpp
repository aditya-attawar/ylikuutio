#include "opengl.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace opengl
    {
        bool init_window()
        {
            if (!glfwInit())
            {
                std::cerr << "Failed to initialize GLFW.\n";
                return false;
            }

            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            return true;
        }

        GLFWwindow* create_window(const int window_width, const int window_height, const char* const title, GLFWmonitor* const monitor, GLFWwindow* const share)
        {
            return glfwCreateWindow(window_width, window_height, title, monitor, share);
        }

        void make_context_current(GLFWwindow* const window)
        {
            glfwMakeContextCurrent(window);
        }

        bool init_glew()
        {
            if (glewInit() != GLEW_OK)
            {
                std::cerr << "Failed to initialize GLEW.\n";
                return false;
            }
            return true;
        }

        void enable_depth_test()
        {
            // Enable depth test.
            glEnable(GL_DEPTH_TEST);
        }

        void disable_depth_test()
        {
            // Disable depth test.
            glDisable(GL_DEPTH_TEST);
        }

        void set_depth_func_to_less()
        {
            // Accept a fragment if it closer to the camera than the former one.
            glDepthFunc(GL_LESS);
        }

        void cull_triangles()
        {
            // Cull triangles whose normal is not towards the camera.
            glEnable(GL_CULL_FACE);
        }

        void set_background_color(const float red, const float green, const float blue, const float alpha)
        {
            glClearColor(
                    static_cast<GLclampf>(red),
                    static_cast<GLclampf>(green),
                    static_cast<GLclampf>(blue),
                    static_cast<GLclampf>(alpha));
        }

        void set_wireframe(const bool wireframe)
        {
            if (wireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
    }
}