// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

TEST(ObjectStruct_must_be_initialized_appropriately, ObjectStruct)
{
    const ObjectStruct test_object_struct;
    ASSERT_EQ(test_object_struct.species_parent, nullptr);
    ASSERT_EQ(test_object_struct.text3D_parent, nullptr);
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_EQ(test_object_struct.rotate_angle, 0.0f);
    ASSERT_FALSE(test_object_struct.is_character);
    ASSERT_FALSE(test_object_struct.quaternions_in_use);
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.z));
    ASSERT_EQ(test_object_struct.rotate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(test_object_struct.translate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
}
