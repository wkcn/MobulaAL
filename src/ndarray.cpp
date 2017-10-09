#include "ndarray.h"
#include "kernels.h"

namespace mobula{

NDArray::NDArray():_size(0), _dtype(DATA_TYPE::FLOAT), _data(nullptr, xdel<DType>){
}

NDArray::NDArray(const int size):_dtype(DATA_TYPE::FLOAT), _data(nullptr, xdel<DType>){
	alloc(size);
	reshape({size});
}

NDArray::NDArray(const Vec<int> &shape):_dtype(DATA_TYPE::FLOAT), _data(nullptr, xdel<DType>){
	alloc(prod(shape));
	reshape(shape);
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

int NDArray::get_ravel_id(const Vec<int> index) const{
	int u = 1;
	int id = 0;
	for (int i = index.size() - 1;i >= 0;--i){
		id += index[i] * u;
		u *= _shape[i];
	}
	return id;
}

DType NDArray::operator[](const int id) const{
	return _data.get()[id];
}
DType& NDArray::operator[](const int id){
	return _data.get()[id];
}

DType* NDArray::data(){
	return _data.get();
}
DType* NDArray::data() const{
	return _data.get();
}

void print_char(ostream &os, char c, int n = 1){
	for (int i = 0;i < n;++i){
		os << c; 
	}
}

void print_ndarray(ostream &os, const NDArray &a, Vec<int> &shape_iter, int axis, const int max_len){
	const Vec<int> shape = a.shape();
	int axis_len = shape[axis];
	if (axis == shape_iter.size() - 1){
		// last axis
		os << '[';
		bool first = true;
		for (int i = 0;i < axis_len;++i){
			shape_iter[axis] = i;
			if (!first)os << ", ";
			first = false;
			os << setw(max_len) << a[a.get_ravel_id(shape_iter)];
		}
		os << ']';
		if (shape_iter[axis] != shape[axis] - 1){
			os << ", " << endl;
			print_char(os, '\n', shape.size() - axis - 2);
			print_char(os, ' ', axis);
		}
		return;
	}
	for (int i = 0;i < axis_len;++i){
		shape_iter[axis] = i;
		os << '[';
		print_ndarray(os, a, shape_iter, axis + 1, max_len);
		os << ']';
		if (shape_iter[axis] != shape[axis] - 1){
			os << ", " << endl;
			print_char(os, '\n', shape.size() - axis - 2);
			print_char(os, ' ', axis);
		}
	}
}	

ostream& operator<<(ostream &os,const NDArray &a){
	NDArray a_host = a.to_host();
	Vec<int> shape_iter(a._shape.size(), 0);
	DType max_val = a_host[0];
	for (int i = 1;i < a_host.size();++i){
		if (a_host[i] > max_val)max_val = a_host[i];
	}
	stringstream ss;
	ss << max_val;
	int max_len = ss.str().size();
	print_ndarray(os, a_host, shape_iter, 0, max_len);
	return os;
}

NDArray operator+(const NDArray& a, const NDArray& b){
	NDArray output(a.shape());
	KERNEL_RUN(add_kernel, 1)(a.size(), a.data(), b.data(), output.data());
	return output;
}

NDArray& operator+=(NDArray &a, const NDArray& b){
	KERNEL_RUN(add_kernel, 1)(a.size(), a.data(), b.data(), a.data());
	return a;
}

NDArray& operator-=(NDArray &a, const NDArray& b){
	KERNEL_RUN(subtract_kernel, 1)(a.size(), a.data(), b.data(), a.data());
	return a;
}

NDArray operator-(const NDArray& a, const NDArray& b){
	NDArray output(a.shape());
	KERNEL_RUN(subtract_kernel, 1)(a.size(), a.data(), b.data(), output.data());
	return output;
}


};
