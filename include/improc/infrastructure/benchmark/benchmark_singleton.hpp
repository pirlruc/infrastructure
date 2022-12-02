#ifndef IMPROC_INFRASTRUCTURE_BENCHMARK_SINGLETON_HPP
#define IMPROC_INFRASTRUCTURE_BENCHMARK_SINGLETON_HPP

#include <improc/exception.hpp>
#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_singleton.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>

#include <unordered_set>

namespace improc 
{
    /**
     * @brief Singleton template for benchmarks
     * It considers a specific pattern to create the information to write on the
     * benchmark: logger_name and message. 
     * 
     * @tparam BenchmarkType - Data type of the benchmark being created
     */
    template <typename BenchmarkType>
    class IMPROC_API BenchmarkSingleton : public LoggerSingleton<BenchmarkType>
    {
        private:
            bool                                        is_created_;
            std::unordered_set<std::string>             keys_;
            std::unordered_map<std::string,std::string> line_content_;

        protected:
            explicit BenchmarkSingleton(std::shared_ptr<spdlog::logger>&&      benchmark_logger);
            explicit BenchmarkSingleton(const std::shared_ptr<spdlog::logger>& benchmark_logger);
            
        public:
            BenchmarkSingleton(BenchmarkSingleton&    that) = delete;
            BenchmarkSingleton(BenchmarkSingleton&&   that) = delete;
            void operator=(const BenchmarkSingleton&  that) = delete;
            void operator=(const BenchmarkSingleton&& that) = delete;

            BenchmarkSingleton&         AddKeys         (const std::unordered_set<std::string>& keys);
            BenchmarkSingleton&         WriteLine       ();

            template<typename ContentType>
            BenchmarkSingleton&         SetKeyContent   (const std::string& key, const ContentType& content);

        private:
            BenchmarkSingleton&         WriteHeader          ();
            BenchmarkSingleton&         WriteContent         ();
            BenchmarkSingleton&         WriteLineOnBenchmark (const std::string& line);
            BenchmarkSingleton&         InitializeLineContent(const std::unordered_set<std::string>& keys);
    };
}

#ifdef IMPROC_BENCHMARK_DISABLED
#    define IMPROC_BENCHMARK_SET_CONTENT(benchmark, key, content)  (void)0
#    define IMPROC_BENCHMARK_WRITE_LINE(benchmark)                 (void)0
#else
#    define IMPROC_BENCHMARK_SET_CONTENT(benchmark, key, content)  (benchmark)->SetKeyContent(key,content)
#    define IMPROC_BENCHMARK_WRITE_LINE(benchmark)                 (benchmark)->WriteLine()
#endif

#include <improc/infrastructure/benchmark/benchmark_singleton.tpp>

#endif