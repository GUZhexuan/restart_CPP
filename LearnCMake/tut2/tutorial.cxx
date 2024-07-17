/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-16 20:56:07
 * @LastEditTime: 2024-07-17 21:28:21
 * @FilePath: /CPPprojects/restart_CPP/LearnCMake/tut2/tutorial.cxx
 * @Description: 
 *              A example provided in CMake Tutorial Official
 *              It just calculates the square root of the input
 */
// A simple program that computes the square root of a number
#include <cmath>
#include <cstdlib> // TODO 5: Remove this line
#include <iostream>
#include <string>

// TODO 11: Include TutorialConfig.h
#include "TutorialConfig.h"

#ifdef USE_MYMATH
#  include "MathFunctions.h"
#endif

int main(int argc, char* argv[])
{
  if (argc < 2) {
    // TODO 12: Create a print statement using Tutorial_VERSION_MAJOR
    //          and Tutorial_VERSION_MINOR

    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;

    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  // TODO 4: Replace atof(argv[1]) with std::stod(argv[1])
  const double inputValue = atof(argv[1]);

  // calculate square root
  #ifdef USE_MYMATH
    std::cout << "I'm using my Newton-Based square root calculation mathod." << std::endl;
    const double outputValue = mathfunctions::sqrt(inputValue);
  #else
    const double outputValue = sqrt(inputValue);
  #endif
  std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
  return 0;
}