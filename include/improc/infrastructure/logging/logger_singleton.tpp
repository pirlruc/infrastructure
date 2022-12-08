/**
 * @brief Construct a new improc::LoggerSingleton<LoggerType> object
 * 
 * @tparam LoggerType - Data type of the logger being created
 * @param logger
 */
template<typename LoggerType>
improc::LoggerSingleton<LoggerType>::LoggerSingleton(std::shared_ptr<spdlog::logger>&&        logger) : data_(std::move(logger)) {}

/**
 * @brief Obtain spdlog::logger object associated with improc::LoggerSingleton<LoggerType> object
 * 
 * @tparam LoggerType - Data type of the logger being created
 * @return std::shared_ptr<spdlog::logger> 
 */
template<typename LoggerType>
std::shared_ptr<spdlog::logger> improc::LoggerSingleton<LoggerType>::data() const
{
    SPDLOG_LOGGER_TRACE(spdlog::default_logger(),"Obtaining default spdlog logger...");
    return this->data_;
}

/**
 * @brief Create or get the improc::LoggerSingleton<LoggerType> object
 * The spdlog::logger associated with the improc::LoggerSingleton<LoggerType> object corresponds to 
 * the logger logger_name. If the logger_name is not provided, the default logger of spdlog is 
 * used. If the logger_name is provided and the logger is not defined, the console is used. 
 * 
 * @tparam LoggerType - Data type of the logger being created
 * @param logger_name 
 * @return std::shared_ptr<LoggerType> 
 */
template<typename LoggerType> 
std::shared_ptr<LoggerType> improc::LoggerSingleton<LoggerType>::get(const std::string& logger_name)
{
    static_assert(std::is_base_of_v<improc::LoggerSingleton<LoggerType>,LoggerType>, "improc::LoggerSingleton must be base of LoggerType");
    SPDLOG_LOGGER_TRACE(spdlog::default_logger(),"Creating logger...");
    static std::shared_ptr<LoggerType> singleton = nullptr;
    if (singleton == nullptr)
    {
        std::shared_ptr<spdlog::logger> logger {};
        if (logger_name.empty() == true)
        {
            logger = spdlog::default_logger();
        }
        else
        {
            logger = spdlog::get(logger_name);
            if (logger == nullptr)
            {
                logger = spdlog::stdout_logger_mt(std::move(logger_name));
                logger->set_level(spdlog::level::debug);
                logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%n] [%^%-8l%$] [%!:%@] %v");
            }
        }
        singleton = std::shared_ptr<LoggerType>(new LoggerType(std::move(logger)));
    }
    return singleton;
}
