#include <gtest/gtest.h>

#include <improc/infrastructure/string.hpp>

TEST(String,TestEmptyStringConstructor) {
    improc::String str_empty {};
    EXPECT_TRUE(str_empty.get_data().empty());
}

TEST(String,TestStringConstructor) {
    improc::String str_not_empty {"test.txt"};
    EXPECT_STREQ(str_not_empty.get_data().c_str(),"test.txt");
}

TEST(String,TestSetString) {
    improc::String str_empty {};
    str_empty.set_string("test.txt");
    EXPECT_STREQ(str_empty.get_data().c_str(),"test.txt");
}

TEST(String,TestStringToLower) {
    improc::String string_upper {"TEST"};
    string_upper.ToLower();
    EXPECT_STREQ(string_upper.get_data().c_str(),"test");
}

TEST(String,TestStringToUpper) {
    improc::String string_lower {"test"};
    string_lower.ToUpper();
    EXPECT_STREQ(string_lower.get_data().c_str(),"TEST");
}

TEST(String,TestStringStaticToLower) {
    EXPECT_STREQ(improc::String::ToLower("TEST").c_str(),"test");
}

TEST(String,TestStringStaticToUpper) {
    EXPECT_STREQ(improc::String::ToUpper("test").c_str(),"TEST");
}

TEST(JsonString,TestEmptyJsonStringConstructor) {
    improc::JsonString str_empty {};
    EXPECT_THROW(str_empty.Parse(""),improc::json_parsing_error);
}

TEST(JsonString,TestJsonStringConstructor) {
    improc::JsonString str_not_empty {};
    EXPECT_EQ(str_not_empty.Parse("{\"content\": \"test.txt\"}")["content"],"test.txt");
}

TEST(JsonString,TestSetJsonString) {
    improc::JsonString str_empty {};
    EXPECT_EQ(str_empty.Parse("{\"content\": \"test.txt\"}")["content"],"test.txt");
}

TEST(JsonString,TestJsonStringParse) {
    improc::JsonString str_empty {};
    EXPECT_EQ(str_empty.Parse("{\"content\": \"test.txt\"}")["content"],"test.txt");
}
