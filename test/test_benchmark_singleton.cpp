#include <gtest/gtest.h>

#include <improc/infrastructure/filesystem/file.hpp>
#include <improc/infrastructure/benchmark/benchmark_singleton.hpp>

#include <spdlog/sinks/basic_file_sink.h>

class TestBenchmarkReference : public improc::BenchmarkSingleton<TestBenchmarkReference>
{
    friend std::shared_ptr<TestBenchmarkReference> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkReference(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkReferenceKeys : public improc::BenchmarkSingleton<TestBenchmarkReferenceKeys>
{
    friend std::shared_ptr<TestBenchmarkReferenceKeys> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkReferenceKeys(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkMove : public improc::BenchmarkSingleton<TestBenchmarkMove>
{
    friend std::shared_ptr<TestBenchmarkMove> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkMove(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkDiff : public improc::BenchmarkSingleton<TestBenchmarkDiff>
{
    friend std::shared_ptr<TestBenchmarkDiff> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkDiff(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

class TestBenchmarkMacro : public improc::BenchmarkSingleton<TestBenchmarkMacro>
{
    friend std::shared_ptr<TestBenchmarkMacro> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestBenchmarkMacro(std::shared_ptr<spdlog::logger>&& logger) : BenchmarkSingleton(std::move(logger)) {}
};

TEST(Benchmark,TestBenchmarkLevelAndPattern) {
    improc::File::Remove("./benchmark_level_pattern.csv");
    spdlog::basic_logger_st("benchmark1","./benchmark_level_pattern.csv");
    TestBenchmarkReference::get("benchmark1")->WriteLine();
    TestBenchmarkReference::get()->data()->flush();
    EXPECT_EQ(TestBenchmarkReference::get()->data()->level(),spdlog::level::critical);
    #if defined _WIN32 || defined _WIN64 || defined _WIN32_WCE
        EXPECT_STREQ(improc::File::Read("./benchmark_level_pattern.csv").c_str(),"benchmark1;\r\nbenchmark1;\r\n");
    #else
        EXPECT_STREQ(improc::File::Read("./benchmark_level_pattern.csv").c_str(),"benchmark1;\nbenchmark1;\n");
    #endif
    spdlog::drop("benchmark1");
}

TEST(Benchmark,TestBenchmarkKeys) {
    improc::File::Remove("./benchmark_keys.csv");
    spdlog::basic_logger_st("benchmark2","./benchmark_keys.csv");
    std::unordered_set<std::string> keys {"test1","test2"};
    TestBenchmarkReferenceKeys::get("benchmark2")->AddKeys(keys);
    TestBenchmarkReferenceKeys::get()->SetKeyContent("test1",true);
    TestBenchmarkReferenceKeys::get()->WriteLine();
    TestBenchmarkReferenceKeys::get()->data()->flush();
    EXPECT_EQ(TestBenchmarkReferenceKeys::get()->data()->level(),spdlog::level::critical);
    #if defined _WIN32 || defined _WIN64 || defined _WIN32_WCE
        EXPECT_STREQ(improc::File::Read("./benchmark_keys.csv").c_str(),"benchmark2;test1;test2\r\nbenchmark2;true;\r\n");
    #else
        EXPECT_STREQ(improc::File::Read("./benchmark_keys.csv").c_str(),"benchmark2;test1;test2\nbenchmark2;true;\n");
    #endif
    EXPECT_THROW(TestBenchmarkReferenceKeys::get()->AddKeys(keys),improc::benchmark_keys_cannot_change);
    spdlog::drop("benchmark2");
}

TEST(Benchmark,TestBenchmarkWriteSameTypeFields) {
    improc::File::Remove("./benchmark_write_same_type_fields.csv");
    spdlog::basic_logger_st("benchmark3","./benchmark_write_same_type_fields.csv");
    std::unordered_set<std::string> keys {"test1","test2"};
    TestBenchmarkMove::get("benchmark3")->AddKeys(keys);
    EXPECT_NO_THROW (
        TestBenchmarkMove::get()->SetKeyContent("test1",1);
        TestBenchmarkMove::get()->SetKeyContent("test2",2);
        TestBenchmarkMove::get()->WriteLine();
        TestBenchmarkMove::get()->WriteLine();
    );
    TestBenchmarkMove::get()->data()->flush();
    #if defined _WIN32 || defined _WIN64 || defined _WIN32_WCE
        EXPECT_STREQ(improc::File::Read("./benchmark_write_same_type_fields.csv").c_str(),"benchmark3;test1;test2\r\nbenchmark3;1;2\r\nbenchmark3;;\r\n");
    #else
        EXPECT_STREQ(improc::File::Read("./benchmark_write_same_type_fields.csv").c_str(),"benchmark3;test1;test2\nbenchmark3;1;2\nbenchmark3;;\n");
    #endif
    spdlog::drop("benchmark3");
}

TEST(Benchmark,TestBenchmarkWriteDiffTypeFields) {
    improc::File::Remove("./benchmark_write_diff_type_fields.csv");
    spdlog::basic_logger_st("benchmark4","./benchmark_write_diff_type_fields.csv");
    std::unordered_set<std::string> keys_1 {"test1","test2"};
    std::unordered_set<std::string> keys_2 {"test3"};
    TestBenchmarkDiff::get("benchmark4")->AddKeys(keys_1);
    TestBenchmarkDiff::get()->AddKeys(keys_2);
    EXPECT_NO_THROW (
        TestBenchmarkDiff::get()->SetKeyContent("test1",false);
        TestBenchmarkDiff::get()->SetKeyContent("test2",3.14);
        TestBenchmarkDiff::get()->SetKeyContent("test3","test");
        TestBenchmarkDiff::get()->WriteLine();
    );
    TestBenchmarkDiff::get()->data()->flush();
    #if defined _WIN32 || defined _WIN64 || defined _WIN32_WCE
        // Ordering is different between windows and linux since the unordered_set std::hash is different
        EXPECT_FALSE(improc::File::Read("./benchmark_write_diff_type_fields.csv").empty());
    #else
        EXPECT_STREQ(improc::File::Read("./benchmark_write_diff_type_fields.csv").c_str(),"benchmark4;test3;test1;test2\nbenchmark4;test;false;3.14\n");
    #endif
    spdlog::drop("benchmark4");
}

TEST(Benchmark,TestBenchmarkWriteWithMacros) {
    improc::File::Remove("./benchmark_write_with_macros.csv");
    spdlog::basic_logger_st("benchmark5","./benchmark_write_with_macros.csv");
    std::unordered_set<std::string> keys_1 {"test1","test2"};
    std::unordered_set<std::string> keys_2 {"test3"};
    TestBenchmarkMacro::get("benchmark5")->AddKeys(keys_1);
    TestBenchmarkMacro::get()->AddKeys(keys_2);
    EXPECT_NO_THROW (
        IMPROC_BENCHMARK_SET_CONTENT(TestBenchmarkMacro::get(),"test1",false);
        IMPROC_BENCHMARK_SET_CONTENT(TestBenchmarkMacro::get(),"test2",3.14);
        IMPROC_BENCHMARK_SET_CONTENT(TestBenchmarkMacro::get(),"test3","macro");
        IMPROC_BENCHMARK_WRITE_LINE (TestBenchmarkMacro::get());
    );
    TestBenchmarkMacro::get()->data()->flush();
   #if defined _WIN32 || defined _WIN64 || defined _WIN32_WCE
        // Ordering is different between windows and linux since the unordered_set std::hash is different
        EXPECT_FALSE(improc::File::Read("./benchmark_write_with_macros.csv").empty());
    #else
        EXPECT_STREQ(improc::File::Read("./benchmark_write_with_macros.csv").c_str(),"benchmark5;test3;test1;test2\nbenchmark5;macro;false;3.14\n");
    #endif
    spdlog::drop("benchmark5");
}
