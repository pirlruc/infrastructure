#ifndef IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP
#define IMPROC_INFRASTRUCTURE_FOLDER_POLICIES_HPP

namespace improc 
{
    namespace folder 
    {
        /**
         * @brief General Policy for listing files.
         * 
         * @tparam ListFileType - rules to get files in folder
         * @tparam PathType     - type considered for paths
         */
        template <class ListFileType = std::filesystem::recursive_directory_iterator, class PathType = std::filesystem::path>
        struct ListFiles
        {
            static std::vector<PathType> GetFiles(const PathType& folder_path);
        };

        /**
         * @brief Policy for listing files in folder.
         * 
         * @tparam PathType      - type considered for paths
         */
        template <class PathType = std::filesystem::path>
        class IMPROC_EXPORTS ListFilesInFolder: public ListFiles<std::filesystem::directory_iterator,PathType> {};

        /**
         * @brief Policy for listing files in folder and subfolders.
         * 
         * @tparam PathType      - type considered for paths
         */
        template <class PathType = std::filesystem::path>
        class IMPROC_EXPORTS ListFilesInFolderAndSubfolders : public ListFiles<std::filesystem::recursive_directory_iterator,PathType> {};

        template <class PathType = std::filesystem::path>
        struct SortFilesByAscendingFilename
        {
            static std::vector<PathType> Sort(std::vector<PathType> filepaths);
        };
    }
}

#include <folder_policies.tpp>

#endif
