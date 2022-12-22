#ifndef IMPROC_INFRASTRUCTURE_TYPE_TRAITS_HPP
#define IMPROC_INFRASTRUCTURE_TYPE_TRAITS_HPP

#include <type_traits>
#include <filesystem>

namespace improc {
    template<class>
    inline constexpr bool dependent_false_v = false;

    template <class T>
    struct is_folder_iterator : std::bool_constant<    std::is_same<T, std::filesystem::recursive_directory_iterator>::value
                                                    || std::is_same<T, std::filesystem::directory_iterator>::value > {};

    template<class T>
    inline constexpr bool is_folder_iterator_v = is_folder_iterator<T>::value;

    template <class T>
    struct is_hashable : std::bool_constant<std::is_integral<T>::value || std::is_same<T, std::string>::value> {};

    template<class T>
    inline constexpr bool is_hashable_v = is_hashable<T>::value;
}

#endif