#include <gtest/gtest.h>
#include <improc_infrastructure_test_config.hpp>
#include <improc/infrastructure/filesystem/file.hpp>
#include <improc/infrastructure/parsers/multiple_file_converter.hpp>
#include <iostream>

TEST(MultipleFileConverter,TestEmptyConstructor) {
    EXPECT_NO_THROW(improc::MultipleFileConverter());
}

TEST(MultipleFileConverter, TestConstructorWithLoad) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    EXPECT_NO_THROW(improc::MultipleFileConverter {json_content});
}

TEST(MultipleFileConverter, TestLoad) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter = improc::MultipleFileConverter();
    EXPECT_NO_THROW(converter.Load(json_content));
}

TEST(MultipleFileConverter, TestLoadConfigEmpty)
{
    Json::Value json_content {};
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content),improc::value_error);
}

TEST(MultipleFileConverter, TestLoadInvalidConfigNotObject) {
    Json::Value json_content = "invalid_config";
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content), improc::value_error);
}

TEST(MultipleFileConverter, TestConverterJsonArray) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_invalid_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content["json_array"]), improc::value_error);
}

TEST(MultipleFileConverter, TestLoadInvalidConfigElem)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_invalid_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content["invalid_config_elem"]), improc::value_error);
}

TEST(MultipleFileConverter, TestLoadConfigElemArray)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_invalid_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content["json_elem_array"]), improc::value_error);
}

TEST(MultipleFileConverter, TestConverterMissingFileContentType) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_invalid_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content["missing_content_type"]), improc::value_error);
}

TEST(MultipleFileConverter, TestConverterMissingJsonContentKey) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_invalid_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content["missing_target_json"]), improc::value_error);
}

TEST(MultipleFileConverter, TestConverterInvalidFileContentType) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_invalid_config.json";
    Json::Value json_content  = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {};
    EXPECT_THROW(converter.Load(json_content["invalid_content_type"]), improc::value_error);
}

TEST(MultipleFileConverter, TestNoLoad) {
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_binary_file.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter = improc::MultipleFileConverter();
    Json::Value result = converter.ConvertToSingleFile(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER), json_content);
    EXPECT_EQ(result, json_content);
}

TEST(MultipleFileConverter, TestConverterInvalidFilepath)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    std::string json_transform_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_binary_file.json";
    Json::Value json_transform_content = improc::JsonFile::Read(json_transform_filepath);
    improc::MultipleFileConverter converter {json_content};
    EXPECT_THROW(converter.ConvertToSingleFile("", json_transform_content),improc::json_error);
}

TEST(MultipleFileConverter, TestConverterEmptyJson)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    improc::MultipleFileConverter converter {json_content};
    Json::Value json_transform_content {};
    Json::Value result = converter.ConvertToSingleFile(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER), json_transform_content);
    EXPECT_EQ(result, json_transform_content);
}

TEST(MultipleFileConverter, TestConverterEmptyJsonFromFile)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    std::string json_transform_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_no_data.json";
    Json::Value json_transform_content = improc::JsonFile::Read(json_transform_filepath);
    improc::MultipleFileConverter converter {json_content};
    Json::Value result = converter.ConvertToSingleFile(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER),json_transform_content);
    EXPECT_EQ(result, json_transform_content);
}

TEST(MultipleFileConverter, TestConverterJsonFile)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    std::string json_transform_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_json_file.json";
    Json::Value json_transform_content = improc::JsonFile::Read(json_transform_filepath);
    std::string json_data_expected_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_json_file_expected.json";
    Json::Value json_data_expected_content = improc::JsonFile::Read(json_data_expected_filepath);

    improc::MultipleFileConverter converter {json_content};
    Json::Value result = converter.ConvertToSingleFile(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER),json_transform_content);
    EXPECT_EQ(result, json_data_expected_content);
}

TEST(MultipleFileConverter, TestConverterBinaryFile)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    std::string json_transform_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_binary_file.json";
    Json::Value json_transform_content = improc::JsonFile::Read(json_transform_filepath);
    std::string json_data_expected_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_binary_file_expected.json";
    Json::Value json_data_expected_content = improc::JsonFile::Read(json_data_expected_filepath);

    improc::MultipleFileConverter converter {json_content};
    Json::Value result = converter.ConvertToSingleFile(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER),json_transform_content);
    EXPECT_EQ(result, json_data_expected_content);
}

TEST(MultipleFileConverter, TestConverterMultipleFileContentTypes)
{
    std::string json_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_config.json";
    Json::Value json_content = improc::JsonFile::Read(json_filepath);
    std::string json_transform_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_multiple_files.json";
    Json::Value json_transform_content = improc::JsonFile::Read(json_transform_filepath);
    std::string json_data_expected_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/multiple_file_multiple_files_expected.json";
    Json::Value json_data_expected_content = improc::JsonFile::Read(json_data_expected_filepath);

    improc::MultipleFileConverter converter {json_content};
    Json::Value result = converter.ConvertToSingleFile(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER),json_transform_content);
    EXPECT_EQ(result, json_data_expected_content);
}
