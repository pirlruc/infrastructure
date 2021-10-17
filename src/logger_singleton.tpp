/**
 * @brief Construct a new improc::LoggerSingleton<LoggerType> object
 * 
 * @tparam LoggerType 
 * @param logger 
 */
template<typename LoggerType>
improc::LoggerSingleton<LoggerType>::LoggerSingleton(std::shared_ptr<spdlog::logger>&&        logger) : data_(std::move(logger)) {}

/**
 * @brief Construct a new improc::LoggerSingleton<LoggerType> object
 * 
 * @tparam LoggerType 
 * @param logger 
 */
template<typename LoggerType>
improc::LoggerSingleton<LoggerType>::LoggerSingleton(const std::shared_ptr<spdlog::logger>&   logger) : data_(std::move(logger)) {}

/**
 * @brief Obtain spdlog::logger object associated with improc::LoggerSingleton<LoggerType> object
 * 
 * @tparam LoggerType 
 * @return std::shared_ptr<spdlog::logger> 
 */
template<typename LoggerType>
std::shared_ptr<spdlog::logger> improc::LoggerSingleton<LoggerType>::data()
{
    SPDLOG_LOGGER_CALL(spdlog::default_logger(),spdlog::level::trace,"Obtaining spdlog logger...");
    return this->data_;
}

/**
 * @brief Create or get the improc::LoggerSingleton<LoggerType> object
 * The spdlog::logger associated with the improc::LoggerSingleton<LoggerType> object corresponds to 
 * the logger logger_name. If the logger_name is not provided, the default logger of spdlog is 
 * used. If the logger_name is provided and the logger is not defined, the console is used. 
 * 
 * @tparam LoggerType 
 * @param logger_name 
 * @return std::shared_ptr<LoggerType> 
 */
template<typename LoggerType> 
std::shared_ptr<LoggerType> improc::LoggerSingleton<LoggerType>::get(const std::string& logger_name)
{
    SPDLOG_LOGGER_CALL(spdlog::default_logger(),spdlog::level::trace,"Creating logger...");
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
                logger = spdlog::stdout_color_mt(std::move(logger_name));
                logger->set_level(spdlog::level::debug);
                logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%n] [%^%-8l%$] [%!:%@] %v");
            }
        }
        singleton = std::shared_ptr<LoggerType>(new LoggerType(std::move(logger)));
    }
    return singleton;
}
