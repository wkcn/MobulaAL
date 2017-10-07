#include "defines.h"

namespace mobula{
map<thread::id, int> MOBULA_KERNEL_IDS;
mutex MOBULA_KERNEL_IDS_MUTEX;
};
