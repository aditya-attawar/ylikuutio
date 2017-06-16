#include "gtest/gtest.h"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.

TEST(any_value_must_be_initialized_appropriately, no_value)
{
    datatypes::AnyValue no_value = datatypes::AnyValue();
    ASSERT_EQ(no_value.type, datatypes::UNKNOWN);
    ASSERT_FALSE(no_value.bool_value);
    ASSERT_TRUE(std::isnan(no_value.float_value));
    ASSERT_TRUE(std::isnan(no_value.double_value));
    ASSERT_EQ(no_value.int32_t_value, 0);
    ASSERT_EQ(no_value.uint32_t_value, 0);
    ASSERT_EQ(no_value.bool_pointer, nullptr);
    ASSERT_EQ(no_value.float_pointer, nullptr);
    ASSERT_EQ(no_value.double_pointer, nullptr);
    ASSERT_EQ(no_value.int32_t_pointer, nullptr);
    ASSERT_EQ(no_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(no_value.universe_pointer, nullptr);
    ASSERT_EQ(no_value.scene_pointer, nullptr);
    ASSERT_EQ(no_value.shader_pointer, nullptr);
    ASSERT_EQ(no_value.material_pointer, nullptr);
    ASSERT_EQ(no_value.species_pointer, nullptr);
    ASSERT_EQ(no_value.object_pointer, nullptr);
    ASSERT_EQ(no_value.vector_font_pointer, nullptr);
    ASSERT_EQ(no_value.glyph_pointer, nullptr);
    ASSERT_EQ(no_value.text3D_pointer, nullptr);
    ASSERT_EQ(no_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(no_value.font2D_pointer, nullptr);
    ASSERT_EQ(no_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(no_value.get_datatype().c_str()), strlen("unknown"));
    ASSERT_EQ(std::strcmp(no_value.get_datatype().c_str(), "unknown"), 0);
    ASSERT_EQ(std::strlen(no_value.get_string().c_str()), strlen("unknown"));
    ASSERT_EQ(std::strcmp(no_value.get_string().c_str(), "unknown"), 0);
}
TEST(any_value_must_be_initialized_appropriately, bool_true)
{
    bool bool_true = true;
    datatypes::AnyValue true_value = datatypes::AnyValue(bool_true);
    ASSERT_EQ(true_value.type, datatypes::BOOL);
    ASSERT_TRUE(true_value.bool_value);
    ASSERT_TRUE(std::isnan(true_value.float_value));
    ASSERT_TRUE(std::isnan(true_value.double_value));
    ASSERT_EQ(true_value.int32_t_value, 0);
    ASSERT_EQ(true_value.uint32_t_value, 0);
    ASSERT_EQ(true_value.bool_pointer, nullptr);
    ASSERT_EQ(true_value.float_pointer, nullptr);
    ASSERT_EQ(true_value.double_pointer, nullptr);
    ASSERT_EQ(true_value.int32_t_pointer, nullptr);
    ASSERT_EQ(true_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(true_value.universe_pointer, nullptr);
    ASSERT_EQ(true_value.scene_pointer, nullptr);
    ASSERT_EQ(true_value.shader_pointer, nullptr);
    ASSERT_EQ(true_value.material_pointer, nullptr);
    ASSERT_EQ(true_value.species_pointer, nullptr);
    ASSERT_EQ(true_value.object_pointer, nullptr);
    ASSERT_EQ(true_value.vector_font_pointer, nullptr);
    ASSERT_EQ(true_value.glyph_pointer, nullptr);
    ASSERT_EQ(true_value.text3D_pointer, nullptr);
    ASSERT_EQ(true_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(true_value.font2D_pointer, nullptr);
    ASSERT_EQ(true_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(true_value.get_datatype().c_str()), strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(true_value.get_string().c_str()), strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_string().c_str(), "true"), 0);
}
TEST(any_value_must_be_initialized_appropriately, bool_false)
{
    bool bool_false = false;
    datatypes::AnyValue false_value = datatypes::AnyValue(bool_false);
    ASSERT_EQ(false_value.type, datatypes::BOOL);
    ASSERT_FALSE(false_value.bool_value);
    ASSERT_TRUE(std::isnan(false_value.float_value));
    ASSERT_TRUE(std::isnan(false_value.double_value));
    ASSERT_EQ(false_value.int32_t_value, 0);
    ASSERT_EQ(false_value.uint32_t_value, 0);
    ASSERT_EQ(false_value.bool_pointer, nullptr);
    ASSERT_EQ(false_value.float_pointer, nullptr);
    ASSERT_EQ(false_value.double_pointer, nullptr);
    ASSERT_EQ(false_value.int32_t_pointer, nullptr);
    ASSERT_EQ(false_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(false_value.universe_pointer, nullptr);
    ASSERT_EQ(false_value.scene_pointer, nullptr);
    ASSERT_EQ(false_value.shader_pointer, nullptr);
    ASSERT_EQ(false_value.material_pointer, nullptr);
    ASSERT_EQ(false_value.species_pointer, nullptr);
    ASSERT_EQ(false_value.object_pointer, nullptr);
    ASSERT_EQ(false_value.vector_font_pointer, nullptr);
    ASSERT_EQ(false_value.glyph_pointer, nullptr);
    ASSERT_EQ(false_value.text3D_pointer, nullptr);
    ASSERT_EQ(false_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(false_value.font2D_pointer, nullptr);
    ASSERT_EQ(false_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(false_value.get_datatype().c_str()), strlen("bool"));
    ASSERT_EQ(std::strcmp(false_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(false_value.get_string().c_str()), strlen("false"));
    ASSERT_EQ(std::strcmp(false_value.get_string().c_str(), "false"), 0);
}
TEST(any_value_must_be_initialized_appropriately, float_0)
{
    float float_zero = 0.0f;
    datatypes::AnyValue float_zero_value = datatypes::AnyValue(float_zero);
    ASSERT_EQ(float_zero_value.type, datatypes::FLOAT);
    ASSERT_FALSE(float_zero_value.bool_value);
    ASSERT_EQ(float_zero_value.float_value, 0.0f);
    ASSERT_TRUE(std::isnan(float_zero_value.double_value));
    ASSERT_EQ(float_zero_value.int32_t_value, 0);
    ASSERT_EQ(float_zero_value.uint32_t_value, 0);
    ASSERT_EQ(float_zero_value.bool_pointer, nullptr);
    ASSERT_EQ(float_zero_value.float_pointer, nullptr);
    ASSERT_EQ(float_zero_value.double_pointer, nullptr);
    ASSERT_EQ(float_zero_value.int32_t_pointer, nullptr);
    ASSERT_EQ(float_zero_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(float_zero_value.universe_pointer, nullptr);
    ASSERT_EQ(float_zero_value.scene_pointer, nullptr);
    ASSERT_EQ(float_zero_value.shader_pointer, nullptr);
    ASSERT_EQ(float_zero_value.material_pointer, nullptr);
    ASSERT_EQ(float_zero_value.species_pointer, nullptr);
    ASSERT_EQ(float_zero_value.object_pointer, nullptr);
    ASSERT_EQ(float_zero_value.vector_font_pointer, nullptr);
    ASSERT_EQ(float_zero_value.glyph_pointer, nullptr);
    ASSERT_EQ(float_zero_value.text3D_pointer, nullptr);
    ASSERT_EQ(float_zero_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(float_zero_value.font2D_pointer, nullptr);
    ASSERT_EQ(float_zero_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(float_zero_value.get_datatype().c_str()), strlen("float"));
    ASSERT_EQ(std::strcmp(float_zero_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), strlen("0.000000"));
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(float_zero_value.get_string().c_str(), "0.000000"), 0);
}
TEST(any_value_must_be_initialized_appropriately, float_NAN)
{
    float float_NAN = NAN;
    datatypes::AnyValue float_NAN_value = datatypes::AnyValue(float_NAN);
    ASSERT_EQ(float_NAN_value.type, datatypes::FLOAT);
    ASSERT_FALSE(float_NAN_value.bool_value);
    ASSERT_TRUE(std::isnan(float_NAN_value.float_value));
    ASSERT_TRUE(std::isnan(float_NAN_value.double_value));
    ASSERT_EQ(float_NAN_value.int32_t_value, 0);
    ASSERT_EQ(float_NAN_value.uint32_t_value, 0);
    ASSERT_EQ(float_NAN_value.bool_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.float_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.double_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.int32_t_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.universe_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.scene_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.shader_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.material_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.species_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.object_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.vector_font_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.glyph_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.text3D_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.font2D_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(float_NAN_value.get_datatype().c_str()), strlen("float"));
    ASSERT_EQ(std::strcmp(float_NAN_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_NAN_value.get_string().c_str()), strlen("nan"));
    ASSERT_EQ(std::strcmp(float_NAN_value.get_string().c_str(), "nan"), 0);
}
TEST(any_value_must_be_initialized_appropriately, double_0)
{
    double double_zero = 0.0f;
    datatypes::AnyValue double_zero_value = datatypes::AnyValue(double_zero);
    ASSERT_EQ(double_zero_value.type, datatypes::DOUBLE);
    ASSERT_FALSE(double_zero_value.bool_value);
    ASSERT_TRUE(std::isnan(double_zero_value.float_value));
    ASSERT_EQ(double_zero_value.double_value, 0.0f);
    ASSERT_EQ(double_zero_value.int32_t_value, 0);
    ASSERT_EQ(double_zero_value.uint32_t_value, 0);
    ASSERT_EQ(double_zero_value.bool_pointer, nullptr);
    ASSERT_EQ(double_zero_value.float_pointer, nullptr);
    ASSERT_EQ(double_zero_value.double_pointer, nullptr);
    ASSERT_EQ(double_zero_value.int32_t_pointer, nullptr);
    ASSERT_EQ(double_zero_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(double_zero_value.universe_pointer, nullptr);
    ASSERT_EQ(double_zero_value.scene_pointer, nullptr);
    ASSERT_EQ(double_zero_value.shader_pointer, nullptr);
    ASSERT_EQ(double_zero_value.material_pointer, nullptr);
    ASSERT_EQ(double_zero_value.species_pointer, nullptr);
    ASSERT_EQ(double_zero_value.object_pointer, nullptr);
    ASSERT_EQ(double_zero_value.vector_font_pointer, nullptr);
    ASSERT_EQ(double_zero_value.glyph_pointer, nullptr);
    ASSERT_EQ(double_zero_value.text3D_pointer, nullptr);
    ASSERT_EQ(double_zero_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(double_zero_value.font2D_pointer, nullptr);
    ASSERT_EQ(double_zero_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(double_zero_value.get_datatype().c_str()), strlen("double"));
    ASSERT_EQ(std::strcmp(double_zero_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), strlen("0.000000"));
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(double_zero_value.get_string().c_str(), "0.000000"), 0);
}
TEST(any_value_must_be_initialized_appropriately, double_NAN)
{
    double double_NAN = NAN;
    datatypes::AnyValue double_NAN_value = datatypes::AnyValue(double_NAN);
    ASSERT_EQ(double_NAN_value.type, datatypes::DOUBLE);
    ASSERT_FALSE(double_NAN_value.bool_value);
    ASSERT_TRUE(std::isnan(double_NAN_value.float_value));
    ASSERT_TRUE(std::isnan(double_NAN_value.double_value));
    ASSERT_EQ(double_NAN_value.int32_t_value, 0);
    ASSERT_EQ(double_NAN_value.uint32_t_value, 0);
    ASSERT_EQ(double_NAN_value.bool_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.float_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.double_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.int32_t_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.universe_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.scene_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.shader_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.material_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.species_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.object_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.vector_font_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.glyph_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.text3D_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.font2D_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(double_NAN_value.get_datatype().c_str()), strlen("double"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_NAN_value.get_string().c_str()), strlen("nan"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_string().c_str(), "nan"), 0);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_zero)
{
    int32_t int32_t_zero = 0;
    datatypes::AnyValue int32_t_zero_value = datatypes::AnyValue(int32_t_zero);
    ASSERT_EQ(int32_t_zero_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_zero_value.bool_value);
    ASSERT_TRUE(std::isnan(int32_t_zero_value.float_value));
    ASSERT_TRUE(std::isnan(int32_t_zero_value.double_value));
    ASSERT_EQ(int32_t_zero_value.int32_t_value, 0);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_zero_value.int32_t_value), 0);
    ASSERT_EQ(int32_t_zero_value.uint32_t_value, 0);
    ASSERT_EQ(int32_t_zero_value.bool_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.float_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.double_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.universe_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.scene_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.shader_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.material_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.species_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.object_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.vector_font_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.glyph_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.text3D_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.font2D_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_datatype().c_str()), strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_string().c_str()), strlen("0"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_string().c_str(), "0"), 0);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    datatypes::AnyValue int32_t_plus_1_value = datatypes::AnyValue(int32_t_plus_1);
    ASSERT_EQ(int32_t_plus_1_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_plus_1_value.bool_value);
    ASSERT_TRUE(std::isnan(int32_t_plus_1_value.float_value));
    ASSERT_TRUE(std::isnan(int32_t_plus_1_value.double_value));
    ASSERT_EQ(int32_t_plus_1_value.int32_t_value, 1);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_plus_1_value.int32_t_value), 1);
    ASSERT_EQ(int32_t_plus_1_value.uint32_t_value, 0);
    ASSERT_EQ(int32_t_plus_1_value.bool_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.float_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.double_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.universe_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.scene_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.shader_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.material_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.species_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.object_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.vector_font_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.glyph_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.text3D_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.font2D_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_datatype().c_str()), strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_string().c_str()), strlen("1"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_string().c_str(), "1"), 0);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    datatypes::AnyValue int32_t_minus_1_value = datatypes::AnyValue(int32_t_minus_1);
    ASSERT_EQ(int32_t_minus_1_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_minus_1_value.bool_value);
    ASSERT_TRUE(std::isnan(int32_t_minus_1_value.float_value));
    ASSERT_TRUE(std::isnan(int32_t_minus_1_value.double_value));
    ASSERT_EQ(int32_t_minus_1_value.int32_t_value, -1);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_minus_1_value.int32_t_value), 4294967295);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_minus_1_value.int32_t_value), 0xffffffff);
    ASSERT_EQ(int32_t_minus_1_value.uint32_t_value, 0);
    ASSERT_EQ(int32_t_minus_1_value.bool_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.float_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.double_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.universe_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.scene_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.shader_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.material_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.species_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.object_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.vector_font_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.glyph_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.text3D_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.font2D_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_datatype().c_str()), strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_string().c_str()), strlen("-1"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_string().c_str(), "-1"), 0);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_max)
{
    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    datatypes::AnyValue int32_t_max_value = datatypes::AnyValue(int32_t_max);
    ASSERT_EQ(int32_t_max_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_max_value.bool_value);
    ASSERT_TRUE(std::isnan(int32_t_max_value.float_value));
    ASSERT_TRUE(std::isnan(int32_t_max_value.double_value));
    ASSERT_EQ(int32_t_max_value.int32_t_value, 2147483647);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_max_value.int32_t_value), 2147483647);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_max_value.int32_t_value), 0x7fffffff);
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int32_t>::max());
    ASSERT_EQ(int32_t_max_value.uint32_t_value, 0);
