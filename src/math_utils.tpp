template <typename NumericType>
bool improc::math::IsEven(const NumericType& number)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
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
bool improc::math::IsOdd(const NumericType& number)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
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
