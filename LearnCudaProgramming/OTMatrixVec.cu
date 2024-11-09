/*
 * @author: Zhexuan Gu
 * @Date: 2024-11-02 14:07:25
 * @LastEditTime: 2024-11-05 12:44:59
 * @FilePath: /LearnCudaProgramming/OTMatrixVec.cu
 * @Description: Please implement
 */
#include <torch/extension.h>
// default to deal with square matrix first 
// Grid Layout    dim3 blocks(3, 2m)
// Block Layout   dim3 threads(mn, mn) = (m^2, m^2)
__global__ void OTMVSq(double* v, double* o, int m, const int widthsplit, const int heightsplit){
  // Block index
  int bx = blockIdx.x;
  int by = blockIdx.y;

  // Thread index
  int tx = threadIdx.x;
  int ty = threadIdx.y;

  // Block dim
  int dx = blockDim.x;
  int dy = blockDim.y;

  // map each thread to sparse matrix entry index
  int Arow = dy * by + ty;
  int Acol = dx * bx + tx;

  if (bx < widthsplit && by < heightsplit) {
    // A1 case
    if(Acol >= Arow * m && Acol < (Arow + 1) * m) {
      atomicAdd(o + Arow, v[Acol]);
    }
  }
  else if (by < heightsplit && bx >= widthsplit){
    // A2 case
    int offset = widthsplit * dx;
    if(((Acol - offset) % (m * m)) == Arow) {
      atomicAdd(o + Arow, -1 * v[Acol]);
    }
  }
  else if (by >= heightsplit && by < 2 * heightsplit && bx < widthsplit) {
    // A3 case 
    int relative_Arow = Arow - heightsplit * dy;
    int subblockid = relative_Arow / m;
    if(Acol >= subblockid * m * m && Acol < (subblockid + 1) * m * m && Acol % m == relative_Arow % m) {
      atomicAdd(o + Arow, v[Acol]);
    }
  }
  else if (by >= 2 * heightsplit && bx >= widthsplit){
    // A4 case
    int relative_Arow = Arow - heightsplit * dy * 2;
    int relative_Acol = Acol - widthsplit * dx;
    int subblockid = relative_Arow / m;
    if(relative_Acol >= subblockid * m * m && relative_Acol < (subblockid + 1) * m * m && relative_Acol % m == relative_Arow % m) {
      atomicAdd(o + Arow, v[Acol]);
    }
  }
}

void OTMVSq_launcher(torch::Tensor& vec, torch::Tensor& out, int vecSize) {
    // Note that we only consider square matrix case
    // additionally, we mainly consider the 32 multiple case
    const int sparseArows = vecSize * vecSize * 3;
    const int sparseAcols = 2 * vecSize * vecSize * vecSize;
    int blockdim = 32;
    dim3 gridSize(sparseAcols / blockdim, sparseArows / blockdim);
    dim3 blockSize(blockdim, blockdim);
    const int widthsplit = vecSize * vecSize * vecSize / blockdim;
    const int heightsplit = vecSize * vecSize / blockdim;
    OTMVSq<<<gridSize, blockSize>>>(vec.data_ptr<double>(), out.data_ptr<double>(), vecSize, widthsplit, heightsplit);
}

