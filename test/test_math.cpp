#include <gtest/gtest.h>

#include <improc/infrastructure/math.hpp>

TEST(MathUtils,TestEven) {
    EXPECT_TRUE(improc::math::IsEven<int>(2));
    EXPECT_TRUE(improc::math::IsEven<unsigned int>(2));
    EXPECT_TRUE(improc::math::IsEven<size_t>(2));
    EXPECT_FALSE(improc::math::IsEven<int>(3));
    EXPECT_FALSE(improc::math::IsEven<unsigned int>(3));
    EXPECT_FALSE(improc::math::IsEven<size_t>(3));
}

TEST(MathUtils,TestOdd) {
    EXPECT_FALSE(improc::math::IsOdd<int>(2));
    EXPECT_FALSE(improc::math::IsOdd<unsigned int>(2));
    EXPECT_FALSE(improc::math::IsOdd<size_t>(2));
    EXPECT_TRUE(improc::math::IsOdd<int>(3));
    EXPECT_TRUE(improc::math::IsOdd<unsigned int>(3));
    EXPECT_TRUE(improc::math::IsOdd<size_t>(3));
}
