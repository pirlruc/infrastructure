#ifndef IMPROC_MATH_HPP
#define IMPROC_MATH_HPP

#include <improc/infrastructure/logger_infrastructure.hpp>
#include <improc/improc_defs.hpp>

namespace improc 
{
    namespace math
    {
        template <typename NumericType>
        IMPROC_EXPORTS bool inline IsEven(const NumericType& number);

        template <typename NumericType>
        IMPROC_EXPORTS bool inline IsOdd(const NumericType& number);
    }
}

#include <math.tpp>

#endif
