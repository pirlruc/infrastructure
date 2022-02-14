template <typename ContextType>
improc::EnvironmentContext<ContextType>::EnvironmentContext() {}

template <typename ContextType>
std::shared_ptr<ContextType> improc::EnvironmentContext<ContextType>::get()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating environment context...");
    static std::shared_ptr<ContextType> singleton = nullptr;
    if (singleton == nullptr)
    {
        singleton = std::shared_ptr<ContextType>(new ContextType());
    }
    return singleton;
}