#ifdef __linux__
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int>::max());
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<long>::max());
#endif
    ASSERT_EQ(int32_t_max_value.bool_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.float_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.double_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.universe_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.scene_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.shader_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.material_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.species_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.object_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.vector_font_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.glyph_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.text3D_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.font2D_pointer, nullptr);
    ASSERT_EQ(int32_t_max_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(int32_t_max_value.get_datatype().c_str()), strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_max_value.get_string().c_str()), strlen("2147483647"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_string().c_str(), "2147483647"), 0);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_min)
{
    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    datatypes::AnyValue int32_t_min_value = datatypes::AnyValue(int32_t_min);
    ASSERT_EQ(int32_t_min_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_min_value.bool_value);
    ASSERT_TRUE(std::isnan(int32_t_min_value.float_value));
    ASSERT_TRUE(std::isnan(int32_t_min_value.double_value));
    ASSERT_EQ(int32_t_min_value.int32_t_value, -2147483648);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_min_value.int32_t_value), 2147483648);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_min_value.int32_t_value), 0x80000000);
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int32_t>::min());
    ASSERT_EQ(int32_t_min_value.uint32_t_value, 0);
#ifdef __linux__
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int>::min());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int>::min());
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<long>::min());
#endif
    ASSERT_EQ(int32_t_min_value.bool_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.float_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.double_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.int32_t_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.universe_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.scene_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.shader_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.material_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.species_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.object_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.vector_font_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.glyph_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.text3D_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.font2D_pointer, nullptr);
    ASSERT_EQ(int32_t_min_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(int32_t_min_value.get_datatype().c_str()), strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_min_value.get_string().c_str()), strlen("-2147483648"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_string().c_str(), "-2147483648"), 0);
}
TEST(any_value_must_be_initialized_appropriately, uint32_t_zero)
{
    uint32_t uint32_t_zero = 0;
    datatypes::AnyValue uint32_t_zero_value = datatypes::AnyValue(uint32_t_zero);
    ASSERT_EQ(uint32_t_zero_value.type, datatypes::UINT32_T);
    ASSERT_FALSE(uint32_t_zero_value.bool_value);
    ASSERT_TRUE(std::isnan(uint32_t_zero_value.float_value));
    ASSERT_TRUE(std::isnan(uint32_t_zero_value.double_value));
    ASSERT_EQ(uint32_t_zero_value.int32_t_value, 0);
    ASSERT_EQ(uint32_t_zero_value.uint32_t_value, 0);
    ASSERT_EQ(uint32_t_zero_value.bool_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.float_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.double_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.int32_t_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.universe_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.scene_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.shader_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.material_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.species_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.object_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.vector_font_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.glyph_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.text3D_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.font2D_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_datatype().c_str()), strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_string().c_str()), strlen("0"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_string().c_str(), "0"), 0);
}
TEST(any_value_must_be_initialized_appropriately, uint32_t_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    datatypes::AnyValue uint32_t_plus_1_value = datatypes::AnyValue(uint32_t_plus_1);
    ASSERT_EQ(uint32_t_plus_1_value.type, datatypes::UINT32_T);
    ASSERT_FALSE(uint32_t_plus_1_value.bool_value);
    ASSERT_TRUE(std::isnan(uint32_t_plus_1_value.float_value));
    ASSERT_TRUE(std::isnan(uint32_t_plus_1_value.double_value));
    ASSERT_EQ(uint32_t_plus_1_value.int32_t_value, 0);
    ASSERT_EQ(uint32_t_plus_1_value.uint32_t_value, 1);
    ASSERT_EQ(uint32_t_plus_1_value.bool_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.float_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.double_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.int32_t_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.universe_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.scene_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.shader_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.material_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.species_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.object_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.vector_font_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.glyph_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.text3D_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.font2D_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_datatype().c_str()), strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_string().c_str()), strlen("1"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_string().c_str(), "1"), 0);
}
TEST(any_value_must_be_initialized_appropriately, uint32_t_max)
{
    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    datatypes::AnyValue uint32_t_max_value = datatypes::AnyValue(uint32_t_max);
    ASSERT_EQ(uint32_t_max_value.type, datatypes::UINT32_T);
    ASSERT_FALSE(uint32_t_max_value.bool_value);
    ASSERT_TRUE(std::isnan(uint32_t_max_value.float_value));
    ASSERT_TRUE(std::isnan(uint32_t_max_value.double_value));
    ASSERT_EQ(uint32_t_max_value.int32_t_value, 0);
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, 4294967295);
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, 0xffffffff);
    ASSERT_EQ(static_cast<int32_t>(uint32_t_max_value.uint32_t_value), -1);
