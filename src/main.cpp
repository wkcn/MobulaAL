#include <iostream>
#include "ndarray.h"
#include "ops.h"
using namespace std;
using namespace mobula;

int main(){
	NDArray a = arange(16);
	NDArray a_host = a.to_host();
	cout << "SIZE: " << a.size() << endl;
	cout << "SHAPE: " << a.shape() << endl;
	cout << a << endl;
	cout << a.reshape({2,2,2,2}) << endl;
	NDArray b = ones(16);
	cout << b << endl;
	cout << a + b << endl;
	a += b;
	cout << a << endl;
	a -= b;
	cout << a << endl;
	cout << a - a - b << endl;
	return 0;
}
