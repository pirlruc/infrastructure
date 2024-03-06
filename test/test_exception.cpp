#include <gtest/gtest.h>

#include <improc/exception.hpp>

TEST(Exception,TestExceptions) {
    EXPECT_THROW(throw improc::value_error("test"),improc::value_error);
    EXPECT_THROW(throw improc::processing_flow_error("test"),improc::processing_flow_error);
    EXPECT_THROW(throw improc::key_error("test"),improc::key_error);
    EXPECT_THROW(throw improc::operating_system_error("test"),improc::operating_system_error);
    EXPECT_THROW(throw improc::syntax_error("test"),improc::syntax_error);
    EXPECT_THROW(throw improc::freetype_error("test"),improc::freetype_error);

    EXPECT_THROW(throw improc::inconsistent_size_detected_reference_pixels(),improc::inconsistent_size_detected_reference_pixels);
    EXPECT_THROW(throw improc::inconsistent_size_pixels_lines(),improc::inconsistent_size_pixels_lines);
    EXPECT_THROW(throw improc::invalid_svd_decomposition(),improc::invalid_svd_decomposition);
    EXPECT_THROW(throw improc::invalid_homography_estimation(),improc::invalid_homography_estimation);
}