#include "kernels.h"

namespace mobula{

MOBULA_KERNEL add_kernel(const int n, const DType *a, const DType *b, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = a[i] + b[i];
	}
}

MOBULA_KERNEL subtract_kernel(const int n, const DType *a, const DType *b, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = a[i] - b[i];
	}
}

MOBULA_KERNEL set_nums_kernel(const int n, const DType value, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = value;
	}
}

MOBULA_KERNEL arange_kernel(const int n, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = i;
	}
}

};
