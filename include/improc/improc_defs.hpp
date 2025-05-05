#ifndef IMPROC_INFRASTRUCTURE_DEFINITIONS_HPP
#define IMPROC_INFRASTRUCTURE_DEFINITIONS_HPP

#if defined(IMPROC_STATIC)
    #define IMPROC_API
#elif defined(_WIN32) || defined(_WIN64) || defined(WINCE)
    #if defined(IMPROC_EXPORTS)     // Building the DLL
        #define IMPROC_API __declspec(dllexport)
    #else                           // Using the DLL
        #define IMPROC_API __declspec(dllimport)
    #endif
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
    #define IMPROC_API __attribute__ ((visibility ("default")))
#else
    #define IMPROC_API
#endif

#define IMPROC_ENUM_KEY_TYPE unsigned int
#define IMPROC_FWD(value) std::forward<decltype(value)>(value)

#endif