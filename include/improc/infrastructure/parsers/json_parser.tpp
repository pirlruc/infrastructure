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
    IMPROC_INFRASTRUCTURE_LOGGER_ERROR  ( "ERROR_01: Parsing not defined for element {}."
                                        , typeid(KeyType).name() );
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading string json element...");
    return json_elem.asString();
}

template<>
inline double improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading double json element...");
    return json_elem.asDouble();
}

template<>
inline float improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading float json element...");
    return json_elem.asFloat();
}

template<>
inline unsigned int improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading unsigned integer json element...");
    return json_elem.asUInt();
}

template<>
inline int improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading integer json element...");
    return json_elem.asInt();
}

template<typename KeyType>
std::vector<KeyType> improc::json::ReadVector(const Json::Value& json_vector)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Reading array json element with type {}..."
                                        , typeid(KeyType).name() );
    std::vector<KeyType> list_elems {};
    if (json_vector.isArray() == true)
    {
        std::transform  ( json_vector.begin(), json_vector.end(), std::back_inserter(list_elems)
                        , [] (const Json::Value& elem) -> KeyType {return improc::json::ReadElement<KeyType>(elem);} );
    }
    else
    {
        list_elems.push_back(improc::json::ReadElement<KeyType>(json_vector));
    }
    return std::move(list_elems);
}
