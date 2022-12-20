#ifndef IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP
#define IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP

#include <improc/improc_defs.hpp>
#include <improc/improc_type_traits.hpp>

namespace improc 
{
    namespace folder 
    {
        /**
         * @brief General Policy for listing files.
         * 
         * @tparam ListFileType - rules to get files in folder
         */
        template <class ListFileType = std::filesystem::recursive_directory_iterator>
        struct ListFiles final
        {
            static std::vector<std::filesystem::path> GetFiles(const std::filesystem::path& folder_path);
        };

        typedef ListFiles<std::filesystem::directory_iterator>              ListFilesInFolder;
        typedef ListFiles<std::filesystem::recursive_directory_iterator>    ListFilesInFolderAndSubfolders;
    }
}

#include <improc/infrastructure/filesystem/folder_policies.tpp>

#endif
