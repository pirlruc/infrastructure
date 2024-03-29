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
 * @brief Set the string data into object
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
 * @brief Get the string data from object
 * 
 * @return std::string
 */
std::string improc::String::get_data() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining string data...");
    return this->data_;
}

/**
 * @brief Converting string data to lower case
 * 
 */
improc::String& improc::String::ToLower()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to lower case...");
    std::transform  ( this->data_.begin(),this->data_.end(),this->data_.begin()
                    , [] (unsigned char character){ return std::tolower(std::move(character)); });
    return (*this);
}

/**
 * @brief Converting string data to upper case
 * 
 */
improc::String& improc::String::ToUpper()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to upper case...");
    std::transform  ( this->data_.begin(),this->data_.end(),this->data_.begin()
                    , [] (unsigned char character){ return std::toupper(std::move(character)); });
    return (*this);
}

/**
 * @brief Converting a string to lower case
 * 
 * @param str_data - string data
 * @return std::string - string data in lower case
 */
std::string improc::String::ToLower(const std::string& str_data)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to lower case...");
    std::string lower {std::move(str_data)};
    std::transform  ( lower.begin(),lower.end(),lower.begin()
                    , [] (unsigned char char_upper){ return std::tolower(std::move(char_upper)); });
    return lower;
}

/**
 * @brief Converting a string to upper case
 * 
 * @param str_data - string data
 * @return std::string - string data in upper case
 */
std::string improc::String::ToUpper(const std::string& str_data)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Transforming string to upper case...");
    std::string upper {std::move(str_data)};
    std::transform  ( upper.begin(),upper.end(),upper.begin()
                    , [] (unsigned char char_lower){ return std::toupper(std::move(char_lower)); });
    return upper;
}

/**
 * @brief Construct a new improc::JsonString object
 * 
 */
improc::JsonString::JsonString()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating json string reader...");
    Json::CharReaderBuilder char_reader_builder {};
    this->char_reader_ = std::make_unique<Json::CharReader*>(char_reader_builder.newCharReader());
}

/**
 * @brief Construct a new improc::JsonString object
 * 
 * @param json_string - json string data
 * @return Json::Value - result of parsing the json string
 */
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
        std::string error_message = fmt::format("Error parsing json string: {}",std::move(parse_errors));
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR  ( "ERROR_01: " + error_message);
        throw improc::json_error(std::move(error_message));
    }
    return json_parsed;
}
