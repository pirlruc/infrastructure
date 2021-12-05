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
     * @tparam BenchmarkType 
     */
    template <typename BenchmarkType>
    class IMPROC_EXPORTS BenchmarkSingleton : public LoggerSingleton<BenchmarkType>
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

            BenchmarkSingleton&                 AddFieldsToLine ();
            BenchmarkSingleton&                 WriteFields     ();
            BenchmarkSingleton&                 WriteLine       ();

            template<typename Arg, typename ... Args>
            BenchmarkSingleton&                 AddFieldsToLine (Arg field_1, Args ... field_n);

            template<typename Arg, typename ... Args>
            BenchmarkSingleton&                 WriteFields     (Arg field_1, Args ... field_n);
    };
}

#include <benchmark_singleton.tpp>

#endif