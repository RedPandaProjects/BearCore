#pragma once
#ifdef MSVC
#include "../BearPlatform/MSVC/BearMemoryAllocator_MSVC.h"
#else
#include "../BearPlatform/GCC/BearMemoryAllocator_GCC.h"
#endif
