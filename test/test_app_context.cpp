#include <gtest/gtest.h>

#include <improc/infrastructure/context/application_context.hpp>

TEST(ApplicationContext,TestDefaultContext) {
    EXPECT_NO_THROW(improc::ApplicationContext::get());
    EXPECT_TRUE(improc::ApplicationContext::get()->get_application_folder().empty());
}

TEST(ApplicationContext,TestGetAndSetContext) {
    improc::ApplicationContext::get()->set_application_folder("test");
    EXPECT_EQ(improc::ApplicationContext::get()->get_application_folder(),"test");
}
