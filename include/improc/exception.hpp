#ifndef IMPROC_INFRASTRUCTURE_EXCEPTIONS_HPP
#define IMPROC_INFRASTRUCTURE_EXCEPTIONS_HPP
 
#include <stdexcept>
 
namespace improc 
{
    class key_error final: public std::runtime_error
    {
        public:
            explicit key_error(const std::string& message): std::runtime_error(std::move(message)) {}
    };

    class value_error final: public std::logic_error
    {
        public:
            explicit value_error(const std::string& message): std::logic_error(std::move(message)) {}
    };

    class operating_system_error final: public std::runtime_error
    {
        public:
            explicit operating_system_error(const std::string& message): std::runtime_error(std::move(message)) {}
    };

    class json_error final: public std::runtime_error
    {
        public:
            explicit json_error(const std::string& message): std::runtime_error(std::move(message)) {}
    };

    class duplicated_key final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Key already exists";
        }
    };

    class not_found_key final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Key does not exist";
        }
    };

    class not_found_in_factory final: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Unknown object type passed to factory.";
            }
    };

    class file_processing_error final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error processing file";
        }
    };

    class not_supported_data_type final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Not supported data type";
        }
    };

    class drawer_not_defined final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Drawer not defined";
        }
    };

    class page_drawer_not_allocated final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Page drawer not allocated";
        }
    };

    class invalid_page_image final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid page image";
        }
    };

    class context_elem_diff_page_elem final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Number of context elements different than the number of page elements";
        }
    };

    class freetype_lib_error final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error executing freetype library method";
        }
    };

    class printing_resolution_not_positive final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Printing resolution should be bigger than zero";
        }
    };

    class not_supported_color_conversion final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Not supported color conversion";
        }
    };

    class invalid_color_space final: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid color space";
        }
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
}
 
#endif