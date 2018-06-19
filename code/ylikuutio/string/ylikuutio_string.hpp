#ifndef __YLIKUUTIO_STRING_HPP_INCLUDED
#define __YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <list>      // std::list
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace string
{
    bool check_and_report_if_some_string_matches(
            const char* const base_pointer,
            const char* const data_pointer,
            const uint64_t data_size,
            const std::vector<std::string> identifier_strings_vector);

    bool check_and_report_if_some_string_matches(
            const std::string& data_string,
            const std::size_t data_index,
            const std::vector<std::string> identifier_strings_vector);

    void extract_string(
            const char* const src_base_pointer,
            char*& src_data_pointer,
            const uint64_t src_data_size,
            const char* const dest_base_pointer,
            char* dest_data_pointer,
            const uint64_t dest_data_size,
            const char* const char_end_string);

    void extract_string_with_several_endings(
            const char* const src_base_pointer,
            char*& src_data_pointer,
            const uint64_t src_data_size,
            const char* const dest_base_pointer,
            char* dest_data_pointer,
            const uint64_t dest_data_size,
            const char* const char_end_string);

    void extract_string_with_several_endings(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const dest_base_pointer,
            char* dest_data_pointer,
            const uint64_t dest_data_size,
            const char* const char_end_string);

    int32_t extract_last_part_of_string(
            const uint8_t* const src_base_pointer,
            const uint64_t src_data_size,
            uint8_t* const dest_base_pointer,
            const uint64_t dest_data_size,
            const char separator);

    int32_t extract_int32_t_value_from_string(
            const char* const src_base_pointer,
            char*& src_data_pointer,
            const uint64_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    int32_t extract_int32_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    float extract_float_value_from_string(
            const char* const src_base_pointer,
            char*& src_data_pointer,
            const uint64_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    int32_t extract_unicode_value_from_string(const char*& unicode_char_pointer);

    std::string convert_std_list_char_to_std_string(const std::list<char>& std_list_char);

    std::string convert_std_list_char_to_std_string(
            const std::list<char>& std_list_char,
            const uint32_t first_line_length,
            const uint32_t line_length);

    std::vector<std::string> convert_std_list_char_to_std_vector_std_string(
            const std::list<char>& std_list_char,
            const uint32_t line_length);

    bool check_if_float_string(const std::string& my_string);
    bool check_if_double_string(const std::string& my_string);
    bool check_if_floating_point_string(const std::string& my_string, int32_t safe_number_of_chars);

    bool check_if_signed_integer_string(const std::string& my_string);

    bool check_if_unsigned_integer_string(const std::string& my_string);

    void print_hexdump(const void* const start_address, const void* const end_address); // `begin` is inclusive, `end is exclusive.
}

#endif
