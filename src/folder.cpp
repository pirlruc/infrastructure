#include <improc/infrastructure/folder.hpp>

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
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating Folder object..." );
    this->set_folder_path(std::move(folder_path));
}

/**
 * @brief Set the folder path object
 * 
 * @param folder_path
 */
improc::Folder& improc::Folder::set_folder_path(const std::string& folder_path)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting folder path {}...",folder_path);
    if (improc::Folder::IsFolder(folder_path) == false)
    {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Invalid folder path {}.",folder_path );
        throw improc::invalid_folder_path();
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
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtain files in folder {}...",this->folder_path_.string());
    improc::folder::ListFilesInFolder<std::filesystem::path> folder_list {};
    return folder_list.GetFiles(this->folder_path_);
}

/**
 * @brief Obtain list of files in a folder and subfolders
 * 
 * @return std::vector<std::filesystem::path> - list of files in folder and subfolders
 */
std::vector<std::filesystem::path> improc::Folder::GetFilesInFolderAndSubfolders() const
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtain files in folder and subfolders {}...",this->folder_path_.string());
    improc::folder::ListFilesInFolderAndSubfolders<std::filesystem::path> folder_list {};
    return folder_list.GetFiles(this->folder_path_);
}

/**
 * @brief Check if folder path exists and is a folder
 * 
 * @param folder_path
 * @return true 
 * @return false 
 */
inline bool improc::Folder::IsFolder(const std::string& folder_path)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Checking if folder path {} exists and is a folder...",folder_path );
    return std::filesystem::is_directory(std::move(folder_path));
}

/**
 * @brief Sort files by ascending filename.
 * 
 * @param filepaths 
 * @return std::vector<std::filesystem::path> 
 */
std::vector<std::filesystem::path> improc::Folder::SortFilesByAscendingFilename(const std::vector<std::filesystem::path>& filepaths)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Sort files by ascending filename..." );
    return std::move(improc::folder::SortFilesByAscendingFilename<std::filesystem::path>().Sort(filepaths));
}
