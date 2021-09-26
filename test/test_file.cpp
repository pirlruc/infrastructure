#include <gtest/gtest.h>

#include <improc/infrastructure/file.hpp>
#include <improc/infrastructure/jsonfile_parser.hpp>

TEST(File,TestEmptyFileConstructor) {
    improc::File file_empty {};
    EXPECT_TRUE(file_empty.get_filepath().empty());
    EXPECT_TRUE(file_empty.get_filename().empty());
    EXPECT_TRUE(file_empty.get_extension().empty());
}

TEST(File,TestFileConstructor) {
    improc::File file_str {"../../test/data/test.json"};
    EXPECT_STREQ(file_str.get_filepath().c_str() ,"../../test/data/test.json");
    EXPECT_STREQ(file_str.get_filename().c_str() ,"test.json");
    EXPECT_STREQ(file_str.get_extension().c_str(),".json");
}

TEST(File,TestFileConstructorNonExistingFile) {
    EXPECT_THROW(improc::File file_not_exists {"test.txt"},improc::invalid_filepath);
}

TEST(File,TestSetFilepath) {
    improc::File file_empty {};
    file_empty.set_filepath("../../test/data/test.txt");
    EXPECT_STREQ(file_empty.get_filepath().c_str() ,"../../test/data/test.txt");
    EXPECT_STREQ(file_empty.get_filename().c_str() ,"test.txt");
    EXPECT_STREQ(file_empty.get_extension().c_str(),".txt");
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
    improc::File file_exists {"../../test/data/test.json"};
    EXPECT_STREQ(file_exists.get_filepath().c_str() ,"../../test/data/test.json");
    EXPECT_STREQ(file_exists.get_filename().c_str() ,"test.json");
    EXPECT_STREQ(file_exists.get_extension().c_str(),".json");
    EXPECT_TRUE (file_exists.Exists());
}

TEST(File,TestIsFile) {
    EXPECT_FALSE(improc::File::IsFile("test.txt"));
    EXPECT_FALSE(improc::File::IsFile("../../test/data"));
    EXPECT_TRUE (improc::File::IsFile("../../test/data/test.json"));
}

TEST(File,TestReadingNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {"file_tst.txt"};
    file_not_exists.Remove();
    EXPECT_THROW(file_not_exists.Read(),improc::invalid_filepath);
}

TEST(File,TestReadingExistingFile) {
    improc::File file_exists {"../../test/data/test.json"};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(File,TestRemovingNonExistingFile) {
    std::ofstream("file_tst.txt");
    improc::File file_not_exists {"file_tst.txt"};
    file_not_exists.Remove();
    EXPECT_NO_THROW(file_not_exists.Remove());
    EXPECT_FALSE(file_not_exists.Exists());
    EXPECT_NO_THROW(improc::File::Remove("file_tst.txt"));
}

TEST(File,TestRemovingExistingFile) {
    std::filesystem::copy("../../test/data/test.json","./toremove.json");
    improc::File file_exists {"./toremove.json"};
    EXPECT_TRUE(file_exists.Exists());
    EXPECT_NO_THROW(file_exists.Remove());
    EXPECT_FALSE(file_exists.Exists());
}

TEST(JsonFile,TestEmptyFileConstructor) {
    improc::JsonFile file_empty {};
    EXPECT_TRUE(file_empty.get_filepath().empty());
    EXPECT_TRUE(file_empty.get_filename().empty());
    EXPECT_TRUE(file_empty.get_extension().empty());
}

TEST(JsonFile,TestFileConstructor) {
    improc::JsonFile file_str {"../../test/data/test.json"};
    EXPECT_STREQ(file_str.get_filepath().c_str() ,"../../test/data/test.json");
    EXPECT_STREQ(file_str.get_filename().c_str() ,"test.json");
    EXPECT_STREQ(file_str.get_extension().c_str(),".json");
}

TEST(JsonFile,TestFileConstructorNonExistingFile) {
    EXPECT_THROW(improc::JsonFile file_not_exists {"test.json"},improc::invalid_filepath);
}

TEST(JsonFile,TestNonJsonFileConstructor) {
    EXPECT_THROW(improc::JsonFile file_str {"test.txt"},improc::invalid_filepath);
}

TEST(JsonFile,TestSetFilepath) {
    improc::JsonFile file_empty {};
    file_empty.set_filepath("../../test/data/test.json");
    EXPECT_STREQ(file_empty.get_filepath().c_str() ,"../../test/data/test.json");
    EXPECT_STREQ(file_empty.get_filename().c_str() ,"test.json");
    EXPECT_STREQ(file_empty.get_extension().c_str(),".json");
}

TEST(JsonFile,TestSetFilepathNonExistingFile) {
    improc::JsonFile file_empty {};
    EXPECT_THROW(file_empty.set_filepath("test.json"),improc::invalid_filepath);
}

TEST(JsonFile,TestNonJsonSetFilepath) {
    improc::JsonFile not_json_file {};
    EXPECT_THROW(not_json_file.set_filepath("../../test/data/test.txt"),improc::invalid_filepath);
}

TEST(JsonFile,TestNonExistingFile) {
    std::ofstream("file_tst.json");
    improc::JsonFile file_not_exists {"file_tst.json"};
    file_not_exists.Remove();
    EXPECT_FALSE(file_not_exists.Exists());
}

TEST(JsonFile,TestExistingFile) {
    improc::JsonFile file_exists {"../../test/data/test.json"};
    EXPECT_STREQ(file_exists.get_filepath().c_str() ,"../../test/data/test.json");
    EXPECT_STREQ(file_exists.get_filename().c_str() ,"test.json");
    EXPECT_STREQ(file_exists.get_extension().c_str(),".json");
    EXPECT_TRUE (file_exists.Exists());
}

TEST(JsonFile,TestReadingNonExistingFile) {
    std::ofstream("file_tst.json");
    improc::JsonFile file_not_exists {"file_tst.json"};
    file_not_exists.Remove();
    EXPECT_THROW(file_not_exists.Read(),improc::invalid_filepath);
}

TEST(JsonFile,TestReadingExistingFile) {
    improc::JsonFile file_exists {"../../test/data/test.json"};
    EXPECT_FALSE(file_exists.Read().empty());
}

TEST(JsonFile,TestReadingNonJsonFile) {
    EXPECT_THROW(improc::JsonFile::Read("../../test/data/test.txt"),improc::invalid_filepath);
}

TEST(JsonFile,TestReadingNonStringContent) {
    improc::JsonFile file_exists {"../../test/data/test.json"};
    EXPECT_THROW(improc::jsonfile::ReadElement<int>(file_exists.Read()),improc::not_supported_data_type);
}

TEST(JsonFile,TestReadingStringContent) {
    improc::JsonFile file_exists {"../../test/data/test.json"};
    std::string content = improc::jsonfile::ReadElement<std::string>(file_exists.Read()["content"]);
    EXPECT_FALSE(content.empty());
    EXPECT_STREQ(content.c_str(),"test");
}
