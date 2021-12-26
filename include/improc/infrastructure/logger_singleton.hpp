#ifndef IMPROC_INFRASTRUCTURE_LOGGER_SINGLETON_HPP
#define IMPROC_INFRASTRUCTURE_LOGGER_SINGLETON_HPP

#include <improc/improc_defs.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace improc 
{
    /**
     * @brief Singleton template for loggers
     * 
     * @tparam LoggerType 
     */
    template <typename LoggerType>
    class IMPROC_EXPORTS LoggerSingleton
    {
        private:
            std::shared_ptr<spdlog::logger> data_;

        protected:
            LoggerSingleton(std::shared_ptr<spdlog::logger>&&       logger);
            LoggerSingleton(const std::shared_ptr<spdlog::logger>&  logger);
    
        public:
            LoggerSingleton(LoggerSingleton&        that) = delete;
            LoggerSingleton(LoggerSingleton&&       that) = delete;
            void operator= (const LoggerSingleton&  that) = delete;
            void operator= (const LoggerSingleton&& that) = delete;

            static std::shared_ptr<LoggerType>  get(const std::string& logger_name = "");
            std::shared_ptr<spdlog::logger>     data() const;
    };
}

#include <logger_singleton.tpp>

#endif