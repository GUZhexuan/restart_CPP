/*
 * @author: Zhexuan Gu
 * @Date: 2024-11-04 21:09:21
 * @LastEditTime: 2024-11-04 22:28:16
 * @FilePath: /LearnCudaProgramming/OTMV_binding.cpp
 * @Description: Please implement
 */
#include <torch/extension.h>

// Declare the roll_call_launcher function
void OTMVSq_launcher(torch::Tensor& vec, torch::Tensor& out, int vecSize);

// Write the C++ function that we will call from Python
void roll_call_binding(torch::Tensor& vec, torch::Tensor& out, int vecSize) {
    OTMVSq_launcher(vec, out, vecSize);
}

PYBIND11_MODULE(HOTKernel, m) {
  m.def(
    "OTMVsp", // Name of the Python function to create
    &roll_call_binding, // Corresponding C++ function to call
    "Launches the roll_call kernel" // Docstring
  );
}