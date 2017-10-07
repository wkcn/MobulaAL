#ifndef _MOBULA_OPS_
#define _MOBULA_OPS_

#include "ndarray.h"

namespace mobula{

NDArray arange(const int n);
NDArray zeros(const int n);
NDArray zeros(const Vec<int> shape);
NDArray ones(const int n);
NDArray ones(const Vec<int> shape);

template<typename T>
T prod(const Vec<T> &v){
	T res = 1;
	for (T t : v)res *= t;
	return res;
}

template<typename T>
T sum(const Vec<T> &v){
	T res = 0;
	for (T t : v)res += t;
	return res;
}


};

#endif
