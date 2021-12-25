template <typename NumericType>
bool inline improc::math::IsEven(const NumericType& number)
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Verifying if number {} is even...",number );
    if (number % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename NumericType>
bool inline improc::math::IsOdd(const NumericType& number)
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Verifying if number {} is odd...",number );
    if (number % 2 == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
