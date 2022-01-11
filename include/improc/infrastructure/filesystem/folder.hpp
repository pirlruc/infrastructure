#ifndef IMPROC_INFRASTRUCTURE_FOLDER_HPP
#define IMPROC_INFRASTRUCTURE_FOLDER_HPP

#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/infrastructure/filesystem/file.hpp>
#include <improc/infrastructure/filesystem/folder_policies.hpp>

#include <filesystem>

namespace improc 
{
    /**
     * @brief Folder object and utilities
     * 
     */
    class IMPROC_EXPORTS Folder
    {
        private:
            std::filesystem::path               folder_path_;

        public:
            Folder();
            Folder(const std::string& folder_path);

            Folder&                             set_folder_path(const std::string& folder_path);

            std::vector<std::filesystem::path>  GetFilesInFolder()              const;
            std::vector<std::filesystem::path>  GetFilesInFolderAndSubfolders() const;

            static bool                               IsFolder(const std::string& folder_path);
            static std::vector<std::filesystem::path> SortFilesByAscendingFilename(const std::vector<std::filesystem::path>& filepaths);
    };
}

#endif
