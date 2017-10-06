#include "ndarray.h"

namespace mobula{

NDArray::NDArray():dtype(FLOAT){
	_data = xnew<float>(10);
	_size = 10;
}

int NDArray::size() const{
	return _size;
}

int NDArray::ndim() const{
	return _ndim;
}

NDArray NDArray::to_host() const{
#ifdef USING_CUDA
	NDArray arr = *this;
	DType *target = new DType[_size];
	cudaMemcpy((void*)target, _data, sizeof(DType) * _size, cudaMemcpyDeviceToHost);
	arr._data = target;
	return arr;
#else
	return *this;
#endif
}

DType* NDArray::data() const{
	return _data;
}

MOBULA_KERNEL add_kernel(const int n, const DType *a, const DType *b, DType *output){
	KERNEL_LOOP(i, n){
		output[i] = a[i] + b[i];
	}
}

NDArray operator+(const NDArray& a, const NDArray& b){
	NDArray output;
	KERNEL_RUN(add_kernel, 1)(a.size(), a.data(), b.data(), output.data());
	return output;
}

};
