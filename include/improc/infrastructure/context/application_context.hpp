#ifndef IMPROC_INFRASTRUCTURE_APPLICATION_CONTEXT_HPP
#define IMPROC_INFRASTRUCTURE_APPLICATION_CONTEXT_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/context/environment_context.hpp>

namespace improc 
{
    class IMPROC_EXPORTS ApplicationContext : public EnvironmentContext<ApplicationContext> 
    {
        friend std::shared_ptr<ApplicationContext> EnvironmentContext::get();

        private:
            std::string             application_folder_;

        private:
            ApplicationContext();

        public:
            ApplicationContext(ApplicationContext&     that) = delete;
            ApplicationContext(ApplicationContext&&    that) = delete;
            void operator= (const ApplicationContext&  that) = delete;
            void operator= (const ApplicationContext&& that) = delete;

            ApplicationContext&     set_application_folder(const std::string& application_folder);
            std::string             get_application_folder() const;
    };
}

#endif