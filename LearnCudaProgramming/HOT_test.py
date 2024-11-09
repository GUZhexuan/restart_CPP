'''
author: Zhexuan Gu
Date: 2024-11-04 20:35:19
LastEditTime: 2024-11-07 15:31:41
FilePath: /restart_CPP/LearnCudaProgramming/HOT_test.py
Description: Please implement
'''


import scipy.sparse as sp
import numpy as np
import torch
import time
import HOTKernel
import os

m = n = 64

dtype = torch.float64
device = 'cuda' if torch.cuda.is_available() else 'cpu'

HOTout = torch.zeros(3 * m * n, dtype=dtype, device=device)
Kernelout = torch.zeros(3 * m * n, dtype=dtype, device=device)
torchSpmvout = torch.zeros(3 * m * n, dtype=dtype, device=device)
sparseAtensor = None


def sparseA():
    A1 = sp.kron(sp.identity(m * n), np.ones(m), format='csr')
    A2 = sp.kron(-np.ones(n), sp.identity(m * n), format='csr')
    A3 = sp.kron(sp.identity(n), sp.kron(np.ones(m), sp.identity(m)), format='csr')
    A4_bar = sp.kron(sp.identity(n), sp.kron(np.ones(n), sp.identity(m)), format='csr')
    
    zeros_1 = sp.csr_matrix((m * n, m * n * n))
    zeros_2 = sp.csr_matrix((m * n, m * m * n))
    
    A = sp.hstack([A1, A2])
    A = sp.vstack([A, sp.hstack([A3, zeros_1])])
    A = sp.vstack([A, sp.hstack([zeros_2, A4_bar])], format="csr")
    
    global sparseAtensor
    sparseAtensor = torch.sparse_csr_tensor(A.indptr, A.indices, A.data, dtype=dtype, device=device)
    

def Ax(vec):
    x1_r = vec[ : m**2 * n]
    x1_r = x1_r.reshape(m * n, m)
    A1x1 = torch.sum(x1_r, dim=1)
    x2_r = vec[m**2 * n : ]
    x2_r = x2_r.reshape(n, m * n)
    A1x1 -= torch.sum(x2_r, dim=0)  
    x1_r = x1_r.reshape(n, m, m)
    A3x1 = torch.sum(x1_r, dim=1).flatten()
    x2_r = x2_r.reshape(n, n, m)
    A4x2 = torch.sum(x2_r, dim=1).flatten()
    torch.concat([A1x1, A3x1, A4x2], out=HOTout)


def randvec():
    vec = torch.randn(m**2 * n + n ** 2 * m, dtype=dtype, device=device)
    return vec


def test(option: int, vec, iters):
    method_str = None
    start = time.perf_counter()
    if option == 1: # this method should contain generate sparse matrix time
        method_str = "Torch internal sparse matrix multiplication."
        sparseA()
        for i in range(iters):
            torchSpmvout = torch.sparse.mm(sparseAtensor, vec.unsqueeze(1)).squeeze()
    elif option == 2:
        method_str = "Block wise multiplication using torch APIs."
        for i in range(iters):
            Ax(vec)
    else:
        method_str = "Pure C++ and cuda kernels."
        for i in range(iters):
            HOTKernel.OTMVsp(vec, Kernelout, m)
    end = time.perf_counter()
    spend_t = end - start
    print("Sparse matrix vector multiplication spent {}s for {} iterations ({}), \
          avg time per iteration is {}s".format(spend_t, iters, method_str, spend_t / iters))


if __name__ == "__main__":
    
    test_vec = randvec()
    sparseA()
    
    # torchSpmvout = torch.sparse.mm(sparseAtensor, test_vec.unsqueeze(1)).squeeze()
    # torch.mv(sparseAtensor, test_vec, out=torchSpmvout)
    # HOTKernel.OTMVsp(test_vec, Kernelout, m)
    # Ax(test_vec)
    
    # print(torch.allclose(HOTout, Kernelout))
    # print(torch.allclose(HOTout, torchSpmvout))
    # print(torch.allclose(Kernelout, torchSpmvout))
    
    
    
    # compare three method times (using x iterations)
    # iters = 1500
    # for i in range(3):
    #     test(i + 1, test_vec, iters)
    
    
    
    
    # compare cpu version
    iters = 1500
    sparseAtensor = sparseAtensor.cpu()
    HOTout = HOTout.cpu()
    cpu_vec = test_vec.clone().cpu()
    start = time.perf_counter()
    for i in range(iters):
        # torchSpmvout = torch.sparse.mm(sparseAtensor, cpu_vec.unsqueeze(1)).squeeze()
        Ax(cpu_vec)
    end = time.perf_counter()
    spend_t = end - start
    print("Sparse matrix vector multiplication spent {}s for {} iterations (cpu SPMV), \
        avg time per iteration is {}s".format(spend_t, iters, spend_t / iters))
    
    
    start = time.perf_counter()
    for i in range(iters):
        HOTKernel.OTMVsp(test_vec, Kernelout, m)
    end = time.perf_counter()
    spend_t = end - start
    print("Sparse matrix vector multiplication spent {}s for {} iterations (HOTCUDA Kernel), \
        avg time per iteration is {}s".format(spend_t, iters, spend_t / iters))
    
    