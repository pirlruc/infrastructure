#ifndef IMPROC_INFRASTRUCTURE_JSON_PARSER_HPP
#define IMPROC_INFRASTRUCTURE_JSON_PARSER_HPP

#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/improc_defs.hpp>
#include <improc/exception.hpp>

#include <json/json.h>
#include <type_traits>

namespace improc 
{
    namespace json
    {
        template<typename KeyType>
        IMPROC_API KeyType inline               ReadElement (const Json::Value& json_elem);

        template<typename KeyType>
        IMPROC_API std::vector<KeyType> inline  ReadVector  (const Json::Value& json_vector);
    }
}

#include <improc/infrastructure/parsers/json_parser.tpp>

#endif
