#ifndef IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP
#define IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP

namespace improc {
    namespace folder 
    {
        /**
         * @brief General Policy for listing files.
         * 
         * @tparam path_type      - type considered for paths
         * @tparam list_file_type - rules to get files in folder
         */
        template <class list_file_type = std::filesystem::recursive_directory_iterator, class path_type = std::filesystem::path>
        struct ListFiles
        {
            static std::vector<path_type> GetFiles(const path_type& folder_path);
        };

        /**
         * @brief Policy for listing files in folder.
         * 
         * @tparam path_type      - type considered for paths
         */
        template <class path_type = std::filesystem::path>
        class IMPROC_EXPORTS ListFilesInFolder: public ListFiles<std::filesystem::directory_iterator,path_type> {};

        /**
         * @brief Policy for listing files in folder and subfolders.
         * 
         * @tparam path_type      - type considered for paths
         */
        template <class path_type = std::filesystem::path>
        class IMPROC_EXPORTS ListFilesInFolderAndSubfolders : public ListFiles<std::filesystem::recursive_directory_iterator,path_type> {};

        template <class path_type = std::filesystem::path>
        struct SortFilesByAscendingFilename
        {
            static std::vector<path_type> Sort(std::vector<path_type> filepaths);
        };
    }
}

#include <folder_policies.tpp>

#endif
