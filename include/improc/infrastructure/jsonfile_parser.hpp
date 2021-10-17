#ifndef IMPROC_INFRASTRUCTURE_JSONFILE_PARSER_HPP
#define IMPROC_INFRASTRUCTURE_JSONFILE_PARSER_HPP

#include <improc/improc_defs.hpp>

#include <json/json.h>

namespace improc {
    // The namespace is just to avoid having warnings related with static template methods in the class JsonFile
    namespace jsonfile
    {
        template<typename KeyType>
        IMPROC_EXPORTS KeyType              ReadElement(const Json::Value& json_elem);

        template<>
        IMPROC_EXPORTS inline std::string   ReadElement(const Json::Value& json_elem);
    }
}

#include <jsonfile_parser.tpp>

#endif
