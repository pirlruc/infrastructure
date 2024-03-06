#ifndef IMPROC_INFRASTRUCTURE_EXCEPTIONS_HPP
#define IMPROC_INFRASTRUCTURE_EXCEPTIONS_HPP
 
#include <stdexcept>
 
/**
 * @brief Image processing library namespace.
 */
namespace improc 
{
    /** @defgroup exceptions Exceptions
     *  Exceptions defined in the image processing library
     *  @{
     */

    /**
     * @brief Raised when a mapping key is not found in the set of existing keys or an invalid operation in the keys is performed.
     */
    class key_error final: public std::logic_error
    {
        public:
            explicit key_error(const std::string& message): std::logic_error(std::move(message)) {}
    };

    /**
     * @brief Raised when an operation or function receives an argument that has the right type but an inappropriate value.
     */
    class value_error final: public std::logic_error
    {
        public:
            explicit value_error(const std::string& message): std::logic_error(std::move(message)) {}
    };

    /**
     * @brief Raised when a parser encounters a syntax error.
     */
    class syntax_error final: public std::runtime_error
    {
        public:
            explicit syntax_error(const std::string& message): std::runtime_error(std::move(message)) {}
    };

    /**
     * @brief Raised when a system function returns a system-related error, including I/O failures.
     */
    class operating_system_error final: public std::runtime_error
    {
        public:
            explicit operating_system_error(const std::string& message): std::runtime_error(std::move(message)) {}
    };

    class processing_flow_error final: public std::logic_error
    {
        public:
            explicit processing_flow_error(const std::string& message): std::logic_error(std::move(message)) {}
    };

    class freetype_error final: public std::runtime_error
    {
        public:
            explicit freetype_error(const std::string& message): std::runtime_error(std::move(message)) {}
    };


    class inconsistent_size_detected_reference_pixels final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Detected pixels and reference pixels with different sizes";
        }
    };

    class inconsistent_size_pixels_lines final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Pixels and lines for homography estimation with different sizes";
        }
    };

    class invalid_svd_decomposition final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid SVD decomposition";
        }
    };

    class invalid_homography_estimation final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Homography cannot be estimated";
        }
    };

    /** @} */ // end of exceptions
}
 
#endif