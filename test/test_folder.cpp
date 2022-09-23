#include <gtest/gtest.h>

#include <improc/infrastructure/filesystem/folder.hpp>

#include <improc_infrastructure_test_config.hpp>

TEST(Folder,TestEmptyFolderConstructor) {
    improc::Folder folder_empty {};
}

TEST(Folder,TestFolderConstructorNonExisting) {
    EXPECT_THROW(improc::Folder folder_not_exists {"test"},improc::invalid_folder_path);
}

TEST(Folder,TestSetFolderPath) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::Folder folder_exists {};
    EXPECT_NO_THROW(folder_exists.set_folder_path(folder_path));
}

TEST(Folder,TestSetFolderPathNonExisting) {
    improc::Folder folder_not_exists {};
    EXPECT_THROW(folder_not_exists.set_folder_path("test"),improc::invalid_folder_path);
}

TEST(Folder,TestIsFolder) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data";
    std::string filepath    = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test.json";
    EXPECT_FALSE(improc::Folder::IsFolder("test"));
    EXPECT_TRUE (improc::Folder::IsFolder(folder_path));
    EXPECT_FALSE(improc::Folder::IsFolder(filepath));
}

TEST(Folder,TestGetFilesInFolder) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::Folder folder_exists {folder_path};
    EXPECT_EQ(folder_exists.GetFilesInFolder().size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfolders) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::Folder folder_exists {folder_path};
    EXPECT_EQ(folder_exists.GetFilesInFolderAndSubfolders().size(),4);
}

TEST(Folder,TestGetFilesInFolderUsingPath) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::folder::ListFiles<std::filesystem::directory_iterator,std::filesystem::path> folder_list {};
    EXPECT_EQ(folder_list.GetFiles(folder_path).size(),2);
    EXPECT_EQ(improc::folder::ListFiles<std::filesystem::directory_iterator>::GetFiles(folder_path).size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingPath) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::folder::ListFiles<std::filesystem::recursive_directory_iterator,std::filesystem::path> folder_list {};
    EXPECT_EQ(folder_list.GetFiles(folder_path).size(),4);
    EXPECT_EQ(improc::folder::ListFiles<std::filesystem::recursive_directory_iterator>::GetFiles(folder_path).size(),4);
}

TEST(Folder,TestGetFilesInFolderUsingPolicy) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::folder::ListFilesInFolder folder_list {};
    EXPECT_EQ(folder_list.GetFiles(folder_path).size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingPolicy) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::folder::ListFilesInFolderAndSubfolders folder_list {};
    EXPECT_EQ(folder_list.GetFiles(folder_path).size(),4);
}

TEST(Folder,TestGetFilesInFolderUsingStrings) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::folder::ListFiles<std::filesystem::directory_iterator,std::string> folder_list {};
    EXPECT_EQ(folder_list.GetFiles(folder_path).size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingStrings) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::folder::ListFiles<std::filesystem::recursive_directory_iterator,std::string> folder_list {};
    EXPECT_EQ(folder_list.GetFiles(folder_path).size(),4);
}

TEST(Folder,TestSortFilesByFilename) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::Folder folder_exists {folder_path};
    std::vector<std::filesystem::path> files = folder_exists.GetFilesInFolderAndSubfolders();
    files = improc::Folder::SortFilesByAscendingFilename(files);
    EXPECT_STREQ(files[0].filename().string().c_str(),"test_1.txt");
    EXPECT_STREQ(files[1].filename().string().c_str(),"test_12.txt");
    EXPECT_STREQ(files[2].filename().string().c_str(),"test_2.txt");
    EXPECT_STREQ(files[3].filename().string().c_str(),"test_3.txt");
}

TEST(Folder,TestSortFilesByAscendingFilenamePolicy) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    improc::Folder folder_exists {folder_path};
    std::vector<std::filesystem::path> files        = folder_exists.GetFilesInFolderAndSubfolders();
    std::vector<std::filesystem::path> sorted_files = improc::folder::SortFilesByAscendingFilename().Sort(files);
    EXPECT_STREQ(sorted_files[0].filename().string().c_str(),"test_1.txt");
    EXPECT_STREQ(sorted_files[1].filename().string().c_str(),"test_12.txt");
    EXPECT_STREQ(sorted_files[2].filename().string().c_str(),"test_2.txt");
    EXPECT_STREQ(sorted_files[3].filename().string().c_str(),"test_3.txt");
}

TEST(Folder,TestSortFilesByAscendingFilenamePolicyUsingString) {
    std::string folder_path = std::string(IMPROC_INFRASTRUCTURE_TEST_FOLDER) + "/test/data/test";
    std::vector<std::string> files        = improc::folder::ListFilesInFolderAndSubfolders<std::string>().GetFiles(folder_path);
    std::vector<std::string> sorted_files = improc::folder::SortFilesByAscendingFilename<std::string>().Sort(files);
    EXPECT_STREQ(std::filesystem::path(sorted_files[0]).filename().string().c_str(),"test_1.txt");
    EXPECT_STREQ(std::filesystem::path(sorted_files[1]).filename().string().c_str(),"test_12.txt");
    EXPECT_STREQ(std::filesystem::path(sorted_files[2]).filename().string().c_str(),"test_2.txt");
    EXPECT_STREQ(std::filesystem::path(sorted_files[3]).filename().string().c_str(),"test_3.txt");
}

TEST(Folder,TestSortFilesByAscendingFilenamePolicyUsingUnknown) {
    std::vector<int> array_int {0,2,21,1,3};
    EXPECT_THROW(improc::folder::SortFilesByAscendingFilename<int>().Sort(array_int),improc::not_supported_data_type);
}
