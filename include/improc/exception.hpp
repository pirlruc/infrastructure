#ifndef IMPROC_INFRASTRUCTURE_EXCEPTIONS_HPP
#define IMPROC_INFRASTRUCTURE_EXCEPTIONS_HPP
 
#include <exception>
 
namespace improc {
    class duplicated_key: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Key already exists";
        }
    };

    class not_found_key: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Key does not exist";
        }
    };

    class invalid_filepath: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid filepath";
        }
    };

    class file_processing_error: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error processing file";
        }
    };

    class not_supported_data_type: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Not supported data type";
        }
    };
}
 
#endif