#include <iostream>
#include "ndarray.h"
#include "ops.h"
using namespace std;
using namespace mobula;

int main(){
	NDArray a = arange(10);
	NDArray a_host = a.to_host();
	cout << "SIZE: " << a.size() << endl;
	for (int i = 0;i < a.size();++i){
		cout << a_host.data()[i] << endl;
	}
	return 0;
}
