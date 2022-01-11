#include <gtest/gtest.h>

#include <improc/infrastructure/context/environment_context.hpp>

class TestEnvironmentGet : public improc::EnvironmentContext<TestEnvironmentGet>
{
    friend std::shared_ptr<TestEnvironmentGet> EnvironmentContext::get();
    public:
        bool created = true;
    
    private:
        TestEnvironmentGet() : EnvironmentContext() {}
};

class TestEnvironmentSet : public improc::EnvironmentContext<TestEnvironmentSet>
{
    friend std::shared_ptr<TestEnvironmentSet> EnvironmentContext::get();
    public:
        bool created = true;
    
    private:
        TestEnvironmentSet() : EnvironmentContext() {}
};

TEST(EnvironmentContext,TestGetEnvironmentContext) {
    EXPECT_NO_THROW(TestEnvironmentGet::get());
    EXPECT_TRUE(TestEnvironmentGet::get()->created);
}


TEST(EnvironmentContext,TestSetEnvironmentContext) {
    TestEnvironmentSet::get()->created = false;
    EXPECT_FALSE(TestEnvironmentSet::get()->created);
}
