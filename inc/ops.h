#ifndef _MOBULA_OPS_
#define _MOBULA_OPS_

#include "ndarray.h"

namespace mobula{

NDArray arange(const int n);
NDArray zeros(const int n);
NDArray zeros(const Vec<int> shape);
NDArray ones(const int n);
NDArray ones(const Vec<int> shape);

};

#endif
