#include <iostream>
#include "ndarray.h"
#include "ops.h"
using namespace std;
using namespace mobula;

int main(){
	NDArray a = arange(10);
	NDArray a_host = a.to_host();
	cout << "SIZE: " << a.size() << endl;
	cout << "SHAPE: " << a.shape() << endl;
	for (int i = 0;i < a.size();++i){
		cout << a_host.data()[i] << endl;
	}

	NDArray b = ones(3);
	return 0;
}
