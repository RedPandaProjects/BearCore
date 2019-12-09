#include "BearCore.hpp"
using namespace BearCore;
#ifdef WINDOWS
#include "Windows/BearThread_Windows.h"
#elif UNIX
#include "Unix/BearThread_Unix.h"
#endif

