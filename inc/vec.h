#ifndef _MOBULA_VEC_
#define _MOBULA_VEC_

#include <iostream>
#include <vector>
using namespace std;

namespace mobula{

template<typename T>
class Vec : public vector<T>{
public:
	bool operator==(const Vec &other) const;
	bool operator!=(const Vec &other) const;
};

template<typename T>
bool Vec<T>::operator==(const Vec<T> &other) const{
	if (this->size() != other.size())return false;
	for (int i = 0;i < this->size();++i){
		if ((*this)[i] != other[i])return false;
	}
	return true;
}

template<typename T>
bool Vec<T>::operator!=(const Vec<T> &other) const{
	return !(*this == other);
}

template<typename T>
ostream& operator<<(ostream &os,const Vec<T> &v){
	os << '(';
	bool first = true;
	for (T k : v){
		if (!first)os << ", ";
		first = false;
		os << k;
	}
	if (v.size() == 1)os << ',';
	os << ')';
	return os;
}

};

#endif
