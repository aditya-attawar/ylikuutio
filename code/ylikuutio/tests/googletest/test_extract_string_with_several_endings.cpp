#include "gtest/gtest.h"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "aa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "aa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "aa";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "ab";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "ab";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    const std::string text_string = "";
    std::size_t data_index = 0;

    char end_string[] = "ab";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_end_string_is_matching_1_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_end_string_is_matching_1_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_1_char_and_end_string_is_matching_1_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_first_char_of_end_string_matches_1st_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "ab";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_first_char_of_end_string_matches_1st_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "ab";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_1_char_and_first_char_of_end_string_matches_1st_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "ab";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_second_char_of_end_string_matches_1st_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "ba";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_second_char_of_end_string_matches_1st_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "ba";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_1_char_and_second_char_of_end_string_matches_1st_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "ba";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_both_chars_of_end_string_match_1st_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "aa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_both_chars_of_end_string_match_1st_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "aa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_1_char_and_both_chars_of_end_string_match_1st_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "aa";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_different_1_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "b";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_different_1_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "b";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_different_1_char)
{
    const std::string text_string = "a";
    std::size_t data_index = 0;

    char end_string[] = "b";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    char text[] = "aa";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    const std::string text_string = "aa";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    const std::string text_string = "aa";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "b";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "b";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "b";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "bc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "bc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "bc";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "cb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "cb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "cb";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "bb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "bb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "bb";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "c";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "c";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    const std::string text_string = "ab";
    std::size_t data_index = 0;

    char end_string[] = "c";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "a";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "b";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "b";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "b";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "c";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "c";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "c";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "d";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "d";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "d";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(dest_string[2], 'c');
    ASSERT_EQ(data_index, 3);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "ad";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "ad";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "ad";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "da";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "da";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "da";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "dea";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "dea";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "dea";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defa";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defa";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defga";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defga";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defga";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 0);
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "bd";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "bd";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "bd";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "db";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "db";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "db";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "deb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "deb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "deb";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defb";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defgb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defgb";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defgb";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "cd";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "cd";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "cd";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "dc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "dc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "dc";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "dec";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "dec";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "dec";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defc";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defgc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defgc";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "defgc";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "";
    std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text_string, data_index, dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    const std::string text_string = "abc";
    std::size_t data_index = 0;

    char end_string[] = "";
    std::string dest_string;

    string::extract_string_with_several_endings(text_string, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string[0], 'a');
    ASSERT_EQ(dest_string[1], 'b');
    ASSERT_EQ(dest_string[2], 'c');
    ASSERT_EQ(data_index, 3);
}
