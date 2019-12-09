#pragma once

typedef signed   char int8;
typedef unsigned char uint8;
typedef signed   short int16;
typedef unsigned short uint16;
typedef signed   int int32;
typedef unsigned int uint32;
typedef char bchar8;
typedef wchar_t bchar16;

#ifdef UNICODE
typedef  bchar16 bchar;
#else
typedef  bchar8 bchar;
#endif

#ifdef MSVC
typedef signed   __int64 int64;
typedef unsigned __int64 uint64;
#else
typedef signed   long long int64;
typedef unsigned  long long uint64;
#endif

#ifdef X32
typedef uint32 bsize;
typedef int32 bint;
#else
typedef uint64 bsize;
typedef int64 bint;
#endif


#ifdef WINDOWS
#include <Windows.h>
#endif

#define BEARPROJECT_EXPORT __declspec(dllexport)
#define BEARPROJECT_IMPORT __declspec(dllimport)