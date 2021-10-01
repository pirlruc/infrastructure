#include <gtest/gtest.h>

#include <improc/infrastructure/folder.hpp>

TEST(Folder,TestEmptyFolderConstructor) {
    improc::Folder folder_empty {};
}

TEST(Folder,TestFolderConstructorNonExisting) {
    EXPECT_THROW(improc::Folder folder_not_exists {"test"},improc::invalid_folder_path);
}

TEST(Folder,TestSetFolderPath) {
    improc::Folder folder_exists {};
    folder_exists.set_folder_path("../../test/data/test");
}

TEST(Folder,TestSetFolderPathNonExisting) {
    improc::Folder folder_not_exists {};
    EXPECT_THROW(folder_not_exists.set_folder_path("test"),improc::invalid_folder_path);
}

TEST(Folder,TestIsFolder) {
    EXPECT_FALSE(improc::Folder::IsFolder("test"));
    EXPECT_TRUE (improc::Folder::IsFolder("../../test/data"));
    EXPECT_FALSE(improc::Folder::IsFolder("../../test/data/test.json"));
}

TEST(Folder,TestGetFilesInFolder) {
    improc::Folder folder_exists {"../../test/data/test"};
    EXPECT_EQ(folder_exists.GetFilesInFolder().size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfolders) {
    improc::Folder folder_exists {"../../test/data/test"};
    EXPECT_EQ(folder_exists.GetFilesInFolderAndSubfolders().size(),4);
}

TEST(Folder,TestGetFilesInFolderUsingPath) {
    improc::folder::ListFiles<std::filesystem::directory_iterator,std::filesystem::path> folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingPath) {
    improc::folder::ListFiles<std::filesystem::recursive_directory_iterator,std::filesystem::path> folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),4);
}

TEST(Folder,TestGetFilesInFolderUsingPolicy) {
    improc::folder::ListFilesInFolder folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingPolicy) {
    improc::folder::ListFilesInFolderAndSubfolders folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),4);
}

TEST(Folder,TestGetFilesInFolderUsingStrings) {
    improc::folder::ListFiles<std::filesystem::directory_iterator,std::string> folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingStrings) {
    improc::folder::ListFiles<std::filesystem::recursive_directory_iterator,std::string> folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),4);
}

TEST(Folder,TestSortFilesByFilename) {
    improc::Folder folder_exists {"../../test/data/test"};
    std::vector<std::filesystem::path> files = folder_exists.GetFilesInFolderAndSubfolders();
    files = improc::Folder::SortFilesByAscendingFilename(files);
    EXPECT_STREQ(files[0].filename().c_str(),"test_1.txt");
    EXPECT_STREQ(files[1].filename().c_str(),"test_12.txt");
    EXPECT_STREQ(files[2].filename().c_str(),"test_2.txt");
    EXPECT_STREQ(files[3].filename().c_str(),"test_3.txt");
}

TEST(Folder,TestNoSortingPolicy) {
    improc::Folder folder_exists {"../../test/data/test"};
    std::vector<std::filesystem::path> files        = folder_exists.GetFilesInFolderAndSubfolders();
    std::vector<std::filesystem::path> sorted_files = improc::folder::NoSorting().Sort(files);
    for (size_t file_idx = 0; file_idx < files.size(); file_idx++)
    {
        EXPECT_STREQ(sorted_files[file_idx].filename().c_str(),files[file_idx].filename().c_str());
    }
}

TEST(Folder,TestSortFilesByAscendingFilenamePolicy) {
    improc::Folder folder_exists {"../../test/data/test"};
    std::vector<std::filesystem::path> files        = folder_exists.GetFilesInFolderAndSubfolders();
    std::vector<std::filesystem::path> sorted_files = improc::folder::SortFilesByAscendingFilename().Sort(files);
    EXPECT_STREQ(sorted_files[0].filename().c_str(),"test_1.txt");
    EXPECT_STREQ(sorted_files[1].filename().c_str(),"test_12.txt");
    EXPECT_STREQ(sorted_files[2].filename().c_str(),"test_2.txt");
    EXPECT_STREQ(sorted_files[3].filename().c_str(),"test_3.txt");
}

TEST(Folder,TestSortFilesByAscendingFilenamePolicyUsingString) {
    std::vector<std::string> files        = improc::folder::ListFilesInFolderAndSubfolders<std::string>().GetFiles("../../test/data/test");
    std::vector<std::string> sorted_files = improc::folder::SortFilesByAscendingFilename<std::string>().Sort(files);
    EXPECT_STREQ(std::filesystem::path(sorted_files[0]).filename().c_str(),"test_1.txt");
    EXPECT_STREQ(std::filesystem::path(sorted_files[1]).filename().c_str(),"test_12.txt");
    EXPECT_STREQ(std::filesystem::path(sorted_files[2]).filename().c_str(),"test_2.txt");
    EXPECT_STREQ(std::filesystem::path(sorted_files[3]).filename().c_str(),"test_3.txt");
}

TEST(Folder,TestSortFilesByAscendingFilenamePolicyUsingUnknown) {
    std::vector<int> array_int {0,2,21,1,3};
    EXPECT_THROW(improc::folder::SortFilesByAscendingFilename<int>().Sort(array_int),improc::not_supported_data_type);
}
