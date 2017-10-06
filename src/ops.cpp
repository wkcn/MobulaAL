#include "ops.h"

namespace mobula{

MOBULA_KERNEL arange_kernel(const int n, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = i;
	}
}

NDArray arange(const int n){
	NDArray arr;
	KERNEL_RUN(arange_kernel, n)(n, arr.data());
	return arr;
}

};
