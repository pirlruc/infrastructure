#include <improc/infrastructure/filesystem/folder.hpp>

/**
 * @brief Construct a new improc::Folder object
 * 
 */
improc::Folder::Folder() {}

/**
 * @brief Construct a new improc::Folder object
 * 
 * @param folder_path 
 */
improc::Folder::Folder(const std::string& folder_path) 
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating Folder object...");
    this->set_folder_path(std::move(folder_path));
}

/**
 * @brief Set the folder path object
 * 
 * @param folder_path
 */
improc::Folder& improc::Folder::set_folder_path(const std::string& folder_path)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting folder path {}...",folder_path);
    if (improc::Folder::IsFolder(folder_path) == false)
    {
        std::string error_message = "Invalid path for folder: " + folder_path;
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
    this->folder_path_ = std::filesystem::path(std::move(folder_path));
    return (*this);
}

/**
 * @brief Obtain list of files in a folder
 * 
 * @return std::vector<std::filesystem::path> - list of files in folder 
 */
std::vector<std::filesystem::path> improc::Folder::GetFilesInFolder() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtain files in folder {}...",this->folder_path_.string());
    return improc::folder::ListFilesInFolder::GetFiles(this->folder_path_);
}

/**
 * @brief Obtain list of files in a folder and subfolders
 * 
 * @return std::vector<std::filesystem::path> - list of files in folder and subfolders
 */
std::vector<std::filesystem::path> improc::Folder::GetFilesInFolderAndSubfolders() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Obtain files in folder and subfolders {}..."
                                        , this->folder_path_.string() );
    return improc::folder::ListFilesInFolderAndSubfolders::GetFiles(this->folder_path_);
}

/**
 * @brief Check if folder path exists and is a folder
 * 
 * @param folder_path
 * @return bool - true if folder exists and false otherwise
 */
bool improc::Folder::IsFolder(const std::string& folder_path)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Checking if folder path {} exists and is a folder...",folder_path);
    return std::filesystem::is_directory(std::move(folder_path));
}

/**
 * @brief Sort files by ascending filename.
 * 
 * @param filepaths 
 * @return std::vector<std::filesystem::path> 
 */
std::vector<std::filesystem::path> improc::Folder::SortFilesByAscendingFilename(std::vector<std::filesystem::path> filepaths)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Sort files by ascending filename...");
    std::sort   ( filepaths.begin()
                , filepaths.end()
                , [] (const std::filesystem::path& left_filepath, const std::filesystem::path& right_filepath) 
                    {
                        return left_filepath.filename() < right_filepath.filename();
                    }
                );
    return std::move(filepaths);
}
