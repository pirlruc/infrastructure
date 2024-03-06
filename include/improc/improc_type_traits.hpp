#ifndef IMPROC_INFRASTRUCTURE_TYPE_TRAITS_HPP
#define IMPROC_INFRASTRUCTURE_TYPE_TRAITS_HPP

#include <type_traits>
#include <filesystem>
#include <variant>

namespace improc 
{
    /** @defgroup type_traits Type Traits
     *  Type traits defined in the image processing library
     *  @{
     */
    
    template<class>
    inline constexpr bool dependent_false_v = false;

    /**
     * @brief If T is a directory iterator, provides the member constant value equal to true. Otherwise value is false.
     * 
     * @tparam T 
     */
    template <class T>
    struct is_folder_iterator : std::bool_constant<    std::is_same<T, std::filesystem::recursive_directory_iterator>::value
                                                    || std::is_same<T, std::filesystem::directory_iterator>::value > {};
    template<class T>
    inline constexpr bool is_folder_iterator_v = is_folder_iterator<T>::value;

    /**
     * @brief If T is a standard C character array string, provides the member constant value equal to true. Otherwise value is false.
     * 
     * @tparam T 
     */
    template <class T>
    struct is_c_str : std::bool_constant<   std::is_same<typename std::decay<T>::type, char *>::value > {};
    template<class T>
    inline constexpr bool is_c_str_v = is_c_str<T>::value;

    template <class T>
    struct is_path : std::bool_constant<    std::is_same<T, std::filesystem::path>::value
                                         || std::is_same<T, std::string>::value
                                         || improc::is_c_str<T>::value > {};
    template<class T>
    inline constexpr bool is_path_v = is_path<T>::value;

    template <class T>
    struct is_hashable : std::bool_constant<std::is_integral<T>::value || std::is_same<T, std::string>::value> {};
    template<class T>
    inline constexpr bool is_hashable_v = is_hashable<T>::value;

    template<class>
    struct is_variant : std::false_type {};
    template<class ... VariantArgs>
    struct is_variant<std::variant<VariantArgs ...>> : std::true_type {};
    template<class T>
    inline constexpr bool is_variant_v = improc::is_variant<T>::value;

    /** @} */ // end of type_traits
}

#endif