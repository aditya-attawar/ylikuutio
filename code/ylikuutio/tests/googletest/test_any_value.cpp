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
}

TEST(any_value_must_be_initialized_appropriately, bool_true)
{
    bool bool_true = true;
    datatypes::AnyValue true_value = datatypes::AnyValue(bool_true);
    ASSERT_EQ(true_value.type, datatypes::BOOL);
    ASSERT_TRUE(true_value.bool_value);
    ASSERT_EQ(std::strlen(true_value.get_datatype().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(true_value.get_string().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_string().c_str(), "true"), 0);
}

TEST(any_value_must_be_initialized_appropriately, bool_false)
{
    bool bool_false = false;
    datatypes::AnyValue false_value = datatypes::AnyValue(bool_false);
    ASSERT_EQ(false_value.type, datatypes::BOOL);
    ASSERT_FALSE(false_value.bool_value);
    ASSERT_EQ(std::strlen(false_value.get_datatype().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(false_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(false_value.get_string().c_str()), std::strlen("false"));
    ASSERT_EQ(std::strcmp(false_value.get_string().c_str(), "false"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_0)
{
    float float_zero = 0.0f;
    datatypes::AnyValue float_zero_value = datatypes::AnyValue(float_zero);
    ASSERT_EQ(float_zero_value.type, datatypes::FLOAT);
    ASSERT_EQ(float_zero_value.float_value, 0.0f);
    uint32_t* IEEE_754_0_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_zero_value.float_value);
    ASSERT_EQ(*IEEE_754_0_uint32_t_pointer, 0);
    ASSERT_EQ(std::strlen(float_zero_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_zero_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), std::strlen("0.000000"));
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(float_zero_value.get_string().c_str(), "0.000000"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_positive_infinity)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    datatypes::AnyValue float_positive_infinity_value = datatypes::AnyValue(float_positive_infinity);
    ASSERT_EQ(float_positive_infinity_value.type, datatypes::FLOAT);
    ASSERT_EQ(float_positive_infinity_value.float_value, std::numeric_limits<float>::infinity());
    uint32_t* IEEE_754_0_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_positive_infinity_value.float_value);
    ASSERT_EQ(*IEEE_754_0_uint32_t_pointer, 0x7f800000);
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_string().c_str()), std::strlen("inf"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_string().c_str(), "inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_negative_infinity)
{
    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    datatypes::AnyValue float_negative_infinity_value = datatypes::AnyValue(float_negative_infinity);
    ASSERT_EQ(float_negative_infinity_value.type, datatypes::FLOAT);
    ASSERT_EQ(float_negative_infinity_value.float_value, float_negative_infinity);
    uint32_t* IEEE_754_0_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_negative_infinity_value.float_value);
    ASSERT_EQ(*IEEE_754_0_uint32_t_pointer, 0xff800000);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_string().c_str()), std::strlen("-inf"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_string().c_str(), "-inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_NAN)
{
    float float_NAN = NAN;
    datatypes::AnyValue float_NAN_value = datatypes::AnyValue(float_NAN);
    ASSERT_EQ(float_NAN_value.type, datatypes::FLOAT);
    ASSERT_TRUE(std::isnan(float_NAN_value.float_value));
    uint32_t* IEEE_754_NAN_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_NAN_value.float_value);
    ASSERT_GT(*IEEE_754_NAN_uint32_t_pointer & 0x7fffffff, 0x7f800000);
    ASSERT_EQ(std::strlen(float_NAN_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_NAN_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_NAN_value.get_string().c_str()), std::strlen("nan"));
    ASSERT_EQ(std::strcmp(float_NAN_value.get_string().c_str(), "nan"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_0)
{
    double double_zero = 0.0f;
    datatypes::AnyValue double_zero_value = datatypes::AnyValue(double_zero);
    ASSERT_EQ(double_zero_value.type, datatypes::DOUBLE);
    ASSERT_EQ(double_zero_value.double_value, 0.0f);
    uint64_t* IEEE_754_0_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_zero_value.double_value);
    ASSERT_EQ(*IEEE_754_0_uint64_t_pointer, 0);
    ASSERT_EQ(std::strlen(double_zero_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_zero_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), std::strlen("0.000000"));
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(double_zero_value.get_string().c_str(), "0.000000"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_positive_infinity)
{
    double double_positive_infinity = std::numeric_limits<double>::infinity();
    datatypes::AnyValue double_positive_infinity_value = datatypes::AnyValue(double_positive_infinity);
    ASSERT_EQ(double_positive_infinity_value.type, datatypes::DOUBLE);
    ASSERT_EQ(double_positive_infinity_value.double_value, std::numeric_limits<double>::infinity());
    uint64_t* IEEE_754_NAN_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_positive_infinity_value.double_value);
    ASSERT_EQ(*IEEE_754_NAN_uint64_t_pointer, 0x7ff0000000000000);
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_string().c_str()), std::strlen("inf"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_string().c_str(), "inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_negative_infinity)
{
    double double_negative_infinity = -1 * std::numeric_limits<double>::infinity();
    datatypes::AnyValue double_negative_infinity_value = datatypes::AnyValue(double_negative_infinity);
    ASSERT_EQ(double_negative_infinity_value.type, datatypes::DOUBLE);
    ASSERT_EQ(double_negative_infinity_value.double_value, double_negative_infinity);
    uint64_t* IEEE_754_NAN_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_negative_infinity_value.double_value);
    ASSERT_EQ(*IEEE_754_NAN_uint64_t_pointer, 0xfff0000000000000);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_string().c_str()), std::strlen("-inf"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_string().c_str(), "-inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_NAN)
{
    double double_NAN = NAN;
    datatypes::AnyValue double_NAN_value = datatypes::AnyValue(double_NAN);
    ASSERT_EQ(double_NAN_value.type, datatypes::DOUBLE);
    ASSERT_TRUE(std::isnan(double_NAN_value.double_value));
    uint64_t* IEEE_754_NAN_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_NAN_value.double_value);
    ASSERT_GT(*IEEE_754_NAN_uint64_t_pointer & 0x7fffffffffffffff, 0x7ff0000000000000);
    ASSERT_EQ(std::strlen(double_NAN_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_NAN_value.get_string().c_str()), std::strlen("nan"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_string().c_str(), "nan"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_zero)
{
    int32_t int32_t_zero = 0;
    datatypes::AnyValue int32_t_zero_value = datatypes::AnyValue(int32_t_zero);
    ASSERT_EQ(int32_t_zero_value.type, datatypes::INT32_T);
    ASSERT_EQ(int32_t_zero_value.int32_t_value, 0);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_zero_value.int32_t_value), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_string().c_str()), std::strlen("0"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_string().c_str(), "0"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    datatypes::AnyValue int32_t_plus_1_value = datatypes::AnyValue(int32_t_plus_1);
    ASSERT_EQ(int32_t_plus_1_value.type, datatypes::INT32_T);
    ASSERT_EQ(int32_t_plus_1_value.int32_t_value, 1);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_plus_1_value.int32_t_value), 1);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_string().c_str()), std::strlen("1"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_string().c_str(), "1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    datatypes::AnyValue int32_t_minus_1_value = datatypes::AnyValue(int32_t_minus_1);
    ASSERT_EQ(int32_t_minus_1_value.type, datatypes::INT32_T);
    ASSERT_EQ(int32_t_minus_1_value.int32_t_value, -1);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_minus_1_value.int32_t_value), 4294967295);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_minus_1_value.int32_t_value), 0xffffffff);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_string().c_str()), std::strlen("-1"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_string().c_str(), "-1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_max)
{
    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    datatypes::AnyValue int32_t_max_value = datatypes::AnyValue(int32_t_max);
    ASSERT_EQ(int32_t_max_value.type, datatypes::INT32_T);
    ASSERT_EQ(int32_t_max_value.int32_t_value, 2147483647);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_max_value.int32_t_value), 2147483647);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_max_value.int32_t_value), 0x7fffffff);
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int32_t>::max());
#ifdef __linux__
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int>::max());
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<long>::max());
#endif
    ASSERT_EQ(std::strlen(int32_t_max_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_max_value.get_string().c_str()), std::strlen("2147483647"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_string().c_str(), "2147483647"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_min)
{
    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    datatypes::AnyValue int32_t_min_value = datatypes::AnyValue(int32_t_min);
    ASSERT_EQ(int32_t_min_value.type, datatypes::INT32_T);
    ASSERT_EQ(int32_t_min_value.int32_t_value, -2147483648);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_min_value.int32_t_value), 2147483648);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_min_value.int32_t_value), 0x80000000);
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int32_t>::min());
#ifdef __linux__
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int>::min());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int>::min());
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<long>::min());
#endif
    ASSERT_EQ(std::strlen(int32_t_min_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_min_value.get_string().c_str()), std::strlen("-2147483648"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_string().c_str(), "-2147483648"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_zero)
{
    uint32_t uint32_t_zero = 0;
    datatypes::AnyValue uint32_t_zero_value = datatypes::AnyValue(uint32_t_zero);
    ASSERT_EQ(uint32_t_zero_value.type, datatypes::UINT32_T);
    ASSERT_EQ(uint32_t_zero_value.uint32_t_value, 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_string().c_str()), std::strlen("0"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_string().c_str(), "0"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    datatypes::AnyValue uint32_t_plus_1_value = datatypes::AnyValue(uint32_t_plus_1);
    ASSERT_EQ(uint32_t_plus_1_value.type, datatypes::UINT32_T);
    ASSERT_EQ(uint32_t_plus_1_value.uint32_t_value, 1);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_string().c_str()), std::strlen("1"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_string().c_str(), "1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_max)
{
    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    datatypes::AnyValue uint32_t_max_value = datatypes::AnyValue(uint32_t_max);
    ASSERT_EQ(uint32_t_max_value.type, datatypes::UINT32_T);
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
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_string().c_str()), std::strlen("4294967295"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_string().c_str(), "4294967295"), 0);
}

TEST(any_value_must_be_initialized_appropriately, universe)
{
    ylikuutio::ontology::Universe* universe = static_cast<ylikuutio::ontology::Universe*>((void*) 0xdeadbeef);
    datatypes::AnyValue universe_any_value = datatypes::AnyValue(universe);
    ASSERT_EQ(universe_any_value.type, datatypes::UNIVERSE_POINTER);
    ASSERT_EQ(universe_any_value.universe, universe);
    ASSERT_EQ(std::strlen(universe_any_value.get_datatype().c_str()), std::strlen("ylikuutio::ontology::Universe*"));
    ASSERT_EQ(std::strcmp(universe_any_value.get_datatype().c_str(), "ylikuutio::ontology::Universe*"), 0);
    ASSERT_EQ(std::strlen(universe_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(universe_any_value.get_string().c_str(), "deadbeef"), 0);
}

TEST(any_value_must_be_initialized_appropriately, scene)
{
    ylikuutio::ontology::Scene* scene = static_cast<ylikuutio::ontology::Scene*>((void*) 0xbad5ce6e);
    datatypes::AnyValue scene_pointer_any_value = datatypes::AnyValue(scene);
    ASSERT_EQ(scene_pointer_any_value.type, datatypes::SCENE_POINTER);
    ASSERT_EQ(scene_pointer_any_value.scene_pointer, scene);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_datatype().c_str()), std::strlen("ylikuutio::ontology::Scene*"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_datatype().c_str(), "ylikuutio::ontology::Scene*"), 0);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_string().c_str()), std::strlen("bad5ce6e"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_string().c_str(), "bad5ce6e"), 0);
}

