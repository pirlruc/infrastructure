#ifndef IMPROC_INFRASTRUCTURE_BENCHMARK_SINGLETON_HPP
#define IMPROC_INFRASTRUCTURE_BENCHMARK_SINGLETON_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logger_singleton.hpp>
#include <improc/infrastructure/logger_infrastructure.hpp>

namespace improc {
    /**
     * @brief Singleton template for benchmarks
     * It considers a specific pattern to create the information to write on the
     * benchmark: logger_name and message. 
     * 
     * @tparam type 
     */
    template <typename type>
    class IMPROC_EXPORTS BenchmarkSingleton : public LoggerSingleton<type>
    {
        private:
            std::string                         line_msg_;

        protected:
            BenchmarkSingleton(std::shared_ptr<spdlog::logger>&&      benchmark_logger);
            BenchmarkSingleton(const std::shared_ptr<spdlog::logger>& benchmark_logger);
            
        public:
            BenchmarkSingleton(BenchmarkSingleton&  that)   = delete;
            BenchmarkSingleton(BenchmarkSingleton&& that)   = delete;
            void operator=(const BenchmarkSingleton&  that) = delete;
            void operator=(const BenchmarkSingleton&& that) = delete;

            void                                AddFieldsToLine ();
            void                                WriteFields     ();
            void                                WriteLine       ();

            template<typename arg, typename ... args>
            void                                AddFieldsToLine (arg field_1, args ... field_n);

            template<typename arg, typename ... args>
            void                                WriteFields     (arg field_1, args ... field_n);
    };
}

#include <benchmark_singleton.tpp>

#endif