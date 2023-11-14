#include <gtest/gtest.h>

#include <improc/infrastructure/filesystem/file.hpp>
#include <improc/infrastructure/parsers/json_parser.hpp>

#include <improc_infrastructure_test_config.hpp>

TEST(BaseFile,TestReadingNonExistingFile) {
    EXPECT_THROW(improc::BaseFile::Read(std::string("base_file_tst.txt")),improc::value_error);
    EXPECT_THROW(improc::BaseFile::Read(std::filesystem::path("base_file_tst.txt")),improc::value_error);
}

TEST(File,TestEmptyFileConstructor) {
    improc::File file_empty {};
    EXPECT_TRUE(file_empty.get_filepath().empty());
    EXPECT_TRUE(file_empty.get_filename().empty());
    EXPECT_TRUE(file_empty.get_extension().empty());
}

TEST(File,TestFileConstructor) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::File file_str {filepath};
    EXPECT_EQ(file_str.get_filepath() ,filepath);
    EXPECT_EQ(file_str.get_filename() ,"test.json");
    EXPECT_EQ(file_str.get_extension(),".json");
}

TEST(File,TestFileConstructorFromJson) {
    Json::Value json_file = improc::JsonFile::Read(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/filepath.json");
    improc::File file_str {json_file["single"],std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER)};
    std::filesystem::path gt_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER);
    gt_filepath /= "test/data/test/test_1.txt";
    EXPECT_EQ(file_str.get_filepath() ,gt_filepath);
    file_str = improc::File(json_file["multiple"],std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER));
    gt_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER);
    gt_filepath /= "test";
    gt_filepath /= "data";
    gt_filepath /= "test";
    gt_filepath /= "test_1.txt";
    EXPECT_EQ(file_str.get_filepath() ,gt_filepath);
}

TEST(File,TestFileConstructorNonExistingFile) {
    EXPECT_THROW(improc::File file_not_exists {std::string("test.txt")},improc::value_error);
}

TEST(File,TestSetFilepath) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.txt";
    improc::File file_empty {};
    file_empty.set_filepath(filepath);
    EXPECT_EQ(file_empty.get_filepath() ,filepath);
    EXPECT_EQ(file_empty.get_filename() ,"test.txt");
    EXPECT_EQ(file_empty.get_extension(),".txt");
}

TEST(File,TestSetFilepathNonExistingFile) {
    improc::File file_empty {};
    EXPECT_THROW(file_empty.set_filepath("test.txt"),improc::value_error);
}

TEST(File,TestNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {std::string("file_tst.txt")};
    file_not_exists.Remove();
    EXPECT_FALSE(file_not_exists.Exists());
    EXPECT_FALSE(improc::File::Exists("file_tst.txt"));
}

TEST(File,TestExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::File file_exists {filepath};
    EXPECT_EQ(file_exists.get_filepath() ,filepath);
    EXPECT_EQ(file_exists.get_filename() ,"test.json");
    EXPECT_EQ(file_exists.get_extension(),".json");
    EXPECT_TRUE (file_exists.Exists());
}

TEST(File,TestIsFile) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data";
    std::string filepath    = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    EXPECT_FALSE(improc::File::IsFile("test.txt"));
    EXPECT_FALSE(improc::File::IsFile(folder_path));
    EXPECT_TRUE (improc::File::IsFile(filepath));
}

TEST(File,TestReadingNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {std::string("file_tst.txt")};
    file_not_exists.Remove();
    EXPECT_THROW(file_not_exists.Read(),improc::value_error);
}

TEST(File,TestReadingExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::File file_exists {filepath};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(File,TestRemovingNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {std::string("file_tst.txt")};
    file_not_exists.Remove();
    EXPECT_FALSE(file_not_exists.Remove());
    EXPECT_FALSE(file_not_exists.Exists());
    EXPECT_FALSE(improc::File::Remove("file_tst.txt"));
}

TEST(File,TestRemovingExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json"; 
    std::filesystem::copy(filepath,"./toremove.json");
    improc::File file_exists {std::string("./toremove.json")};
    EXPECT_TRUE(file_exists.Exists());
    EXPECT_TRUE(file_exists.Remove());
    EXPECT_FALSE(file_exists.Exists());
}

TEST(JsonFile,TestEmptyFileConstructor) {
    improc::JsonFile file_empty {};
    EXPECT_TRUE(file_empty.get_filepath().empty());
    EXPECT_TRUE(file_empty.get_filename().empty());
    EXPECT_TRUE(file_empty.get_extension().empty());
}

TEST(JsonFile,TestFileConstructor) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_str {filepath};
    EXPECT_EQ(file_str.get_filepath() ,filepath);
    EXPECT_EQ(file_str.get_filename() ,"test.json");
    EXPECT_EQ(file_str.get_extension(),".json");
}

TEST(JsonFile,TestFileConstructorFromJson) {
    Json::Value json_file = improc::JsonFile::Read(std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/filepath.json");
    improc::JsonFile file_str {json_file["single-json"],std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER)};
    std::filesystem::path gt_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER);
    gt_filepath /= "test/data/test.json";
    EXPECT_EQ(file_str.get_filepath() ,gt_filepath);
    file_str = improc::JsonFile(json_file["multiple-json"],std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER));
    gt_filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER);
    gt_filepath /= "test";
    gt_filepath /= "data";
    gt_filepath /= "test.json";
    EXPECT_EQ(file_str.get_filepath() ,gt_filepath);
}

TEST(JsonFile,TestFileConstructorNonExistingFile) {
    EXPECT_THROW(improc::JsonFile file_not_exists {std::string("test.json")},improc::value_error);
}

TEST(JsonFile,TestNonJsonFileConstructor) {
    EXPECT_THROW(improc::JsonFile file_str {std::string("test.txt")},improc::value_error);
}

TEST(JsonFile,TestSetFilepath) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_empty {};
    file_empty.set_filepath(filepath);
    EXPECT_EQ(file_empty.get_filepath() ,filepath);
    EXPECT_EQ(file_empty.get_filename() ,"test.json");
    EXPECT_EQ(file_empty.get_extension(),".json");
}

TEST(JsonFile,TestSetFilepathNonExistingFile) {
    improc::JsonFile file_empty {};
    EXPECT_THROW(file_empty.set_filepath("test.json"),improc::value_error);
}

TEST(JsonFile,TestNonJsonSetFilepath) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.txt";
    improc::JsonFile not_json_file {};
    EXPECT_THROW(not_json_file.set_filepath(filepath),improc::value_error);
}

TEST(JsonFile,TestNonExistingFile) {
    std::ofstream("file_tst.json");
    improc::JsonFile file_not_exists {std::string("file_tst.json")};
    file_not_exists.Remove();
    EXPECT_FALSE(file_not_exists.Exists());
}

TEST(JsonFile,TestExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile json_file {filepath};
    EXPECT_EQ(json_file.get_filepath() ,filepath);
    EXPECT_EQ(json_file.get_filename() ,"test.json");
    EXPECT_EQ(json_file.get_extension(),".json");
    EXPECT_TRUE (json_file.Exists());
}

TEST(JsonFile,TestReadingNonExistingFile) {
    std::ofstream("file_tst.json");
    improc::JsonFile file_not_exists {std::string("file_tst.json")};
    file_not_exists.Remove();
    EXPECT_THROW(file_not_exists.Read(),improc::value_error);
}

TEST(JsonFile,TestReadingExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(JsonFile,TestReadingNonJsonFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.txt";
    EXPECT_THROW(improc::JsonFile::Read(filepath),improc::value_error);
}
