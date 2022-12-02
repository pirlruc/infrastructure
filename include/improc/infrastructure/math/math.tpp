/**
 * @brief Checks if an integer data type is even
 * 
 * @param number
 * @return bool - returns true if it is even and false otherwise
 */
template <typename NumericType>
bool inline improc::math::IsEven(const NumericType& number)
{
    static_assert(std::is_integral_v<NumericType>, "Number should be an integer data type.");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Verifying if number {} is even...",number);
    if (number % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Checks if an integer data type is odd
 * 
 * @param number
 * @return bool - returns true if it is odd and false otherwise
 */
template <typename NumericType>
bool inline improc::math::IsOdd(const NumericType& number)
{
    static_assert(std::is_integral_v<NumericType>, "Number should be an integer data type.");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Verifying if number {} is odd...",number);
    if (number % 2 == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
