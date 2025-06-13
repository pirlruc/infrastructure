#include <gtest/gtest.h>

#include <improc/exception.hpp>

TEST(Exception,TestExceptions) {
    EXPECT_THROW(throw improc::value_error("test"),improc::value_error);
    EXPECT_THROW(throw improc::processing_flow_error("test"),improc::processing_flow_error);
    EXPECT_THROW(throw improc::key_error("test"),improc::key_error);
    EXPECT_THROW(throw improc::operating_system_error("test"),improc::operating_system_error);
    EXPECT_THROW(throw improc::json_error("test"),improc::json_error);
    EXPECT_THROW(throw improc::freetype_error("test"),improc::freetype_error);
    EXPECT_THROW(throw improc::opencv_error ("test"),improc::opencv_error );

    EXPECT_THROW(throw improc::inconsistent_size_detected_reference_pixels(),improc::inconsistent_size_detected_reference_pixels);
    EXPECT_THROW(throw improc::inconsistent_size_pixels_lines(),improc::inconsistent_size_pixels_lines);
    EXPECT_THROW(throw improc::invalid_svd_decomposition(),improc::invalid_svd_decomposition);
    EXPECT_THROW(throw improc::invalid_homography_estimation(),improc::invalid_homography_estimation);
}

TEST(Exception, TestInconsistentSizeDetectedReferencePixels) {
    try {
        throw improc::inconsistent_size_detected_reference_pixels();
    } 
    catch (const improc::inconsistent_size_detected_reference_pixels& e) {
        EXPECT_STREQ("Detected pixels and reference pixels with different sizes", e.what());
    }
}

TEST(Exception, TestInconsistentSizePixelsLines) {
    try {
        throw improc::inconsistent_size_pixels_lines();
    } 
    catch (const improc::inconsistent_size_pixels_lines& e) {
        EXPECT_STREQ("Pixels and lines for homography estimation with different sizes", e.what());
    }
}

TEST(Exception, TestInvalidSvdDecomposition) {
    try {
        throw improc::invalid_svd_decomposition();
    } 
    catch (const improc::invalid_svd_decomposition& e) {
        EXPECT_STREQ("Invalid SVD decomposition", e.what());
    }
}

TEST(Exception, TestInvalidHomographyEstimation) {
    try {
        throw improc::invalid_homography_estimation();
    } 
    catch (const improc::invalid_homography_estimation& e) {
        EXPECT_STREQ("Homography cannot be estimated", e.what());
    }
}