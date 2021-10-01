#ifndef IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP
#define IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP

namespace improc {
    namespace folder 
    {
        /**
         * @brief Policy for listing files in folder.
         * 
         * @tparam path_type      - type considered for paths
         * @tparam list_file_type - rules to get files in folder
         */
        template <class path_type = std::string, class list_file_type = std::filesystem::recursive_directory_iterator>
        struct ListFilesInFolder
        {
            std::vector<path_type> GetFiles(const path_type& folder_path);
        };
    }
}

#include <folder_policies.tpp>

#endif
