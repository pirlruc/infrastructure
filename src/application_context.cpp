#include <improc/infrastructure/context/application_context.hpp>

/**
 * @brief Construct a new improc::ApplicationContext object
 * 
 */
improc::ApplicationContext::ApplicationContext(): EnvironmentContext<ApplicationContext>()
                                                , application_folder_("") {}

/**
 * @brief Sets the root folder of the application during execution
 * 
 * @param application_folder
 */
improc::ApplicationContext& improc::ApplicationContext::set_application_folder(const std::string& application_folder)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting application folder...");
    this->application_folder_ = std::move(application_folder);
    return (*this);
}

/**
 * @brief Obtains the root folder of the application during execution
 * 
 */
std::string improc::ApplicationContext::get_application_folder() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining application folder...");
    return this->application_folder_;
}
