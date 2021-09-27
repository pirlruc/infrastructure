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
void improc::Folder::set_folder_path(const std::string& folder_path)
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
 * @brief Obtain list of files in a folder
 * 
 * @param folder_path
 * @return std::vector<std::filesystem::path> - list of files in folder 
 */
std::vector<std::filesystem::path> improc::Folder::GetFilesInFolder()
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtain files in folder {}...",this->folder_path_.string());
    std::vector<std::filesystem::path> files {};
    for (auto& folder_entry : std::filesystem::directory_iterator(this->folder_path_))
    {
        std::filesystem::path filepath = folder_entry.path();
        if (improc::File::IsFile(filepath.string()) == true)
        {
            files.push_back(std::move(filepath));
        }
    }
    return std::move(files);
}

/**
 * @brief Obtain list of files in a folder and subfolders
 * 
 * @param folder_path
 * @return std::vector<std::filesystem::path> - list of files in folder and subfolders
 */
std::vector<std::filesystem::path> improc::Folder::GetFilesInFolderAndSubfolders()
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtain files in folder and subfolders{}...",this->folder_path_.string());
    std::vector<std::filesystem::path> files {};
    for (auto& folder_entry : std::filesystem::recursive_directory_iterator(this->folder_path_))
    {
        std::filesystem::path filepath = folder_entry.path();
        if (improc::File::IsFile(filepath.string()) == true)
        {
            files.push_back(std::move(filepath));
        }
    }
    return std::move(files);
}

std::vector<std::filesystem::path> improc::SortFilesByFilename(std::vector<std::filesystem::path> files)
{
    std::sort   ( files.begin()
                , files.end()
                , [] (const auto& lhs, const auto& rhs) 
                    {
                        return lhs.filename().string() < rhs.filename().string();
                    }
                );
    return files;
}
