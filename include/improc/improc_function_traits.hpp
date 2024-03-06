#ifndef IMPROC_INFRASTRUCTURE_FUNCTION_TRAITS_HPP
#define IMPROC_INFRASTRUCTURE_FUNCTION_TRAITS_HPP

#include <variant>

namespace improc 
{
    /** @defgroup function_traits Function Traits
     *  Function traits defined in the image processing library
     *  @{
     */

    template<class Function>
    struct function_traits;
    
    // Function pointer
    template<class ReturnType, class ... Args>
    struct function_traits<ReturnType(*)(Args...)> : public function_traits<ReturnType(Args...)> {};
    
    template<class ReturnType, class ... Args>
    struct function_traits<ReturnType(Args ...)>
    {
        using return_type = ReturnType;

        using signature = ReturnType(Args ...);
    
        static constexpr std::size_t arity = sizeof...(Args);
    
        template <std::size_t ArgSize>
        struct argument
        {
            static_assert(ArgSize < arity, "Invalid number of parameters for functor");
            using type = typename std::tuple_element<ArgSize,std::tuple<Args ...>>::type;
        };
    };

    // Member function pointer
    template<class ClassType, class ReturnType, class ... Args>
    struct function_traits<ReturnType(ClassType::*)(Args ...)> : public function_traits<ReturnType(ClassType&,Args ...)> {};
    
    template<class ClassType, class ReturnType, class ... Args>
    struct function_traits<ReturnType(ClassType::*)(Args ...) const> : public function_traits<ReturnType(ClassType&,Args ...)> {};
    
    // Member object pointer
    template<class ClassType, class ReturnType>
    struct function_traits<ReturnType(ClassType::*)> : public function_traits<ReturnType(ClassType&)> {};

    // Functor
    template<class Functor>
    struct function_traits
    {
        private:
            using call_type = function_traits<decltype(&std::remove_reference<Functor>::type::operator())>;

        public:
            using return_type = typename call_type::return_type;

            using signature   = typename call_type::signature;

            static constexpr std::size_t arity = call_type::arity - 1;
    
            template <std::size_t ArgSize>
            struct argument
            {
                static_assert(ArgSize < arity, "Invalid number of parameters for functor");
                using type = typename call_type::template argument<ArgSize + 1>::type;
            };
    };
    
    template<class Functor>
    struct function_traits<Functor&> : public function_traits<Functor> {};
    
    template<class Functor>
    struct function_traits<Functor&&> : public function_traits<Functor> {};

    template <class Functor>
    inline constexpr bool is_function_v = std::is_function<typename improc::function_traits<Functor>::signature>::value;

    // Variant Functor
    template<class>
    struct is_variant_arg_function_type : std::false_type {};

    template<class ... VariantArgs>
    struct is_variant_arg_function_type<std::variant<VariantArgs ...>> 
    : std::conjunction< std::is_function<typename improc::function_traits<VariantArgs>::signature> ...> {};

    template<class T>
    inline constexpr bool is_variant_arg_function_type_v = is_variant_arg_function_type<T>::value;

    template<class,class>
    struct is_variant_arg_function_return_type : std::false_type {};

    template<class ReturnType, class ... VariantArgs>
    struct is_variant_arg_function_return_type<ReturnType, std::variant<VariantArgs ...>> 
    : std::conjunction< std::is_same<ReturnType, typename improc::function_traits<VariantArgs>::return_type> ...> {};

    template<class ReturnType, class T>
    inline constexpr bool is_variant_arg_function_return_type_v = is_variant_arg_function_return_type<ReturnType,T>::value;

    /** @} */ // end of function_traits
}

#endif