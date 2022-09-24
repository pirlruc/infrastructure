#ifndef IMPROC_INFRASTRUCTURE_DEFINITIONS_HPP
#define IMPROC_INFRASTRUCTURE_DEFINITIONS_HPP

#ifndef IMPROC_API
    #if defined _WIN32 || defined WINCE
        #define IMPROC_API __declspec(dllexport)
    #elif defined __GNUC__ && __GNUC__ >= 4 || defined __APPLE__
        #define IMPROC_API __attribute__ ((visibility ("default")))
    #else
        #define IMPROC_API
    #endif
#else
    #if defined _WIN32 || defined WINCE
        #define IMPROC_API __declspec(dllimport)
    #endif
#endif

#define IMPROC_ENUM_KEY_TYPE unsigned int

#endif