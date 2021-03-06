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

    class not_found_in_factory : public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Unknown object type passed to factory.";
            }
    };

    class invalid_filepath: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid filepath";
        }
    };

    class invalid_folder_path: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid folder path";
        }
    };

    class file_processing_error: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error processing file";
        }
    };

    class json_parsing_error: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error parsing json structure";
        }
    };

    class not_supported_data_type: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Not supported data type";
        }
    };

    class benchmark_keys_cannot_change: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Cannot change benchmark keys after creation";
        }
    };

    class drawer_not_defined: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Drawer not defined";
        }
    };

    class page_drawer_not_allocated: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Page drawer not allocated";
        }
    };

    class invalid_page_image: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Invalid page image";
        }
    };

    class context_elem_diff_page_elem: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Number of context elements different than the number of page elements";
        }
    };

    class freetype_lib_error: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error executing freetype library method";
        }
    };

    class printing_resolution_not_positive: public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Printing resolution should be bigger than zero";
        }
    };
}
 
#endif