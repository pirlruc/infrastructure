#ifndef IMPROC_INFRASTRUCTURE_LOGGER_SINGLETON_HPP
#define IMPROC_INFRASTRUCTURE_LOGGER_SINGLETON_HPP

#include <improc/improc_defs.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <type_traits>

namespace improc 
{
    /**
     * @brief Singleton template for loggers
     * 
     * @tparam LoggerType - Data type of the logger being created
     */
    template <typename LoggerType>
    class IMPROC_API LoggerSingleton
    {
        private:
            std::shared_ptr<spdlog::logger> data_;

        protected:
            explicit LoggerSingleton(std::shared_ptr<spdlog::logger>&&       logger);
            explicit LoggerSingleton(const std::shared_ptr<spdlog::logger>&  logger);
    
        public:
            LoggerSingleton(LoggerSingleton&        that) = delete;
            LoggerSingleton(LoggerSingleton&&       that) = delete;
            void operator= (const LoggerSingleton&  that) = delete;
            void operator= (const LoggerSingleton&& that) = delete;

            static std::shared_ptr<LoggerType>  get(const std::string& logger_name = "");
            std::shared_ptr<spdlog::logger>     data() const;
    };
}

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define IMPROC_LOGGER_TRACE(logger_singleton, ...) SPDLOG_LOGGER_TRACE((logger_singleton)->data(), __VA_ARGS__)
#else
#    define IMPROC_LOGGER_TRACE(logger_singleton, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define IMPROC_LOGGER_DEBUG(logger_singleton, ...) SPDLOG_LOGGER_DEBUG((logger_singleton)->data(), __VA_ARGS__)
#else
#    define IMPROC_LOGGER_DEBUG(logger_singleton, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define IMPROC_LOGGER_INFO(logger_singleton, ...) SPDLOG_LOGGER_INFO((logger_singleton)->data(), __VA_ARGS__)
#else
#    define IMPROC_LOGGER_INFO(logger_singleton, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define IMPROC_LOGGER_WARN(logger_singleton, ...) SPDLOG_LOGGER_WARN((logger_singleton)->data(), __VA_ARGS__)
#else
#    define IMPROC_LOGGER_WARN(logger_singleton, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define IMPROC_LOGGER_ERROR(logger_singleton, ...) SPDLOG_LOGGER_ERROR((logger_singleton)->data(), __VA_ARGS__)
#else
#    define IMPROC_LOGGER_ERROR(logger_singleton, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define IMPROC_LOGGER_CRITICAL(logger_singleton, ...) SPDLOG_LOGGER_CRITICAL((logger_singleton)->data(), __VA_ARGS__)
#else
#    define IMPROC_LOGGER_CRITICAL(logger_singleton, ...) (void)0
#endif

#include <improc/infrastructure/logging/logger_singleton.tpp>

#endif