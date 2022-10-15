#include <gtest/gtest.h>

#include <improc/infrastructure/logging/logger_singleton.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>

class TestLoggerReference : public improc::LoggerSingleton<TestLoggerReference>
{
    friend std::shared_ptr<TestLoggerReference> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestLoggerReference(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(logger) {}
};

class TestLoggerMove : public improc::LoggerSingleton<TestLoggerMove>
{
    friend std::shared_ptr<TestLoggerMove> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestLoggerMove(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

class TestExistingLogger : public improc::LoggerSingleton<TestExistingLogger>
{
    friend std::shared_ptr<TestExistingLogger> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestExistingLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

class TestDoubleLogger : public improc::LoggerSingleton<TestDoubleLogger>
{
    friend std::shared_ptr<TestDoubleLogger> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestDoubleLogger(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

class TestLogging : public improc::LoggerSingleton<TestLogging>
{
    friend std::shared_ptr<TestLogging> LoggerSingleton::get(const std::string& logger_name);
    private:
        TestLogging(std::shared_ptr<spdlog::logger>&& logger) : LoggerSingleton(std::move(logger)) {}
};

TEST(Logger,TestLogging) {
    EXPECT_NO_THROW (
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%-5l] [%@ >> %!] %v");
        spdlog::set_level(spdlog::level::level_enum::trace);
    );
}

TEST(Logger,TestLoggerDefaultConstructor) {
    EXPECT_STREQ(spdlog::default_logger()->name().c_str(),TestLoggerReference::get()->data()->name().c_str());
}

TEST(Logger,TestLoggerNonExistingConstructor) {
    TestLoggerMove::get("specific_logger");
    EXPECT_TRUE(spdlog::get("specific_logger") != nullptr);
    EXPECT_STREQ(TestLoggerMove::get()->data()->name().c_str(),"specific_logger");
}

TEST(Logger,TestLoggerExistingConstructor) {
    spdlog::stdout_color_st("console_logger");
    TestExistingLogger::get("console_logger");
    EXPECT_STREQ(TestExistingLogger::get()->data()->name().c_str(),"console_logger");
}

TEST(Logger,TestLoggerDoubleConstructor) {
    TestDoubleLogger::get("logger_console_1");
    EXPECT_STREQ(TestDoubleLogger::get()->data()->name().c_str(),"logger_console_1");
    TestDoubleLogger::get("logger_console_2");
    EXPECT_STREQ(TestDoubleLogger::get()->data()->name().c_str(),"logger_console_1");
    EXPECT_TRUE(spdlog::get("logger_console_1") != nullptr);
    EXPECT_TRUE(spdlog::get("logger_console_2") == nullptr);
}

TEST(Logger,TestLoggerLogging) {
    TestLogging::get("log_console");
    EXPECT_STREQ(TestLogging::get()->data()->name().c_str(),"log_console");
    IMPROC_LOGGER_TRACE(TestLogging::get(),"Test {} {}",1,2);
    IMPROC_LOGGER_DEBUG(TestLogging::get(),"Test {} {}",2,3);
    IMPROC_LOGGER_INFO (TestLogging::get(),"Test {} {}",3,4);
    IMPROC_LOGGER_ERROR(TestLogging::get(),"Test {} {}",4,5);
    IMPROC_LOGGER_WARN (TestLogging::get(),"Test {} {}",5,6);
    IMPROC_LOGGER_CRITICAL(TestLogging::get(),"Test {} {}",6,7);
}
