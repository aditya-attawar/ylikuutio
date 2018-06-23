#include "gtest/gtest.h"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "aa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "ab";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_1_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, iloinen_lokki_laulaa_ja_nukkuu)
{
    char text[] = "iloinen lokki laulaa ja nukkuu";
    char* text_pointer = text;

    char end_string[] = "ja";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'i');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'o');
    ASSERT_EQ(*dest_array++, 'i');
    ASSERT_EQ(*dest_array++, 'n');
    ASSERT_EQ(*dest_array++, 'e');
    ASSERT_EQ(*dest_array++, 'n');
    ASSERT_EQ(*dest_array++, ' ');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'o');
    ASSERT_EQ(*dest_array++, 'k');
    ASSERT_EQ(*dest_array++, 'k');
    ASSERT_EQ(*dest_array++, 'i');
    ASSERT_EQ(*dest_array++, ' ');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'u');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, ' ');
    ASSERT_EQ(*dest_array++, 0);
}
