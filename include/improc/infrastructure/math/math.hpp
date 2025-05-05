#ifndef IMPROC_MATH_HPP
#define IMPROC_MATH_HPP

#include <improc/infrastructure/logging/logger_infrastructure.hpp>
#include <improc/improc_defs.hpp>
#include <improc/improc_type_traits.hpp>

namespace improc 
{
    namespace math
    {
        template <typename NumericType>
        bool inline IsEven(const NumericType& number);

        template <typename NumericType>
        bool inline IsOdd(const NumericType& number);
    }
}

#include <improc/infrastructure/math/math.tpp>

#endif
