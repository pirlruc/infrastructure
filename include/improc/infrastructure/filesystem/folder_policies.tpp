/**
 * @brief Obtain files in folder according to list_file_type.
 * 
 * @tparam ListFileType  - can be either:
 *                              1. std::filesystem::directory_iterator to get files in folder
 *                              2. std::filesystem::recursive_directory_iterator to get files in folder and subfolders
 * @param  folder_path 
 * @return std::vector<path_type> 
 */
template <class ListFileType>
std::vector<std::filesystem::path> improc::folder::ListFiles<ListFileType>::GetFiles(const std::filesystem::path& folder_path)
{
    static_assert( improc::is_folder_iterator_v<ListFileType> 
                 , "ListFileType should be a std::filesystem::directory_iterator or std::filesystem::recursive_directory_iterator."); 
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ("Obtain files in folder {}...",folder_path.string());
    ListFileType directory_iterator = ListFileType(std::move(folder_path));

    std::vector<std::filesystem::path> filepaths {};
    std::transform  ( std::filesystem::begin(directory_iterator),std::filesystem::end(directory_iterator)
                    , std::back_inserter(filepaths)
                    , [] (const std::filesystem::directory_entry& directory_entry) -> std::string {return directory_entry.path();} );

    std::vector<std::filesystem::path> filtered_files {};
    std::copy_if( filepaths.begin(), filepaths.end()
                , std::back_inserter(filtered_files)
                , [] (const std::filesystem::path& path) {return improc::File::IsFile(std::move(path)) == true;} );
    return filtered_files;
}
