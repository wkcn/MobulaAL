#ifndef _MOBULA_NDARRAY_
#define _MOBULA_NDARRAY_


#include "defines.h"

namespace mobula{

class NDArray{
public:
	NDArray();
	int size() const;
	int ndim() const;
	DType* data() const;
	NDArray to_host() const;
public:
	template<typename T>
	T get_data(T, int i);
public:
	friend NDArray operator+(const NDArray&, const NDArray&);
private:
	int _size;
	int _ndim;
	int *_shape;
	DATA_TYPE dtype;
	DType *_data;
};

};
#endif
