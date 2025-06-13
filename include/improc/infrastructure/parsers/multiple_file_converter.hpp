#ifndef IMPROC_MULTIPLE_FILE_CONVERTER_HPP
#define IMPROC_MULTIPLE_FILE_CONVERTER_HPP

#include <unordered_map>
#include <json/json.h>
#include <improc/improc_defs.hpp>
#include <improc/infrastructure/filesystem/file.hpp>
#include <improc/infrastructure/structures/file_content_type.hpp>
#include <cppcodec/base64_rfc4648.hpp>

namespace improc
{

    /**
     * @class MultipleFileConverter
     * @brief Consolidates JSON data with file references into self-contained JSON by embedding file contents.
     */
    class IMPROC_API MultipleFileConverter final
    {
        private:
            typedef std::pair<FileContentType, std::string> ContentPair;
            std::unordered_map<std::string, ContentPair> conversion_map_;

        public:
            MultipleFileConverter();
            explicit MultipleFileConverter(const Json::Value& json_config);

            MultipleFileConverter&          Load(const Json::Value& json_config);

            Json::Value                     ConvertToSingleFile ( const std::string& application_folder
                                                                , const Json::Value& json_content ) const;

        private:
            void                            ParseConfiguration(const Json::Value& json_config);
    };
}

#endif