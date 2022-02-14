#include <gtest/gtest.h>

#include <improc/infrastructure/filesystem/file.hpp>
#include <improc/infrastructure/parsers/json_parser.hpp>

#include <improc_infrastructure_test_config.hpp>

TEST(JsonParser,TestReadingInvalidContent) {
    Json::Value json_content {"test"};
    EXPECT_THROW(improc::json::ReadElement<size_t>(json_content),improc::not_supported_data_type);
}

TEST(JsonParser,TestReadingStringContent) {
    Json::Value json_content {"test"};
    EXPECT_EQ(improc::json::ReadElement<std::string>(json_content),"test");
}

TEST(JsonParser,TestReadingUnsignedIntegerContent) {
    Json::Value json_content {1};
    EXPECT_EQ(improc::json::ReadElement<unsigned int>(json_content),1);
}

TEST(JsonParser,TestReadingIntegerContent) {
    Json::Value json_content {-1};
    EXPECT_EQ(improc::json::ReadElement<int>(json_content),-1);
}

TEST(JsonParser,TestReadingDoubleContent) {
    Json::Value json_content {2.5};
    EXPECT_EQ(improc::json::ReadElement<double>(json_content),2.5);
}

TEST(JsonParser,TestReadingFloatContent) {
    Json::Value json_content {3.2f};
    EXPECT_EQ(improc::json::ReadElement<float>(json_content),3.2f);
}

TEST(JsonParser,TestReadingStringArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/json_parser_types.json";
    improc::JsonFile file_exists {filepath};
    std::vector<std::string> content = improc::json::ReadVector<std::string>(file_exists.Read()["content-string"]);
    EXPECT_EQ(content[0],"test-0");
    EXPECT_EQ(content[1],"test-1");
}

TEST(JsonFile,TestReadingUnsignedIntegerArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/json_parser_types.json";
    improc::JsonFile file_exists {filepath};
    std::vector<unsigned int> content = improc::json::ReadVector<unsigned int>(file_exists.Read()["content-uint"]);
    EXPECT_EQ(content[0],0);
    EXPECT_EQ(content[1],1);
}

TEST(JsonFile,TestReadingIntegerArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/json_parser_types.json";
    improc::JsonFile file_exists {filepath};
    std::vector<int> content = improc::json::ReadVector<int>(file_exists.Read()["content-int"]);
    EXPECT_EQ(content[0],-2);
    EXPECT_EQ(content[1],-1);
}

TEST(JsonFile,TestReadingDoubleArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/json_parser_types.json";
    improc::JsonFile file_exists {filepath};
    std::vector<double> content = improc::json::ReadVector<double>(file_exists.Read()["content-double"]);
    EXPECT_EQ(content[0],-2.2);
    EXPECT_EQ(content[1],-3.2);
}

TEST(JsonFile,TestReadingFloatArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/json_parser_types.json";
    improc::JsonFile file_exists {filepath};
    std::vector<float> content = improc::json::ReadVector<float>(file_exists.Read()["content-float"]);
    EXPECT_EQ(content[0],2.2f);
    EXPECT_EQ(content[1],3.2f);
}
