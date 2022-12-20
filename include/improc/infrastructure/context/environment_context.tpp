/**
 * @brief Construct a new improc::EnvironmentContext<ContextType> object
 * 
 * @tparam ContextType - Data type of the application context being created
 */
template <typename ContextType>
improc::EnvironmentContext<ContextType>::EnvironmentContext() 
{
    static_assert(std::is_base_of_v<improc::EnvironmentContext<ContextType>,ContextType>, "improc::EnvironmentContext must be base of ContextType");
}

/**
 * @brief Create or get the improc::EnvironmentContext<ContextType> object
 * 
 * @tparam ContextType - Data type of the application context being created
 */
template <typename ContextType>
std::shared_ptr<ContextType> improc::EnvironmentContext<ContextType>::get()
{
    static_assert(std::is_base_of_v<improc::EnvironmentContext<ContextType>,ContextType>, "improc::EnvironmentContext must be base of ContextType");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating environment context...");
    static std::shared_ptr<ContextType> singleton = nullptr;
    if (singleton == nullptr)
    {
        singleton = std::shared_ptr<ContextType>(new ContextType());
    }
    return singleton;
}
