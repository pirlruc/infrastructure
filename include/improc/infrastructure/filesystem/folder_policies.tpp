/**
 * @brief Obtain files in folder according to list_file_type.
 * 
 * @tparam ListFileType  - can be either:
 *                              1. std::filesystem::directory_iterator to get files in folder
 *                              2. std::filesystem::recursive_directory_iterator to get files in folder and subfolders
 * @tparam PathType      - can be either std::string or std::filesystem::path
 * @param  folder_path 
 * @return std::vector<path_type> 
 */
template <class ListFileType, class PathType>
std::vector<PathType> improc::folder::ListFiles<ListFileType,PathType>::GetFiles(const PathType& folder_path)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Obtain files in folder {}..."
                                        , std::filesystem::path(folder_path).string() );
    ListFileType directory_iterator = ListFileType(folder_path);

    std::vector<std::string> filepaths {};
    std::transform  ( std::filesystem::begin(directory_iterator),std::filesystem::end(directory_iterator)
                    , std::back_inserter(filepaths)
                    , [] (const std::filesystem::directory_entry& directory_entry) -> std::string {return directory_entry.path().string();} );

    std::vector<PathType> filtered_files {};
    std::copy_if( filepaths.begin(), filepaths.end()
                , std::back_inserter(filtered_files)
                , [] (const std::string& path) {return improc::File::IsFile(path) == true;} );
    return std::move(filtered_files);
}

/**
 * @brief Sort files by ascending filename.
 * 
 * @tparam PathType - can be either std::string or std::filesystem::path
 * @param  filepaths 
 * @return std::vector<PathType> 
 */
template <class PathType>
std::vector<PathType> improc::folder::SortFilesByAscendingFilename<PathType>::Sort(std::vector<PathType> filepaths)
{
    IMPROC_INFRASTRUCTURE_LOGGER_ERROR  ( "ERROR_01: File sorting not supported for data type {}."
                                        , typeid(PathType).name() );
    throw improc::not_supported_data_type();
}

template <>
std::vector<std::filesystem::path> improc::folder::SortFilesByAscendingFilename<std::filesystem::path>::Sort(std::vector<std::filesystem::path> filepaths)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Sorting files by ascending filename...");
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Sorting files by ascending filename...");
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
