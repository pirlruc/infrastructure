#ifndef IMPROC_INFRASTRUCTURE_FOLDER_HPP
#define IMPROC_INFRASTRUCTURE_FOLDER_HPP

#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>
#include <improc/infrastructure/logger_infrastructure.hpp>
#include <improc/infrastructure/file.hpp>

#include <filesystem>

namespace improc {
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

            void set_folder_path(const std::string& folder_path);

            std::vector<std::filesystem::path>  GetFilesInFolder();
            std::vector<std::filesystem::path>  GetFilesInFolderAndSubfolders();

            static bool                         IsFolder(const std::string& folder_path);
    };

    std::vector<std::filesystem::path>          SortFilesByFilename(std::vector<std::filesystem::path> files);
}

#endif
