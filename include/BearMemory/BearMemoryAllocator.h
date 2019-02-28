#pragma once
#ifdef _MSVC_VER
#include "../BearPlatform/MSVC/BearMemoryAllocator.h"
#else
#include "../BearPlatform/GCC/BearMemoryAllocator.h"
#endif
