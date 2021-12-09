#ifndef IMPROC_MATH_UTILS_HPP
#define IMPROC_MATH_UTILS_HPP

#include <improc/infrastructure/logger_infrastructure.hpp>
#include <improc/improc_defs.hpp>

namespace improc 
{
    namespace math
    {
        template <typename NumericType>
        bool IMPROC_EXPORTS IsEven(const NumericType& number);

        template <typename NumericType>
        bool IMPROC_EXPORTS IsOdd(const NumericType& number);
    }
}

#include <math_utils.tpp>

#endif
