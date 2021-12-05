/**
 * @brief Read <KeyType> element in json
 * 
 * @tparam KeyType 
 * @param json_elem 
 * @return KeyType 
 */
template<typename KeyType>
KeyType improc::json::ReadElement(const Json::Value& json_elem)
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
inline std::string improc::json::ReadElement(const Json::Value& json_elem)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Reading string json element..." );
    return json_elem.asString();
}


template<typename KeyType>
std::vector<KeyType> improc::json::ReadVector(const Json::Value& json_vector)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Reading array json element with type {}...",typeid(KeyType).name() );
    std::vector<KeyType> list_elems;
    if (json_vector.isArray() == true)
    {
        for (Json::Value::const_iterator elem_iter = json_vector.begin(); elem_iter != json_vector.end(); ++elem_iter)
        {
            list_elems.push_back(improc::json::ReadElement<KeyType>(*elem_iter));
        }
    }
    else
    {
        list_elems.push_back(improc::json::ReadElement<KeyType>(json_vector));
    }
    return std::move(list_elems);
}
