#include "ops.h"

namespace mobula{

MOBULA_KERNEL arange_kernel(const int n, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = i;
	}
}

NDArray arange(const int n){
	NDArray arr;
	arr.alloc(n);
	KERNEL_RUN(arange_kernel, n)(n, arr.data());
	return arr;
}

MOBULA_KERNEL set_nums_kernel(const int n, const DType value, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = value;
	}
}

NDArray zeros(const int n){
	return zeros(Vec<int>(1, n));
}

NDArray zeros(const Vec<int> shape){
	NDArray arr;
	int n = prod(shape);
	arr.alloc(n);
	arr.reshape(shape);
	KERNEL_RUN(set_nums_kernel, n)(n, 0, arr.data());
	return arr;
}

NDArray ones(const int n){
	return ones(Vec<int>(1, n));
}

NDArray ones(const Vec<int> shape){
	NDArray arr;
	int n = prod(shape);
	arr.alloc(n);
	arr.reshape(shape);
	KERNEL_RUN(set_nums_kernel, n)(n, 1, arr.data());
	return arr;
}

};
