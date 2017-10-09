#include "ops.h"
#include "kernels.h"

namespace mobula{

NDArray zeros(const int n){
	return zeros(Vec<int>(1, n));
}

NDArray zeros(const Vec<int> shape){
	NDArray arr(shape);
	int n = arr.size(); 
	KERNEL_RUN(set_nums_kernel, n)(n, 0, arr.data());
	return arr;
}

NDArray ones(const int n){
	return ones(Vec<int>(1, n));
}

NDArray ones(const Vec<int> shape){
	NDArray arr(shape);
	int n = arr.size();
	KERNEL_RUN(set_nums_kernel, n)(n, 1, arr.data());
	return arr;
}

NDArray arange(const int n){
	NDArray arr(n);
	KERNEL_RUN(arange_kernel, n)(n, arr.data());
	return arr;
}

};
