/**
 * @brief Read <KeyType> element in json
 * 
 * @tparam KeyType 
 * @param json_elem 
 * @return KeyType 
 */
template<typename KeyType>
KeyType improc::jsonfile::ReadElement(const Json::Value& json_elem)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::critical
                      , "ERROR_04: Parsing not defined for element {}.",typeid(KeyType).name() );
    throw improc::not_supported_data_type();
}

/**
 * @brief Read string element in json
 * 
 * @tparam  
 * @param json_elem 
 * @return std::string 
 */
template<>
inline std::string improc::jsonfile::ReadElement(const Json::Value& json_elem)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Reading string json element..." );
    return json_elem.asString();
}
