#include <improc/infrastructure/string.hpp>

/**
 * @brief Construct a new improc::String object
 * 
 */
improc::String::String() {}

/**
 * @brief Construct a new improc::String object
 * 
 * @param str_data - string data
 */
improc::String::String(const std::string& str_data) : data_(std::move(str_data)) {}

/**
 * @brief Set the string object
 * 
 * @param str_data - string data
 */
improc::String& improc::String::set_string(const std::string& str_data)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting string {}...",str_data);
    this->data_ = std::move(str_data);
    return (*this);
}

/**
 * @brief Get the string object data
 * 
 * @return std::string
 */
std::string improc::String::get_data() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining string data...");
    return this->data_;
}

/**
 * @brief Converting string to lower case
 * 
 */
improc::String& improc::String::ToLower()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to lower case...");
    boost::algorithm::to_lower(this->data_);
    return (*this);
}

/**
 * @brief Converting string to upper case
 * 
 */
improc::String& improc::String::ToUpper()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to upper case...");
    boost::algorithm::to_upper(this->data_);
    return (*this);
}

/**
 * @brief Converting a string to lower case
 * 
 * @return std::string
 */
std::string improc::String::ToLower(const std::string& str_data)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to lower case...");
    return boost::algorithm::to_lower_copy(str_data);
}

/**
 * @brief Converting a string to upper case
 * 
 * @return std::string
 */
std::string improc::String::ToUpper(const std::string& str_data)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to upper case...");
    return boost::algorithm::to_upper_copy(str_data);
}

improc::JsonString::JsonString()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating json string reader...");
    Json::CharReaderBuilder char_reader_builder {};
    this->char_reader_ = std::make_unique<Json::CharReader*>(char_reader_builder.newCharReader());
}

Json::Value improc::JsonString::Parse(const std::string& json_string) const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Parsing json string...");
    Json::Value json_parsed  {};
    std::string parse_errors {};
    bool is_parse_successful = (*this->char_reader_)->parse( json_string.c_str()
                                                           , json_string.c_str() + json_string.length()
                                                           , &json_parsed, &parse_errors );
    if (is_parse_successful == false)
    {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR  ( "ERROR_01: Error parsing json string {}: {}."
                                            , json_string, parse_errors );
        throw improc::json_parsing_error();
    }
    return json_parsed;
}
