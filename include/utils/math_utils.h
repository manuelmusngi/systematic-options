#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cmath> // For std::erf

// Standard normal cumulative distribution function (CDF)
// This is an approximation for erf. For production, use a more robust library.
double normal_cdf(double x);

#endif // MATH_UTILS_H
