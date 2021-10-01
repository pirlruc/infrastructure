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
template <class path_type, class list_file_type>
std::vector<path_type> improc::folder::ListFilesInFolder<path_type,list_file_type>::GetFiles(const path_type& folder_path)
{
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
