/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-17 21:25:16
 * @LastEditTime: 2024-07-17 23:07:31
 * @FilePath: /CPPprojects/restart_CPP/LearnCMake/tut2/MathFunctions/MathFunctions.cxx
 * @Description: 
 *              Call the functions 'mysqrt' in detail namespace 
 */
#include "MathFunctions.h"

// TODO 11: include cmath

// TODO 10: Wrap the mysqrt include in a precompiled ifdef based on USE_MYMATH
#include "mysqrt.h"

namespace mathfunctions {
double sqrt(double x)
{
  // TODO 9: If USE_MYMATH is defined, use detail::mysqrt.
  // Otherwise, use std::sqrt.
  return detail::mysqrt(x);
}
}