#ifdef __linux__
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<unsigned int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<unsigned int>::max());
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<unsigned long>::max());
#endif
    ASSERT_EQ(uint32_t_max_value.bool_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.float_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.double_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.int32_t_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.universe_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.scene_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.shader_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.material_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.species_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.object_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.vector_font_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.glyph_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.text3D_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.font2D_pointer, nullptr);
    ASSERT_EQ(uint32_t_max_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_datatype().c_str()), strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_string().c_str()), strlen("4294967295"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_string().c_str(), "4294967295"), 0);
}
TEST(any_value_must_be_initialized_appropriately, universe)
{
    ontology::Universe* universe = static_cast<ontology::Universe*>((void*) 0xdeadbeef);
    datatypes::AnyValue universe_pointer_any_value = datatypes::AnyValue(universe);
    ASSERT_EQ(universe_pointer_any_value.type, datatypes::UNIVERSE_POINTER);
    ASSERT_FALSE(universe_pointer_any_value.bool_value);
    ASSERT_TRUE(std::isnan(universe_pointer_any_value.float_value));
    ASSERT_TRUE(std::isnan(universe_pointer_any_value.double_value));
    ASSERT_EQ(universe_pointer_any_value.int32_t_value, 0);
    ASSERT_EQ(universe_pointer_any_value.uint32_t_value, 0);
    ASSERT_EQ(universe_pointer_any_value.bool_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.float_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.double_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.int32_t_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.universe_pointer, universe);
    ASSERT_EQ(universe_pointer_any_value.scene_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.shader_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.material_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.species_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.object_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.vector_font_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.glyph_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.text3D_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.font2D_pointer, nullptr);
    ASSERT_EQ(universe_pointer_any_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(universe_pointer_any_value.get_datatype().c_str()), strlen("ontology::Universe*"));
    ASSERT_EQ(std::strcmp(universe_pointer_any_value.get_datatype().c_str(), "ontology::Universe*"), 0);
    ASSERT_EQ(std::strlen(universe_pointer_any_value.get_string().c_str()), strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(universe_pointer_any_value.get_string().c_str(), "deadbeef"), 0);
}
TEST(any_value_must_be_initialized_appropriately, scene)
{
    ontology::Scene* scene = static_cast<ontology::Scene*>((void*) 0xbad5ce6e);
    datatypes::AnyValue scene_pointer_any_value = datatypes::AnyValue(scene);
    ASSERT_EQ(scene_pointer_any_value.type, datatypes::SCENE_POINTER);
    ASSERT_FALSE(scene_pointer_any_value.bool_value);
    ASSERT_TRUE(std::isnan(scene_pointer_any_value.float_value));
    ASSERT_TRUE(std::isnan(scene_pointer_any_value.double_value));
    ASSERT_EQ(scene_pointer_any_value.int32_t_value, 0);
    ASSERT_EQ(scene_pointer_any_value.uint32_t_value, 0);
    ASSERT_EQ(scene_pointer_any_value.bool_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.float_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.double_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.int32_t_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.universe_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.scene_pointer, scene);
    ASSERT_EQ(scene_pointer_any_value.shader_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.material_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.species_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.object_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.vector_font_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.glyph_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.text3D_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.font2D_pointer, nullptr);
    ASSERT_EQ(scene_pointer_any_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_datatype().c_str()), strlen("ontology::Scene*"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_datatype().c_str(), "ontology::Scene*"), 0);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_string().c_str()), strlen("bad5ce6e"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_string().c_str(), "bad5ce6e"), 0);
}
TEST(any_value_must_be_initialized_appropriately, shader)
{
    ontology::Shader* shader = static_cast<ontology::Shader*>((void*) 0xbad5bade7);
    datatypes::AnyValue shader_pointer_any_value = datatypes::AnyValue(shader);
    ASSERT_EQ(shader_pointer_any_value.type, datatypes::SHADER_POINTER);
    ASSERT_FALSE(shader_pointer_any_value.bool_value);
    ASSERT_TRUE(std::isnan(shader_pointer_any_value.float_value));
    ASSERT_TRUE(std::isnan(shader_pointer_any_value.double_value));
    ASSERT_EQ(shader_pointer_any_value.int32_t_value, 0);
    ASSERT_EQ(shader_pointer_any_value.uint32_t_value, 0);
    ASSERT_EQ(shader_pointer_any_value.bool_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.float_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.double_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.int32_t_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.universe_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.scene_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.shader_pointer, shader);
    ASSERT_EQ(shader_pointer_any_value.material_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.species_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.object_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.vector_font_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.glyph_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.text3D_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.font2D_pointer, nullptr);
    ASSERT_EQ(shader_pointer_any_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_datatype().c_str()), strlen("ontology::Shader*"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_datatype().c_str(), "ontology::Shader*"), 0);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_string().c_str()), strlen("bad5bade7"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_string().c_str(), "bad5bade7"), 0);
}
TEST(any_value_must_be_initialized_appropriately, material)
{
    ontology::Material* material = static_cast<ontology::Material*>((void*) 0xbad6a7e71a1);
    datatypes::AnyValue material_pointer_any_value = datatypes::AnyValue(material);
    ASSERT_EQ(material_pointer_any_value.type, datatypes::MATERIAL_POINTER);
    ASSERT_FALSE(material_pointer_any_value.bool_value);
    ASSERT_TRUE(std::isnan(material_pointer_any_value.float_value));
    ASSERT_TRUE(std::isnan(material_pointer_any_value.double_value));
    ASSERT_EQ(material_pointer_any_value.int32_t_value, 0);
    ASSERT_EQ(material_pointer_any_value.uint32_t_value, 0);
    ASSERT_EQ(material_pointer_any_value.bool_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.float_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.double_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.int32_t_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.universe_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.scene_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.shader_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.material_pointer, material);
    ASSERT_EQ(material_pointer_any_value.species_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.object_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.vector_font_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.glyph_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.text3D_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.font2D_pointer, nullptr);
    ASSERT_EQ(material_pointer_any_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_datatype().c_str()), strlen("ontology::Material*"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_datatype().c_str(), "ontology::Material*"), 0);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_string().c_str()), strlen("bad6a7e71a1"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_string().c_str(), "bad6a7e71a1"), 0);
}
TEST(any_value_must_be_initialized_appropriately, species)
{
    ontology::Species* species = static_cast<ontology::Species*>((void*) 0xbad5bec1e5);
    datatypes::AnyValue species_pointer_any_value = datatypes::AnyValue(species);
    ASSERT_EQ(species_pointer_any_value.type, datatypes::SPECIES_POINTER);
    ASSERT_FALSE(species_pointer_any_value.bool_value);
    ASSERT_TRUE(std::isnan(species_pointer_any_value.float_value));
    ASSERT_TRUE(std::isnan(species_pointer_any_value.double_value));
    ASSERT_EQ(species_pointer_any_value.int32_t_value, 0);
    ASSERT_EQ(species_pointer_any_value.uint32_t_value, 0);
    ASSERT_EQ(species_pointer_any_value.bool_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.float_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.double_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.int32_t_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.universe_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.scene_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.shader_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.material_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.species_pointer, species);
    ASSERT_EQ(species_pointer_any_value.object_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.vector_font_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.glyph_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.text3D_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.font2D_pointer, nullptr);
    ASSERT_EQ(species_pointer_any_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_datatype().c_str()), strlen("ontology::Species*"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_datatype().c_str(), "ontology::Species*"), 0);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_string().c_str()), strlen("bad5bec1e5"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_string().c_str(), "bad5bec1e5"), 0);
}
TEST(any_value_must_be_initialized_appropriately, object)
{
    ontology::Object* object = static_cast<ontology::Object*>((void*) 0xbad0b1ec7);
    datatypes::AnyValue object_pointer_any_value = datatypes::AnyValue(object);
    ASSERT_EQ(object_pointer_any_value.type, datatypes::OBJECT_POINTER);
    ASSERT_FALSE(object_pointer_any_value.bool_value);
    ASSERT_TRUE(std::isnan(object_pointer_any_value.float_value));
    ASSERT_TRUE(std::isnan(object_pointer_any_value.double_value));
    ASSERT_EQ(object_pointer_any_value.int32_t_value, 0);
    ASSERT_EQ(object_pointer_any_value.uint32_t_value, 0);
    ASSERT_EQ(object_pointer_any_value.bool_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.float_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.double_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.int32_t_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.uint32_t_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.universe_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.scene_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.shader_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.material_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.species_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.object_pointer, object);
    ASSERT_EQ(object_pointer_any_value.vector_font_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.glyph_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.text3D_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.symbiosis_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.font2D_pointer, nullptr);
    ASSERT_EQ(object_pointer_any_value.console_pointer, nullptr);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_datatype().c_str()), strlen("ontology::Object*"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_datatype().c_str(), "ontology::Object*"), 0);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_string().c_str()), strlen("bad0b1ec7"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_string().c_str(), "bad0b1ec7"), 0);
}