TEST(any_value_must_be_initialized_appropriately, shader)
{
    ylikuutio::ontology::Shader* shader = static_cast<ylikuutio::ontology::Shader*>((void*) 0xbad5bade7);
    datatypes::AnyValue shader_pointer_any_value = datatypes::AnyValue(shader);
    ASSERT_EQ(shader_pointer_any_value.type, datatypes::SHADER_POINTER);
    ASSERT_EQ(shader_pointer_any_value.shader_pointer, shader);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_datatype().c_str()), std::strlen("ylikuutio::ontology::Shader*"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_datatype().c_str(), "ylikuutio::ontology::Shader*"), 0);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_string().c_str()), std::strlen("bad5bade7"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_string().c_str(), "bad5bade7"), 0);
}

TEST(any_value_must_be_initialized_appropriately, material)
{
    ylikuutio::ontology::Material* material = static_cast<ylikuutio::ontology::Material*>((void*) 0xbad6a7e71a1);
    datatypes::AnyValue material_pointer_any_value = datatypes::AnyValue(material);
    ASSERT_EQ(material_pointer_any_value.type, datatypes::MATERIAL_POINTER);
    ASSERT_EQ(material_pointer_any_value.material_pointer, material);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_datatype().c_str()), std::strlen("ylikuutio::ontology::Material*"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_datatype().c_str(), "ylikuutio::ontology::Material*"), 0);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_string().c_str()), std::strlen("bad6a7e71a1"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_string().c_str(), "bad6a7e71a1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, species)
{
    ylikuutio::ontology::Species* species = static_cast<ylikuutio::ontology::Species*>((void*) 0xbad5bec1e5);
    datatypes::AnyValue species_pointer_any_value = datatypes::AnyValue(species);
    ASSERT_EQ(species_pointer_any_value.type, datatypes::SPECIES_POINTER);
    ASSERT_EQ(species_pointer_any_value.species_pointer, species);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_datatype().c_str()), std::strlen("ylikuutio::ontology::Species*"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_datatype().c_str(), "ylikuutio::ontology::Species*"), 0);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_string().c_str()), std::strlen("bad5bec1e5"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_string().c_str(), "bad5bec1e5"), 0);
}

TEST(any_value_must_be_initialized_appropriately, object)
{
    ylikuutio::ontology::Object* object = static_cast<ylikuutio::ontology::Object*>((void*) 0xbad0b1ec7);
    datatypes::AnyValue object_pointer_any_value = datatypes::AnyValue(object);
    ASSERT_EQ(object_pointer_any_value.type, datatypes::OBJECT_POINTER);
    ASSERT_EQ(object_pointer_any_value.object_pointer, object);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_datatype().c_str()), std::strlen("ylikuutio::ontology::Object*"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_datatype().c_str(), "ylikuutio::ontology::Object*"), 0);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_string().c_str()), std::strlen("bad0b1ec7"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_string().c_str(), "bad0b1ec7"), 0);
}
