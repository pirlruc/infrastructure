#include <gtest/gtest.h>

#include <improc/exception.hpp>

TEST(Exception,TestExceptions) {
    EXPECT_THROW(throw improc::value_error("test"),improc::value_error);
    EXPECT_THROW(throw improc::key_error("test"),improc::key_error);
    EXPECT_THROW(throw improc::operating_system_error("test"),improc::operating_system_error);
    EXPECT_THROW(throw improc::json_error("test"),improc::json_error);

    EXPECT_THROW(throw improc::not_supported_data_type(),improc::not_supported_data_type);
    EXPECT_THROW(throw improc::drawer_not_defined(),improc::drawer_not_defined);
    EXPECT_THROW(throw improc::page_drawer_not_allocated(),improc::page_drawer_not_allocated);
    EXPECT_THROW(throw improc::invalid_page_image(),improc::invalid_page_image);
    EXPECT_THROW(throw improc::context_elem_diff_page_elem(),improc::context_elem_diff_page_elem);
    EXPECT_THROW(throw improc::freetype_lib_error(),improc::freetype_lib_error);
    EXPECT_THROW(throw improc::printing_resolution_not_positive(),improc::printing_resolution_not_positive);
    EXPECT_THROW(throw improc::not_supported_color_conversion(),improc::not_supported_color_conversion);
    EXPECT_THROW(throw improc::invalid_color_space(),improc::invalid_color_space);
    EXPECT_THROW(throw improc::inconsistent_size_detected_reference_pixels(),improc::inconsistent_size_detected_reference_pixels);
    EXPECT_THROW(throw improc::inconsistent_size_pixels_lines(),improc::inconsistent_size_pixels_lines);
    EXPECT_THROW(throw improc::invalid_svd_decomposition(),improc::invalid_svd_decomposition);
    EXPECT_THROW(throw improc::invalid_homography_estimation(),improc::invalid_homography_estimation);
}