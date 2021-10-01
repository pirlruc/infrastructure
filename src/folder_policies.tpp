/**
 * @brief Obtain files in folder according to list_file_type.
 * 
 * @tparam path_type       - can be either std::string or std::filesystem::path
 * @tparam list_file_type  - can be either:
 *                              1. std::filesystem::directory_iterator to get files in folder
 *                              2. std::filesystem::recursive_directory_iterator to get files in folder and subfolders
 * @param  folder_path 
 * @return std::vector<path_type> 
 */
template <class list_file_type, class path_type>
std::vector<path_type> improc::folder::ListFiles<list_file_type,path_type>::GetFiles(const path_type& folder_path)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtain files in folder {}...", std::filesystem::path(folder_path).string() );
    std::vector<path_type> files {};
    for (auto& folder_entry : list_file_type(folder_path))
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
 * @brief Do not sort files.
 * 
 * @tparam path_type - can be either std::string or std::filesystem::path
 * @param  filepaths 
 * @return std::vector<path_type> 
 */
template <class path_type>
std::vector<path_type> improc::folder::NoSorting<path_type>::Sort(const std::vector<path_type>& filepaths) 
{
    return std::move(filepaths);
}

/**
 * @brief Sort files by ascending filename.
 * 
 * @tparam path_type - can be either std::string or std::filesystem::path
 * @param  filepaths 
 * @return std::vector<path_type> 
 */
template <class path_type>
std::vector<path_type> improc::folder::SortFilesByAscendingFilename<path_type>::Sort(std::vector<path_type> filepaths)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::critical
                      , "ERROR_01: File sorting not supported for data type {}.",typeid(path_type).name() );
    throw improc::not_supported_data_type();
}

template <>
std::vector<std::filesystem::path> improc::folder::SortFilesByAscendingFilename<std::filesystem::path>::Sort(std::vector<std::filesystem::path> filepaths)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Sorting files by ascending filename..." );
    std::sort   ( filepaths.begin()
                , filepaths.end()
                , [] (const std::filesystem::path& left_filepath, const std::filesystem::path& right_filepath) 
                    {
                        return left_filepath.filename().string() < right_filepath.filename().string();
                    }
                );
    return std::move(filepaths);
}

template <>
std::vector<std::string> improc::folder::SortFilesByAscendingFilename<std::string>::Sort(std::vector<std::string> filepaths)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Sorting files by ascending filename..." );
    std::sort   ( filepaths.begin()
                , filepaths.end()
                , [] (const std::filesystem::path& left_filepath, const std::filesystem::path& right_filepath) 
                    {
                        return std::filesystem::path(left_filepath ).filename().string() 
                             < std::filesystem::path(right_filepath).filename().string();
                    }
                );
    return std::move(filepaths);
}