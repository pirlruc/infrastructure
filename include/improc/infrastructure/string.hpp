#ifndef IMPROC_INFRASTRUCTURE_STRING_HPP
#define IMPROC_INFRASTRUCTURE_STRING_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/exception.hpp>

#include <string>
#include <json/json.h>
#include <boost/algorithm/string.hpp>

namespace improc 
{
    /**
     * @brief String object and utilities
     * 
     */
    class IMPROC_EXPORTS String
    {
        private:
            std::string                 data_;

        public:
            String();
            String(const std::string& str_data);

            String&                     set_string(const std::string& str_data);
            std::string                 get_data() const;

            String&                     ToLower();
            String&                     ToUpper();

            static std::string          ToLower(const std::string& upper_str);
            static std::string          ToUpper(const std::string& lower_str);
    };


    class IMPROC_EXPORTS JsonString
    {
        private:
            std::unique_ptr<Json::CharReader*>  char_reader_;
            std::string                         json_string_;

        public:
            JsonString();
            JsonString(const std::string& json_string);

            JsonString&                         set_json_string(const std::string& json_string);

            Json::Value                         Parse() const;

            static Json::Value                  Parse(const std::string& json_string);
    };
}

#endif