#ifndef IMPROC_INFRASTRUCTURE_FILE_HPP
#define IMPROC_INFRASTRUCTURE_FILE_HPP

#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>
#include <improc/infrastructure/string.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/infrastructure/parsers/json_parser.hpp>

#include <json/json.h>

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>

namespace improc 
{
    /**
     * @brief File object and utilities
     * 
     */
    class IMPROC_EXPORTS File
    {
        private:
            std::filesystem::path   filepath_;

        public:
            File();
            File(const std::string& filepath);
            File(const Json::Value& filepath_json, const std::optional<std::string>& application_folder = std::optional<std::string>());

            File&                   set_filepath(const std::string& filepath);
            
            std::string             get_filepath () const;
            std::string             get_filename () const;
            std::string             get_extension() const;

            std::string             Read()   const;
            bool                    Remove() const;
            bool                    Exists() const;

            static std::string      Read    (const std::string& filepath);
            static bool             Remove  (const std::string& filepath);
            static bool             Exists  (const std::string& filepath);
            static bool             IsFile  (const std::string& filepath);
    };

    /**
     * @brief Json file object and utilities
     * 
     */
    class IMPROC_EXPORTS JsonFile : public File
    {
        public:
            JsonFile();
            JsonFile(const std::string& filepath);
            JsonFile(const Json::Value& filepath_json, const std::optional<std::string>& application_folder = std::optional<std::string>());

            JsonFile&               set_filepath(const std::string& filepath);

            Json::Value             Read() const;
            static Json::Value      Read(const std::string& filepath);

        private:
            static inline bool      IsExtensionValid(const improc::File& json_file);
    };
}

#endif
