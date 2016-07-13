#include "line_line_intersection.hpp"
#include "line2D.hpp"
#include "line3D.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include Eigen
#include <Eigen/Dense>

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

namespace geometry
{
    glm::vec2 get_intersection_point(geometry::Line2D line1, geometry::Line2D line2)
    {
        // See http://mathworld.wolfram.com/Line-LineIntersection.html

        Eigen::Matrix2f lower_matrix_for_solving_x_and_y;
        lower_matrix_for_solving_x_and_y <<
            line1.x1_minus_x2, line1.y1_minus_y2,  \
            line2.x1_minus_x2, line2.y1_minus_y2;
        float det_lower_matrix_for_solving_x_and_y = lower_matrix_for_solving_x_and_y.determinant();

        if (det_lower_matrix_for_solving_x_and_y == 0.0f)
        {
            // Lines are parallel, they do not intersect!
            return glm::vec2(NAN, NAN);
        }

        // Lines do intersect, so let's compute where!
        // TODO: Implement support for vertical lines!

        Eigen::Matrix2f upper_matrix_for_solving_x;
        upper_matrix_for_solving_x <<
            line1.determinant, line1.x1_minus_x2, \
            line2.determinant, line2.x1_minus_x2;
        float det_upper_matrix_for_solving_x = upper_matrix_for_solving_x.determinant();

        Eigen::Matrix2f upper_matrix_for_solving_y;
        upper_matrix_for_solving_y <<
            line1.determinant, line1.y1_minus_y2, \
            line2.determinant, line2.y1_minus_y2;
        float det_upper_matrix_for_solving_y = upper_matrix_for_solving_y.determinant();

        // Compute x and y coordinates.
        float x = det_upper_matrix_for_solving_x / det_lower_matrix_for_solving_x_and_y;
        float y = det_upper_matrix_for_solving_y / det_lower_matrix_for_solving_x_and_y;
        return glm::vec2(x, y);
    }

    glm::vec3 get_intersection_point(geometry::Line3D line1, geometry::Line3D line2)
    {
        // TODO: implement this function!
        glm::vec3 intersection_point;
        return intersection_point;
    }
}
