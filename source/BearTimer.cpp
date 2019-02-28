#include "BearCore.hpp"
#ifdef WINDOWS
#include "Windows/BearTimer_Windows.h"
#elif UNIX
#include "Linux/BearTimer_Linux.h"
#endif 

