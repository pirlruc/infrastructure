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
#include <optional>

namespace improc 
{
    /**
     * @brief Base file object and utilities
     * 
     */
    class BaseFile
    {
        protected:
            std::filesystem::path   filepath_;

        public:
            BaseFile();
            explicit BaseFile(const std::string& filepath);
            explicit BaseFile(const std::filesystem::path& filepath);
            explicit BaseFile(const Json::Value& filepath_json, const std::optional<std::string>& application_folder = std::optional<std::string>());

            template<typename FilepathType>
            BaseFile&               set_filepath(const FilepathType& filepath);
            
            std::string             get_filepath () const;
            std::string             get_filename () const;
            std::string             get_extension() const;

            std::string             Read()   const;
            bool                    Remove() const;
            bool                    Exists() const;

            template<typename FilepathType>
            static std::string      Read    (const FilepathType& filepath);
            
            template<typename FilepathType>
            static bool             Remove  (const FilepathType& filepath);
            
            template<typename FilepathType>
            static bool             Exists  (const FilepathType& filepath);
            
            template<typename FilepathType>
            static bool             IsFile  (const FilepathType& filepath);
    };

    /**
     * @brief File object and utilities
     * 
     */
    class IMPROC_API File final: public BaseFile
    {
        public:
            File();
            explicit File(const std::string& filepath);
            explicit File(const std::filesystem::path& filepath);
            explicit File(const Json::Value& filepath_json, const std::optional<std::string>& application_folder = std::optional<std::string>());

            template<typename FilepathType>
            File&               set_filepath(const FilepathType& filepath);
    };

    /**
     * @brief Json file object and utilities
     * 
     */
    class IMPROC_API JsonFile final : public BaseFile
    {
        public:
            JsonFile();
            explicit JsonFile(const std::string& filepath);
            explicit JsonFile(const std::filesystem::path& filepath);
            explicit JsonFile(const Json::Value& filepath_json, const std::optional<std::string>& application_folder = std::optional<std::string>());

            template<typename FilepathType>
            JsonFile&               set_filepath(const FilepathType& filepath);

            Json::Value             Read() const;

            template<typename FilepathType>
            static Json::Value      Read(const FilepathType& filepath);

        private:
            static inline bool      IsExtensionValid(const improc::BaseFile& json_file);
    };
}

#include <improc/infrastructure/filesystem/file.tpp>

#endif
