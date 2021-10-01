#ifndef IMPROC_INFRASTRUCTURE_STRING_HPP
#define IMPROC_INFRASTRUCTURE_STRING_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logger_infrastructure.hpp>

#include <string>
#include <boost/algorithm/string.hpp>

namespace improc {
    /**
     * @brief String object and utilities
     * 
     */
    class IMPROC_EXPORTS String
    {
        private:
            std::string                 data_;

        public:
            String();
            String(const std::string& str_data);

            void                        set_string(const std::string& str_data);
            std::string                 get_data() const;

            void                        ToLower();
            void                        ToUpper();

            static const std::string    ToLower(const std::string& upper_str);
            static const std::string    ToUpper(const std::string& lower_str);
    };
}

#endif