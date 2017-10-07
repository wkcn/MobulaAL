#ifndef _MOBULA_NDARRAY_
#define _MOBULA_NDARRAY_


#include "defines.h"
#include "vec.h"

namespace mobula{

class NDArray{
public:
	NDArray();
	~NDArray();
	DType* data();
	DType* data() const;
public:
	int size() const;
	int ndim() const;
	Vec<int> shape() const;
	NDArray reshape(Vec<int> shape) const;
	NDArray to_host() const;
public:
	void alloc(int n);
	void free();
public:
	template<typename T>
	T get_data(T, int i);
public:
	friend NDArray operator+(const NDArray&, const NDArray&);
private:
	int _size;
	Vec<int> _shape;
	DATA_TYPE _dtype;
	DType *_data;
};

};
#endif
