#include "BearCore.hpp"
using namespace BearCore;
#ifdef WINDOWS
#include "Windows/BearThread_Windows.h"
#elif UNIX
#include "Linux/BearThread_Linux.h"
#endif

