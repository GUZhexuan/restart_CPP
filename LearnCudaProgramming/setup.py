'''
author: Zhexuan Gu
Date: 2024-11-04 20:56:30
LastEditTime: 2024-11-04 22:05:11
FilePath: /LearnCudaProgramming/setup.py
Description: Please implement
'''
from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CUDAExtension

__version__ = "0.0.1"

# Define the C++ extension modules
ext_modules = [
    CUDAExtension('HOTKernel', [
        './OTMV_binding.cpp',
        './OTMatrixVec.cu',
    ])
]

setup(
    name="HOTKernel",
    version=__version__,
    ext_modules=ext_modules,
    cmdclass={"build_ext": BuildExtension}
)