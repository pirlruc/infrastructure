#ifndef IMPROC_INFRASTRUCTURE_ENVIRONMENT_CONTEXT_HPP
#define IMPROC_INFRASTRUCTURE_ENVIRONMENT_CONTEXT_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>

#include <type_traits>

namespace improc 
{
    /**
     * @brief Singleton template for application contexts
     * 
     * @tparam ContextType - Data type of the application context being created
     */
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