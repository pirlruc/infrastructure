/**
 * @brief Read KeyType element in json
 * 
 * @tparam KeyType - data type of the element in the json element
 * @param json_elem - json element
 * @return KeyType - parsed json element into KeyType data type
 */
template<typename KeyType>
KeyType inline improc::json::ReadElement(const Json::Value& json_elem)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Reading json element with type {}..."
                                        , typeid(KeyType).name() );
    if constexpr (std::is_same_v<KeyType,std::string>)
    {
        return json_elem.asString();
    }
    else if constexpr (std::is_same_v<KeyType,bool>)
    {
        return json_elem.asBool();
    }
    else if constexpr (std::is_same_v<KeyType,unsigned int>)
    {
        return json_elem.asUInt();
    }
    else if constexpr (std::is_same_v<KeyType,int>)
    {
        return json_elem.asInt();
    }
    else if constexpr (std::is_same_v<KeyType,float>)
    {
        return json_elem.asFloat();
    }
    else if constexpr (std::is_same_v<KeyType,double>)
    {
        return json_elem.asDouble();
    }
    else
    {
        static_assert(improc::dependent_false_v<KeyType>,"Parsing not defined for element data type");
    }
}

/**
 * @brief Read KeyType array in json
 * 
 * @tparam KeyType - data type of the elements in the json array
 * @param json_vector - json array
 * @return std::vector<KeyType> - parsed json array into an array of KeyType elements
 */
template<typename KeyType>
std::vector<KeyType> inline improc::json::ReadVector(const Json::Value& json_vector)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Reading array json element with type {}..."
                                        , typeid(KeyType).name() );
    std::vector<KeyType> list_elems {};
    if (json_vector.isArray() == true)
    {
        std::transform  ( json_vector.begin(), json_vector.end(), std::back_inserter(list_elems)
                        , [] (const Json::Value& elem) -> KeyType {return improc::json::ReadElement<KeyType>(std::move(elem));} );
    }
    else
    {
        list_elems.push_back(improc::json::ReadElement<KeyType>(std::move(json_vector)));
    }
    return std::move(list_elems);
}
