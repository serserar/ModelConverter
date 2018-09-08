#ifndef MATH_H
#define MATH_H
#include <math.h>
#include "../system.h"
#define Real T

template<class Real>
class Math {
public:

    constexpr static double PI = 3.14159265;
    constexpr static double HALF_PI = 0.5 * PI;
    constexpr static double DEG2RAD = 3.14159265 / 180;
    constexpr static double ZERO_TOLERANCE = 1e-08;;
    constexpr static double EPSILON = __DBL_EPSILON__;

    inline static Real Pow(Real base, Real exponent) {
        return (Real) pow((double) base, (double) exponent);
    }

    inline static Real Pow2(Real number) {
        return (Real) pow(number, 2.0);
    }

    inline static Real Sqrt(Real rvalue) {
        return (Real) sqrt((double) rvalue);
    }

    inline static Real Cos(Real rangle) {
        return (Real) cos((double) rangle);
    }

    inline static Real Sin(Real rangle) {
        return (Real) sin((double) rangle);
    }

    inline static Real Tan(Real rangle) {
        return (Real) tan((double) rangle);
    }

    inline static Real ACos (Real fValue) {
        if ( -(Real)1.0 < fValue )
        {
            if ( fValue < (Real)1.0 )
                return (Real)acos((double)fValue);
            else
                return (Real)0.0;
        }
        else
        {
            return PI;
        }
    }

    inline static Real ASin (Real fValue) {
        if ( -(Real)1.0 < fValue )
        {
            if ( fValue < (Real)1.0 )
                return (Real)asin((double)fValue);
            else
                return HALF_PI;
        } else {
            return -HALF_PI;
        }
    }

    inline static Real ATan(Real rangle) {
        return (Real) atan((double) rangle);
    }

    inline static Real InvSqrt (Real fValue) {
        return (Real)(1.0/sqrt((double)fValue));
    }

    inline static Real Abs (Real fValue) {
        return abs(fValue);
    }

    inline static Real DegreesToRadians(Real degree) {
        Real radians = ( degree * PI ) / 180 ;
        return radians;
    }

    inline static Real RadiansToDegree(Real radians) {
        Real degree=( radians * 180 ) / PI ;
        return degree;
    }
};

#endif // MATH_H
