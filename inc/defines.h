#ifndef _MOBULA_DEFINES_
#define _MOBULA_DEFINES_

#include <vector>
#include <string>
#include <typeinfo>
#include <cassert>
using namespace std;

namespace mobula{

#ifdef USING_CUDA

#include <cuda_runtime.h>
#define CUDA_NUM_THREADS 512
#define CUDA_GET_BLOCKS(n) ((n) + CUDA_NUM_THREADS - 1) / CUDA_NUM_THREADS

#define MOBULA_KERNEL __global__ void 
#define KERNEL_LOOP(i,n) for (int i = blockIdx.x * blockDim.x + threadIdx.x;i < (n);i += blockDim.x * gridDim.x)
#define KERNEL_RUN(a, n) a<<<CUDA_GET_BLOCKS(n), CUDA_NUM_THREADS>>>

#else

#define MOBULA_KERNEL void
#define KERNEL_LOOP(i,n) for(int i = 0;i < (n);++i)
#define KERNEL_RUN(a, n) a

#endif

enum class DATA_TYPE{
	FLOAT
};
typedef float DType;

template<typename T>
T* xnew(int size){
#ifdef USING_CUDA
	T *p;
	cudaMalloc((void **)&p, sizeof(T) * size);
	return p; 
#else
	return new T[size];
#endif
}

template<typename T>
void xdel(T* p){
#ifdef USING_CUDA
	cudaFree(p);
#else
	delete []p;
#endif
}

};

#endif
