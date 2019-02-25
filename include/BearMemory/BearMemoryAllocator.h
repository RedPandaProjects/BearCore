#pragma once
#ifdef WINDOWS
#include "../BearPlatform/Windows/BearMemoryAllocator.h"
#elif LINUX
#include "../BearPlatform/Linux/BearMemoryAllocator.h"
#endif
