/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-17 20:38:01
 * @LastEditTime: 2024-07-17 20:58:28
 * @FilePath: /CPPprojects/restart_CPP/LearnCMake/tut2/MathFunctions/mysqrt.cxx
 * @Description: Please implement
 */
#include "mysqrt.h"

#include <iostream>

namespace mathfunctions {
namespace detail {
// a hack square root calculation using simple operations
double mysqrt(double x)
{
  if (x <= 0) {
    return 0;
  }

  double result = x;

  // do ten iterations

  /*
  To compute:  n = result^2
  we define:   delta = n - result^2 

  then apply gradient descent method on delta function since our target is to minimize the delta to 0.

  We know from the newton step method that:
    we can take the intersection of  "the tagent line on result" & "the x axis" as the new x ccordinate
    since the point is  (result, delta) and the slope is -2*result
    therefore the tangent line can be represented as:
        m = -2 * result * (x - result) + delta

        set m = 0;        new_result = delta / (2 * result) + result; 
  */

  for (int i = 0; i < 10; ++i) {
    if (result <= 0) {
      // square root must be positive
      result = 0.1;
    }
    double delta = x - (result * result);
    result = result + 0.5 * delta / result;
    std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
  }
  return result;
}
}
}