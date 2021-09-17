#ifndef IMPROC_INFRASTRUCTURE_LOGGER_INFRASTRUCTURE_HPP
#define IMPROC_INFRASTRUCTURE_LOGGER_INFRASTRUCTURE_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logger_singleton.hpp>

namespace improc {
    /**
     * @brief Logger used for infrastructure library
     * 
     */
    class IMPROC_EXPORTS InfrastructureLogger : public LoggerSingleton<InfrastructureLogger>
    {
        friend std::shared_ptr<InfrastructureLogger> LoggerSingleton::get(const std::string& logger_name);
        private:
            InfrastructureLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}

        public:
            InfrastructureLogger(InfrastructureLogger&  that) = delete;
            InfrastructureLogger(InfrastructureLogger&& that) = delete;
            void operator=(const InfrastructureLogger&  that) = delete;
            void operator=(const InfrastructureLogger&& that) = delete;
    };
}

#endif