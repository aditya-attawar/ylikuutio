#include "gtest/gtest.h"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <string>   // std::string

TEST(unicode_value_from_string, char_only_a)
{
    const char text[] = "a";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
}

TEST(unicode_value_from_string, char_only_abc)
{
    const char text[] = "abc";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'b');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'c');
}

TEST(unicode_value_from_string, unicode_a)
{
    const char text[] = "&#xa;";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xa);
}

TEST(unicode_value_from_string, unicode_deadbeef)
{
    const char text[] = "&#xdeadbeef;";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xdeadbeef);
}

TEST(unicode_value_from_string, iloinen_10cc1_01c00_ja_c1e1ece_caace101_kaikkialle)
{
    const char text[] = "iloinen&#x10cc1;&#x01c00;ja&#xc1e1ece;&#xcaace101;kaikkialle";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'o');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'n');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'e');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'n');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0x10cc1);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0x01c00);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'j');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xc1e1ece);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xcaace101);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'e');
}
