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
void improc::String::set_string(const std::string& str_data)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting string {}...",str_data );
    this->data_ = std::move(str_data);
}

/**
 * @brief Get the string object data
 * 
 * @return std::string
 */
std::string improc::String::get_data() const
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining string data..." );
    return this->data_;
}

/**
 * @brief Converting string to lower case
 * 
 */
void improc::String::ToLower()
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Transforming string to lower case..." );
    boost::algorithm::to_lower(this->data_);
}

/**
 * @brief Converting string to upper case
 * 
 */
void improc::String::ToUpper()
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Transforming string to upper case..." );
    boost::algorithm::to_upper(this->data_);
}

/**
 * @brief Converting a string to lower case
 * 
 * @return std::string
 */
const std::string improc::String::ToLower(const std::string& str_data)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Transforming string to lower case..." );
    return boost::algorithm::to_lower_copy(str_data);
}

/**
 * @brief Converting a string to upper case
 * 
 * @return std::string
 */
const std::string improc::String::ToUpper(const std::string& str_data)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Transforming string to upper case..." );
    return boost::algorithm::to_upper_copy(str_data);
}
