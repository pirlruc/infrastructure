#ifndef IMPROC_INFRASTRUCTURE_LOGGER_INFRASTRUCTURE_HPP
#define IMPROC_INFRASTRUCTURE_LOGGER_INFRASTRUCTURE_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_singleton.hpp>

namespace improc 
{
    /**
     * @brief Logger used for infrastructure library
     * 
     */
    class IMPROC_API InfrastructureLogger final : public LoggerSingleton<InfrastructureLogger>
    {
        friend std::shared_ptr<InfrastructureLogger> LoggerSingleton::get(const std::string& logger_name);
        private:
            explicit InfrastructureLogger(std::shared_ptr<spdlog::logger>&&      logger) : LoggerSingleton(std::move(logger)) {}

        public:
            InfrastructureLogger(InfrastructureLogger&  that) = delete;
            InfrastructureLogger(InfrastructureLogger&& that) = delete;
            void operator=(const InfrastructureLogger&  that) = delete;
            void operator=(const InfrastructureLogger&& that) = delete;
    };
}

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define IMPROC_INFRASTRUCTURE_LOGGER_TRACE(...) IMPROC_LOGGER_TRACE(improc::InfrastructureLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_INFRASTRUCTURE_LOGGER_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define IMPROC_INFRASTRUCTURE_LOGGER_DEBUG(...) IMPROC_LOGGER_DEBUG(improc::InfrastructureLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_INFRASTRUCTURE_LOGGER_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define IMPROC_INFRASTRUCTURE_LOGGER_INFO(...) IMPROC_LOGGER_INFO(improc::InfrastructureLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_INFRASTRUCTURE_LOGGER_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define IMPROC_INFRASTRUCTURE_LOGGER_WARN(...) IMPROC_LOGGER_WARN(improc::InfrastructureLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_INFRASTRUCTURE_LOGGER_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define IMPROC_INFRASTRUCTURE_LOGGER_ERROR(...) IMPROC_LOGGER_ERROR(improc::InfrastructureLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_INFRASTRUCTURE_LOGGER_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define IMPROC_INFRASTRUCTURE_LOGGER_CRITICAL(...) IMPROC_LOGGER_CRITICAL(improc::InfrastructureLogger::get(), __VA_ARGS__)
#else
#    define IMPROC_INFRASTRUCTURE_LOGGER_CRITICAL(...) (void)0
#endif

#endif