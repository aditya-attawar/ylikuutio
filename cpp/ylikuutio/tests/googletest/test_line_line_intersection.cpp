#include "gtest/gtest.h"
#include "cpp/ylikuutio/geometry/line_line_intersection.hpp"
#include "cpp/ylikuutio/geometry/line2D.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

TEST(line2D_line2D_intersection, parallel_lines)
{
    // ^............ a1 = point 1 of line a at (2, 2).
    // |.....b1..... a2 = point 2 of line a at (11, 5).
    // |..b2.....a2.
    // |*......*.... b1 = point 1 of line b at (7, 6).
    // |....*....... b2 = point 2 of line b at (4, 5).
    // |a1..........
    // |............
    // +----------->
    geometry::Line2D line_a = geometry::Line2D(glm::vec2(2.0f, 2.0f), glm::vec2(11.0f, 5.0f));
    geometry::Line2D line_b = geometry::Line2D(glm::vec2(7.0f, 6.0f), glm::vec2(4.0f, 5.0f));

    glm::vec2 intersection_point_a_a = geometry::get_intersection_point(&line_a, &line_a);
    ASSERT_TRUE(std::isnan(intersection_point_a_a.x));
    ASSERT_TRUE(std::isnan(intersection_point_a_a.y));

    glm::vec2 intersection_point_a_b = geometry::get_intersection_point(&line_a, &line_b);
    ASSERT_TRUE(std::isnan(intersection_point_a_b.x));
    ASSERT_TRUE(std::isnan(intersection_point_a_b.y));

    glm::vec2 intersection_point_b_a = geometry::get_intersection_point(&line_b, &line_a);
    ASSERT_TRUE(std::isnan(intersection_point_b_a.x));
    ASSERT_TRUE(std::isnan(intersection_point_b_a.y));

    glm::vec2 intersection_point_b_b = geometry::get_intersection_point(&line_b, &line_b);
    ASSERT_TRUE(std::isnan(intersection_point_b_b.x));
    ASSERT_TRUE(std::isnan(intersection_point_b_b.y));

    // Line c is same as but point order is changed.
    geometry::Line2D line_c = geometry::Line2D(glm::vec2(11.0f, 5.0f), glm::vec2(2.0f, 2.0f));

    glm::vec2 intersection_point_a_c = geometry::get_intersection_point(&line_a, &line_c);
    ASSERT_TRUE(std::isnan(intersection_point_a_c.x));
    ASSERT_TRUE(std::isnan(intersection_point_a_c.y));

    glm::vec2 intersection_point_b_c = geometry::get_intersection_point(&line_b, &line_c);
    ASSERT_TRUE(std::isnan(intersection_point_b_c.x));
    ASSERT_TRUE(std::isnan(intersection_point_b_c.y));

    glm::vec2 intersection_point_c_c = geometry::get_intersection_point(&line_c, &line_c);
    ASSERT_TRUE(std::isnan(intersection_point_c_c.x));
    ASSERT_TRUE(std::isnan(intersection_point_c_c.y));

    glm::vec2 intersection_point_c_a = geometry::get_intersection_point(&line_c, &line_a);
    ASSERT_TRUE(std::isnan(intersection_point_c_a.x));
    ASSERT_TRUE(std::isnan(intersection_point_c_a.y));

    glm::vec2 intersection_point_c_b = geometry::get_intersection_point(&line_c, &line_b);
    ASSERT_TRUE(std::isnan(intersection_point_c_b.x));
    ASSERT_TRUE(std::isnan(intersection_point_c_b.y));
}

TEST(line2D_line2D_intersection, intersecting_lines)
{
    // ^..........*. a1 = point 1 of line a at (5, 1).
    // |*.......a2.. a2 = point 2 of line a at (10, 6).
    // |.b1.....*...
    // |....*..*.... b1 = point 1 of line b at (3, 5).
    // |......x..... b2 = point 2 of line b at (9, 2).
    // |.....*.b2...
    // |...a1.....*. x = intersection point at (7, 3).
    // +----------->
    geometry::Line2D line_a = geometry::Line2D(glm::vec2(5.0f, 1.0f), glm::vec2(10.0f, 6.0f));
    ASSERT_EQ(line_a.determinant, 20.0f);
    ASSERT_EQ(line_a.x1_minus_x2, -5.0f);
    ASSERT_EQ(line_a.y1_minus_y2, -5.0f);

    geometry::Line2D line_b = geometry::Line2D(glm::vec2(3.0f, 5.0f), glm::vec2(9.0f, 2.0f));
    ASSERT_EQ(line_b.determinant, -39.0f);
    ASSERT_EQ(line_b.x1_minus_x2, -6.0f);
    ASSERT_EQ(line_b.y1_minus_y2, 3.0f);

    glm::vec2 intersection_point = geometry::get_intersection_point(&line_a, &line_b);
    ASSERT_EQ(intersection_point.x, 7.0f);
    ASSERT_EQ(intersection_point.y, 3.0f);
}
