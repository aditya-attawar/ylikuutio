#ifndef __LINE3D_HPP_INCLUDED
#define __LINE3D_HPP_INCLUDED

#include "line.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace geometry
{
    class Line3D : public Line
    {
        public:
            // constructor.
            Line3D(std::vector<float> point1, std::vector<float> point2)
                : Line(point1, point2)
            {
            }

            // constructor.
            Line3D(std::vector<float> general_form_coefficients, float general_form_constant)
                : Line(general_form_coefficients, general_form_constant)
            {
            }

            bool do_lines3D_intersect(geometry::Line3D* line1, geometry::Line3D* line2);
            bool do_lines3D_intersect(geometry::Line3D* line);

        private:
            glm::vec3 vec3_point1;
            glm::vec3 vec3_point2;
    };
}

#endif
