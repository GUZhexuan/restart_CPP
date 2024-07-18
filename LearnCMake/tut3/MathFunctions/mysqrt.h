/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-17 20:42:53
 * @LastEditTime: 2024-07-17 23:05:48
 * @FilePath: /CPPprojects/restart_CPP/LearnCMake/tut2/MathFunctions/mysqrt.h
 * @Description: 
 *                  The first namespace 'mathfunctions' is to include our sqrt function
 *                  in the 'libMathFunctions.a' library
 */
#pragma once

namespace mathfunctions {
    namespace detail {
        double mysqrt(double x);
    }
}