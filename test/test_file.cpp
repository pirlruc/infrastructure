#include <gtest/gtest.h>

#include <improc/infrastructure/file.hpp>
#include <improc/infrastructure/json_parser.hpp>

#include <improc_infrastructure_test_config.hpp>

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

TEST(File,TestFileConstructorNonExistingFile) {
    EXPECT_THROW(improc::File file_not_exists {"test.txt"},improc::invalid_filepath);
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
    EXPECT_THROW(file_empty.set_filepath("test.txt"),improc::invalid_filepath);
}

TEST(File,TestNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {"file_tst.txt"};
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
    improc::File file_not_exists {"file_tst.txt"};
    file_not_exists.Remove();
    EXPECT_THROW(file_not_exists.Read(),improc::invalid_filepath);
}

TEST(File,TestReadingExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::File file_exists {filepath};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(File,TestRemovingNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {"file_tst.txt"};
    file_not_exists.Remove();
    EXPECT_FALSE(file_not_exists.Remove());
    EXPECT_FALSE(file_not_exists.Exists());
    EXPECT_FALSE(improc::File::Remove("file_tst.txt"));
}

TEST(File,TestRemovingExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json"; 
    std::filesystem::copy(filepath,"./toremove.json");
    improc::File file_exists {"./toremove.json"};
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

TEST(JsonFile,TestFileConstructorNonExistingFile) {
    EXPECT_THROW(improc::JsonFile file_not_exists {"test.json"},improc::invalid_filepath);
}

TEST(JsonFile,TestNonJsonFileConstructor) {
    EXPECT_THROW(improc::JsonFile file_str {"test.txt"},improc::invalid_filepath);
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
    EXPECT_THROW(file_empty.set_filepath("test.json"),improc::invalid_filepath);
}

TEST(JsonFile,TestNonJsonSetFilepath) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.txt";
    improc::JsonFile not_json_file {};
    EXPECT_THROW(not_json_file.set_filepath(filepath),improc::invalid_filepath);
}

TEST(JsonFile,TestNonExistingFile) {
    std::ofstream("file_tst.json");
    improc::JsonFile file_not_exists {"file_tst.json"};
    file_not_exists.Remove();
    EXPECT_FALSE(file_not_exists.Exists());
}

TEST(JsonFile,TestExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    EXPECT_EQ(file_exists.get_filepath() ,filepath);
    EXPECT_EQ(file_exists.get_filename() ,"test.json");
    EXPECT_EQ(file_exists.get_extension(),".json");
    EXPECT_TRUE (file_exists.Exists());
}

TEST(JsonFile,TestReadingNonExistingFile) {
    std::ofstream("file_tst.json");
    improc::JsonFile file_not_exists {"file_tst.json"};
    file_not_exists.Remove();
    EXPECT_THROW(file_not_exists.Read(),improc::invalid_filepath);
}

TEST(JsonFile,TestReadingExistingFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(JsonFile,TestReadingNonJsonFile) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.txt";
    EXPECT_THROW(improc::JsonFile::Read(filepath),improc::invalid_filepath);
}

TEST(JsonFile,TestReadingNonStringContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    EXPECT_THROW(improc::json::ReadElement<int>(file_exists.Read()),improc::not_supported_data_type);
}

TEST(JsonFile,TestReadingStringContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    std::string content = improc::json::ReadElement<std::string>(file_exists.Read()["content"]);
    EXPECT_FALSE(content.empty());
    EXPECT_EQ(content,"test");
}

TEST(JsonFile,TestReadingStringElemAsArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    std::vector<std::string> content = improc::json::ReadVector<std::string>(file_exists.Read()["content"]);
    EXPECT_EQ(content.size(),1);
    EXPECT_EQ(content[0],"test");
}

TEST(JsonFile,TestReadingStringArrayContent) {
    std::string filepath = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    improc::JsonFile file_exists {filepath};
    std::vector<std::string> content = improc::json::ReadVector<std::string>(file_exists.Read()["content_array"]);
    EXPECT_EQ(content.size(),2);
    EXPECT_EQ(content[0],"test_1");
    EXPECT_EQ(content[1],"test_2");
}
