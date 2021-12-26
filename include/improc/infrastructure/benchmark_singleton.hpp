#ifndef IMPROC_INFRASTRUCTURE_BENCHMARK_SINGLETON_HPP
#define IMPROC_INFRASTRUCTURE_BENCHMARK_SINGLETON_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logger_singleton.hpp>
#include <improc/infrastructure/logger_infrastructure.hpp>

#include <unordered_set>

namespace improc 
{
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
            bool                                        is_created_;
            std::unordered_set<std::string>             keys_;
            std::unordered_map<std::string,std::string> line_content_;

        protected:
            BenchmarkSingleton(std::shared_ptr<spdlog::logger>&&      benchmark_logger);
            BenchmarkSingleton(const std::shared_ptr<spdlog::logger>& benchmark_logger);
            
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

#include <benchmark_singleton.tpp>

#endif