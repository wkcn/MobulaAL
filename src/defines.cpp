#include "defines.h"

namespace mobula{
map<thread::id, pair<int, int> > MOBULA_KERNEL_INFOS;
map<thread::id, mutex> MOBULA_KERNEL_MUTEXES;
};
