#include <gtest/gtest.h>

#include <improc/infrastructure/logging/logger_infrastructure.hpp>

TEST(LoggerInfrastructure,TestLoggerLogging) {
    improc::InfrastructureLogger::get("infrastructure_logger");
    EXPECT_STREQ(improc::InfrastructureLogger::get()->data()->name().c_str(),"infrastructure_logger");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Test {} {}",1,2);
    IMPROC_INFRASTRUCTURE_LOGGER_DEBUG("Test {} {}",2,3);
    IMPROC_INFRASTRUCTURE_LOGGER_INFO ("Test {} {}",3,4);
    IMPROC_INFRASTRUCTURE_LOGGER_ERROR("Test {} {}",4,5);
    IMPROC_INFRASTRUCTURE_LOGGER_WARN ("Test {} {}",5,6);
    IMPROC_INFRASTRUCTURE_LOGGER_CRITICAL("Test {} {}",6,7);
}
