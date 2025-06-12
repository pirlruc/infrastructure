#ifndef IMPROC_FILE_CONTENT_TYPE_HPP
#define IMPROC_FILE_CONTENT_TYPE_HPP

#include <improc/improc_defs.hpp>
#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/infrastructure/string.hpp>

namespace improc
{
    /**
     * @brief Enumeration class for supported file content types
     *
     */
    class IMPROC_API FileContentType final
    {
        public:
            /**
             * @brief Supported file content types:
             *  kJson   - Json content (structured nested content)
             *  kBinary - Binary content
             */
            enum Value : IMPROC_ENUM_KEY_TYPE
            {
                kJSON   = 1,
                kBinary = 2,
            };

        private:
            Value                           value_;

        public:
            FileContentType();
            explicit FileContentType(const std::string &file_content_type_str);

            /**
             * @brief Construct a new improc::FileContentType object
             *
             * @param file_type_value - file type value
             */
            constexpr explicit              FileContentType(Value file_type_value)
                : value_(std::move(file_type_value)) {}

            /**
             * @brief Obtain file content type value
             */
            constexpr operator              Value() const { return this->value_; }

            /**
             * @brief Obtain file type string description
             */
            constexpr std::string_view      ToString() const
            {
                switch (this->value_)
                {
                case FileContentType::Value::kJSON  : return "JSON";   break;
                case FileContentType::Value::kBinary: return "Binary"; break;
                default:
                    throw improc::key_error("ToString method not defined for file content type enum");
                }
            }
    };
}

#endif