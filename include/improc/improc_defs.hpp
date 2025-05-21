#ifndef IMPROC_INFRASTRUCTURE_DEFINITIONS_HPP
#define IMPROC_INFRASTRUCTURE_DEFINITIONS_HPP

#if defined(IMPROC_STATIC)
    #define IMPROC_API
    #define IMPROC_EXPORT_TEMPLATE_DECLARATION
    #define IMPROC_EXPORT_TEMPLATE_DEFINITION
#elif defined(_WIN32) || defined(_WIN64) || defined(WINCE)
    #if defined(IMPROC_EXPORTS)     // Building the DLL
        #define IMPROC_API __declspec(dllexport)
        #define IMPROC_EXPORT_TEMPLATE_DECLARATION
        #define IMPROC_EXPORT_TEMPLATE_DEFINITION IMPROC_API
    #else                           // Using the DLL
        #define IMPROC_API __declspec(dllimport)
        #define IMPROC_EXPORT_TEMPLATE_DECLARATION IMPROC_API
        #define IMPROC_EXPORT_TEMPLATE_DEFINITION
    #endif
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
    #define IMPROC_API __attribute__ ((visibility ("default")))
    #define IMPROC_EXPORT_TEMPLATE_DECLARATION IMPROC_API
    #define IMPROC_EXPORT_TEMPLATE_DEFINITION
#else
    #define IMPROC_API
    #define IMPROC_EXPORT_TEMPLATE_DECLARATION
    #define IMPROC_EXPORT_TEMPLATE_DEFINITION
#endif

#define IMPROC_ENUM_KEY_TYPE unsigned int
#define IMPROC_FWD(value) std::forward<decltype(value)>(value)

#endif