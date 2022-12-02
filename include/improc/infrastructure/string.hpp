#ifndef IMPROC_INFRASTRUCTURE_STRING_HPP
#define IMPROC_INFRASTRUCTURE_STRING_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/exception.hpp>

#include <string>
#include <algorithm>
#include <json/json.h>

#include <improc/improc_compilation_variables.hpp>
#ifdef IMPROC_WITH_BOOST
    #include <boost/algorithm/string.hpp>
#endif

namespace improc 
{
    /**
     * @brief String object and utilities
     * 
     */
    class IMPROC_API String final
    {
        private:
            std::string                 data_;

        public:
            String();
            explicit String(const std::string& str_data);

            String&                     set_string(const std::string& str_data);
            std::string                 get_data() const;

            String&                     ToLower();
            String&                     ToUpper();

            static std::string          ToLower(const std::string& upper_str);
            static std::string          ToUpper(const std::string& lower_str);
    };

    /**
     * @brief Json string object and utilities
     * 
     */
    class IMPROC_API JsonString final
    {
        private:
            std::unique_ptr<Json::CharReader*>  char_reader_;

        public:
            JsonString();

            Json::Value                         Parse(const std::string& json_string) const;
    };
}

#endif