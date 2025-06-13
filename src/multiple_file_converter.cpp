#include <improc/infrastructure/parsers/multiple_file_converter.hpp>

improc::MultipleFileConverter::MultipleFileConverter()
: conversion_map_(std::unordered_map<std::string, ContentPair>()) 
{}

/**
 * @brief Construct a new improc::MultipleFileConverter object with JSON configuration.
 * 
 * @param json_config JSON configuration specifying file processing rules.
 */
improc::MultipleFileConverter::MultipleFileConverter(const Json::Value& json_config)
: improc::MultipleFileConverter()
{
    this->Load(json_config);
};

/**
 * @brief Load or reload processing configuration.
 * @param json_config JSON configuration specifying file processing rules.
 * @return Reference to self for method chaining
 * @throws improc::value_error If configuration is invalid
 */
improc::MultipleFileConverter& improc::MultipleFileConverter::Load(const Json::Value& json_config)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Loading multiple file converter configuration...");
    if (json_config.isNull())
    {
        std::string error_message = "JSON configuration is empty";
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
    else if (!json_config.isObject())
    {
        std::string error_message = "JSON configuration must be a JSON object";
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_02: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
    this->conversion_map_.clear();
    this->ParseConfiguration(json_config);
    return (*this);
};

/**
 * @brief Validate and parse the configuration JSON
 * @param json_config Configuration to validate and parse
 * @throws improc::value_error If configuration is invalid
 */
void improc::MultipleFileConverter::ParseConfiguration(const Json::Value& json_config)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Parsing JSON configuration...");
    for (Json::Value::const_iterator config_elem_iter = json_config.begin(); config_elem_iter != json_config.end(); ++config_elem_iter)
    {
        static const std::string kFileContentTypeKey   = "file-content-type";
        static const std::string kTargetJsonContentKey = "json-content-key";

        const std::string& source_key = config_elem_iter.key().asString();
        if (!config_elem_iter->isObject())
        {
            std::string error_message = fmt::format("Configuration for key '{}' must be a JSON object", source_key);
            IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: " + error_message);
            throw improc::value_error(std::move(error_message));
        }
        if (!config_elem_iter->isMember(kFileContentTypeKey))
        {
            std::string error_message = fmt::format( "Missing '{}' in configuration for key '{}'"
                                                   , kFileContentTypeKey, source_key);
            IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_02: " + error_message);
            throw improc::value_error(std::move(error_message));
        }
        if (!config_elem_iter->isMember(kTargetJsonContentKey))
        {
            std::string error_message = fmt::format( "Missing '{}' in configuration for key '{}'"
                                                   , kTargetJsonContentKey, source_key);
            IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_03: " + error_message);
            throw improc::value_error(std::move(error_message));
        }

        try
        {
            improc::FileContentType content_type = improc::FileContentType((*config_elem_iter)[kFileContentTypeKey].asString());
            std::string target_key = (*config_elem_iter)[kTargetJsonContentKey].asString();
            this->conversion_map_[source_key] = std::make_pair(std::move(content_type), std::move(target_key));
        }
        catch (const std::exception& error)
        {
            std::string error_message = fmt::format("Invalid configuration for key '{}': {}", source_key, error.what());
            IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_04: " + error_message);
            throw improc::value_error(std::move(error_message));
        }
    }
}

/**
 * @brief Convert JSON with file references to self-contained JSON.
 * @param application_folder Base directory for relative filepaths.
 * @param json_data Input JSON potentially containing file references.
 * @return Json::Value New JSON with embedded file contents.
 * @throws improc::key_error If file content type is unsupported
 *
 */
Json::Value improc::MultipleFileConverter::ConvertToSingleFile  ( const std::string& application_folder
                                                                , const Json::Value& json_content) const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Converting multiple files into a single json file...");
    Json::Value json_result = json_content;
    for (Json::Value::const_iterator json_content_iter = json_content.begin(); json_content_iter != json_content.end(); ++json_content_iter)
    {
        const std::string source_key = json_content_iter.key().asString();
        if (json_content_iter->type() == Json::ValueType::objectValue)
        {
            json_result[source_key] = this->ConvertToSingleFile(application_folder, *json_content_iter);
        }
        else if (  json_content_iter->type() == Json::ValueType::arrayValue
                || json_content_iter->type() == Json::ValueType::stringValue )
        {
            auto conversion_info = this->conversion_map_.find(source_key);
            if (conversion_info == this->conversion_map_.end())
            {
                IMPROC_INFRASTRUCTURE_LOGGER_DEBUG("Source key '{}' not configured for processing, keeping as-is", source_key);
                continue;
            }

            auto [content_type, target_key] = conversion_info->second;
            Json::Value to_replace {};
            try
            {
                switch (content_type)
                {
                    case improc::FileContentType::kJSON:
                    {
                        Json::Value file_content = improc::JsonFile(*json_content_iter, application_folder).Read();
                        to_replace = this->ConvertToSingleFile(application_folder, std::move(file_content));
                        IMPROC_INFRASTRUCTURE_LOGGER_DEBUG("Source key '{}' processed as JSON file", source_key);
                        break;
                    }
                    case improc::FileContentType::kBinary:
                    {
                        std::string file_content = improc::File(*json_content_iter, application_folder).Read();
                        to_replace = cppcodec::base64_rfc4648::encode(std::move(file_content));
                        IMPROC_INFRASTRUCTURE_LOGGER_DEBUG("Source key '{}' processed as binary file", source_key);
                        break;
                    }
                    default:
                    {
                        std::string error_message = fmt::format("Source key '{}' with unsupported file content type", source_key);
                        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: " + error_message);
                        throw improc::key_error(error_message);
                    }
                }
                json_result.removeMember(source_key);
                json_result[target_key] = std::move(to_replace);
            }
            catch (const std::exception& error)
            {
                std::string error_message = fmt::format("Failed to process file content for key '{}': {}", source_key, error.what());
                IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_02: " + error_message);
                throw improc::json_error(std::move(error_message));
            }
        }
    }
    return json_result;
}
