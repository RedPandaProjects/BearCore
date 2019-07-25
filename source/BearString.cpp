#include "BearCore.hpp"
using namespace BearCore;
#ifdef WINDOWS
#include "Windows/BearString_Windows.h"
#elif UNIX
#include "Unix/BearString_Unix.h"
#endif

