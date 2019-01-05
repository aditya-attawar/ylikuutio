#include "gtest/gtest.h"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <vector>   // std::vector

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_empty_string)
{
    const std::string data_string = "";
    std::size_t data_index = 0;
    std::string dest_string;
    const char separator = 'a';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_separator_matches_1st_char_of_data_string)
{
    const std::string data_string = "a";
    std::size_t data_index = 0;
    std::string dest_string;
    const char separator = 'a';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 0);
}

TEST(extract_string_from_memory, 1_char_must_be_extracted_when_separator_does_not_match_and_data_string_size_is_1)
{
    const std::string data_string = "a";
    std::size_t data_index = 0;
    std::string dest_string;
    const char separator = 'b';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
}

TEST(extract_string_from_memory, 2_chars_must_be_extracted_when_separator_does_not_match_and_data_string_size_is_2)
{
    const std::string data_string = "ab";
    std::size_t data_index = 0;
    std::string dest_string;
    const char separator = 'c';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
}

TEST(extract_string_from_memory, 1_char_must_be_extracted_when_separator_matches_2nd_char_of_data_string)
{
    const std::string data_string = "ab";
    std::size_t data_index = 0;
    std::string dest_string;
    const char separator = 'b';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
}

TEST(extract_string_from_memory, 2_char_must_be_extracted_when_separator_matches_3rd_char_of_data_string)
{
    const std::string data_string = "abc";
    std::size_t data_index = 0;
    std::string dest_string;
    const char separator = 'c';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_empty_and_data_index_is_out_of_bounds)
{
    const std::string data_string = "";
    std::size_t data_index = 1;
    std::string dest_string;
    const char separator = 'a';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_1_char_and_data_index_is_out_of_bounds)
{
    const std::string data_string = "a";
    std::size_t data_index = 2;
    std::string dest_string;
    const char separator = 'b';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_2_chars_and_data_index_is_out_of_bounds)
{
    const std::string data_string = "ab";
    std::size_t data_index = 2;
    std::string dest_string;
    const char separator = 'c';
    yli::string::extract_string(data_string, data_index, dest_string, separator);
    ASSERT_EQ(dest_string.size(), 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    char text[] = "";
    char* text_pointer = text;

    const char end_string[] = "";
    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    yli::string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
    ASSERT_EQ(text_pointer, text);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    char text[] = "";
    char* text_pointer = text;

    const char end_string[] = "a";
    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    yli::string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
    ASSERT_EQ(text_pointer, text);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    char text[] = "";
    char* text_pointer = text;

    const char end_string[] = "aa";
    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    yli::string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
    ASSERT_EQ(text_pointer, text);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    char text[] = "";
    char* text_pointer = text;

    const char end_string[] = "ab";
    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    yli::string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
    ASSERT_EQ(text_pointer, text);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_end_string_is_same_char)
{
    char text[] = "a";
    char* text_pointer = text;

    const char end_string[] = "a";
    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    yli::string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
    ASSERT_EQ(text_pointer, text);
}

TEST(extract_string_from_memory, iloinen_lokki_laulaa_ja_nukkuu)
{
    char text[] = "iloinen lokki laulaa ja nukkuu";
    char* text_pointer = text;

    const char end_string[] = "ja";
    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    yli::string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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
    ASSERT_EQ((std::size_t) text_pointer, (std::size_t) text + 21);
}
