#include <gtest/gtest.h>

#include <improc/infrastructure/structures/file_content_type.hpp>

TEST(FileContentType, TestEmptyFileContentTypeConstructor) {
    improc::FileContentType content_type {};
    EXPECT_EQ(content_type, improc::FileContentType::kJSON);
}

TEST(FileContentType,TestConstructorFromValue) {
    improc::FileContentType content_type {improc::FileContentType::Value::kBinary};
    EXPECT_EQ(content_type,improc::FileContentType::Value::kBinary);
}

TEST(FileContentType, TestToStringInvalidValue) {
    improc::FileContentType invalid_type(static_cast<improc::FileContentType::Value>(999));
    EXPECT_THROW(invalid_type.ToString(), improc::key_error);
}

TEST(FileContentType, TestConstructorFromLowerString) {
    EXPECT_EQ(improc::FileContentType("json"), improc::FileContentType::kJSON);
    EXPECT_EQ(improc::FileContentType("binary"), improc::FileContentType::kBinary);
}

TEST(FileContentType, TestConstructorFromUpperString) {
    EXPECT_EQ(improc::FileContentType("JSON"), improc::FileContentType::kJSON);
    EXPECT_EQ(improc::FileContentType("BINARY"), improc::FileContentType::kBinary); 
}

TEST(FileContentType,TestInvalidFileContentTypeConstructor) {
    EXPECT_THROW(improc::FileContentType content_type {"invalid"},std::out_of_range);
}

TEST(FileContentType,TestConstructorFromClass) {
    EXPECT_EQ(improc::FileContentType::kJSON  ,improc::FileContentType::Value::kJSON);
    EXPECT_EQ(improc::FileContentType::kBinary,improc::FileContentType::Value::kBinary);
}

TEST(FileContentType, TestToString) {
    EXPECT_EQ(improc::FileContentType("json").ToString(), "JSON");
    EXPECT_EQ(improc::FileContentType("binary").ToString(), "Binary");
}
