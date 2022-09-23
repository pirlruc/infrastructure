#ifndef IMPROC_INFRASTRUCTURE_ENVIRONMENT_CONTEXT_HPP
#define IMPROC_INFRASTRUCTURE_ENVIRONMENT_CONTEXT_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>

namespace improc 
{
    template <typename ContextType>
    class IMPROC_API EnvironmentContext
    {
        protected:
            EnvironmentContext();

        public:
            EnvironmentContext(EnvironmentContext&     that) = delete;
            EnvironmentContext(EnvironmentContext&&    that) = delete;
            void operator= (const EnvironmentContext&  that) = delete;
            void operator= (const EnvironmentContext&& that) = delete;

            static std::shared_ptr<ContextType>         get();
    };

    #include <improc/infrastructure/context/environment_context.tpp>
}

#endif