#include <improc/infrastructure/context/application_context.hpp>

improc::ApplicationContext::ApplicationContext(): EnvironmentContext<ApplicationContext>()
                                                , application_folder_("") {}

improc::ApplicationContext& improc::ApplicationContext::set_application_folder(const std::string& application_folder)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting application folder...");
    this->application_folder_ = application_folder;
    return (*this);
}

std::string improc::ApplicationContext::get_application_folder() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining application folder...");
    return this->application_folder_;
}
