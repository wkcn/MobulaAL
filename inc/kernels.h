#ifndef _MOBULA_KERNELS_
#define _MOBULA_KERNELS_

#include "defines.h"

namespace mobula{

MOBULA_KERNEL add_kernel(const int n, const DType *a, const DType *b, DType *output);
MOBULA_KERNEL subtract_kernel(const int n, const DType *a, const DType *b, DType *output);
MOBULA_KERNEL arange_kernel(const int n, DType *output);
MOBULA_KERNEL set_nums_kernel(const int n, const DType value, DType *output);

};

#endif
