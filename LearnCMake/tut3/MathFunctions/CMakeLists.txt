# TODO 1: Add a library called MathFunctions with sources MathFunctions.cxx
# and mysqrt.cxx
# Hint: You will need the add_library command
add_library(MathFunctions MathFunctions.cxx mysqrt.cxx)

# Finally, the  'libMathFunctions.a' static library will be generated in the build directory

# By using 'interface' keyword, the consumer which links to MathFunctions library will
# automatically include the source directory where MathFunctions.h located! 
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Therefore, we can delete the EXTRA_INCLUDES in top-level CMakeLists.txt