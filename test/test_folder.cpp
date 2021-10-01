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

TEST(Folder,TestGetFilesInFolderUsingStrings) {
    improc::folder::ListFilesInFolder<std::string,std::filesystem::directory_iterator> folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),2);
}

TEST(Folder,TestGetFilesInFolderAndSubfoldersUsingStrings) {
    improc::folder::ListFilesInFolder<std::string,std::filesystem::recursive_directory_iterator> folder_list {};
    EXPECT_EQ(folder_list.GetFiles("../../test/data/test").size(),4);
}

TEST(Folder,TestSortFilesByFilename) {
    improc::Folder folder_exists {"../../test/data/test"};
    std::vector<std::filesystem::path> files = folder_exists.GetFilesInFolderAndSubfolders();
    files = improc::SortFilesByFilename(files);
    EXPECT_STREQ(files[0].filename().c_str(),"test_1.txt");
    EXPECT_STREQ(files[1].filename().c_str(),"test_12.txt");
    EXPECT_STREQ(files[2].filename().c_str(),"test_2.txt");
    EXPECT_STREQ(files[3].filename().c_str(),"test_3.txt");
}
