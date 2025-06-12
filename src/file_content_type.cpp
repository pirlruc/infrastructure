#include <improc/infrastructure/structures/file_content_type.hpp>

/**
 * @brief Construct a new improc::FileContentType object
 */
improc::FileContentType::FileContentType() : value_(improc::FileContentType::kJSON) {};

/**
 * @brief Construct a new improc::FileContentType object based on input string
 * 
 * @param file_content_type_str - file content type description as string
 */
improc::FileContentType::FileContentType(const std::string& file_content_type_str)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating file content type from string {}...", file_content_type_str);
    static const std::unordered_map<std::string,improc::FileContentType::Value> kToElemType = { {"json"  ,improc::FileContentType::Value::kJSON  }
                                                                                              , {"binary",improc::FileContentType::Value::kBinary}
                                                                                              };    
    this->value_ = kToElemType.at(improc::String::ToLower(std::move(file_content_type_str)));
}
