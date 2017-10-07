#include "ndarray.h"

namespace mobula{

NDArray::NDArray():_size(0), _dtype(DATA_TYPE::FLOAT), _data(nullptr, xdel<DType>){
}

NDArray::~NDArray(){
}

int NDArray::size() const{
	return _size;
}

int NDArray::ndim() const{
	return _shape.size();
}

Vec<int> NDArray::shape() const{
	return _shape;
}

void NDArray::alloc(int n){
	_size = n;
	_shape.resize(1, n);
	_data.reset(xnew<DType>(n));
}

NDArray NDArray::reshape(Vec<int> shape) const{
	int new_size = 1;
	for (int k : shape)new_size *= k;
	NDArray tmp = *this;
	tmp._shape = shape;
	return tmp;
};

NDArray NDArray::to_host() const{
#ifdef USING_CUDA
	NDArray arr = *this;
	DType *target = new DType[_size];
	cudaMemcpy((void*)target, _data.get(), sizeof(DType) * _size, cudaMemcpyDeviceToHost);
	arr._data.reset(target);
	return arr;
#else
	return *this;
#endif
}

DType* NDArray::data(){
	return _data.get();
}
DType* NDArray::data() const{
	return _data.get();
}

ostream& operator<<(ostream &os,const NDArray &a){
	NDArray a_host = a.to_host();
	vector<int> shape_iter(a._shape.size(), 0);
	while(1){

	}
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
