#pragma once
#ifdef _MSC_VER
#include "../BearPlatform/MSVC/BearMemoryAllocator_MSVC.h"
#else
#include "../BearPlatform/GCC/BearMemoryAllocator_GCC.h"
#endif
