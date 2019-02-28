#include "BearCore.hpp"
#ifdef WINDOWS
#include "Windows/BearMutex_Windows.h"
#elif UNIX
#include "Linux/BearMutex_Linux.h"
#endif