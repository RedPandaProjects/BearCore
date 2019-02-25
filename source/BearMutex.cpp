#include "BearCore.hpp"
#ifdef WINDOWS
#include "Windows/BearMutex_Windows.h"
#elif LINUX
#include "Linux/BearMutex_Linux.h"
#endif