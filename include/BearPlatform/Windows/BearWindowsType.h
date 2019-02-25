#pragma warning (disable:4127 4239 4100 4251 4201 4756)

typedef signed   char int8;
typedef unsigned char uint8;
typedef signed   short int16;
typedef unsigned short uint16;
typedef signed   int int32;
typedef unsigned int uint32;
typedef char bchar8;
typedef wchar_t bchar16;
typedef int8 bcharu8;
#ifdef UNICODE
typedef  bchar16 bchar;
#else
typedef  bchar8 bchar;
#endif
typedef signed   __int64 int64;
typedef unsigned __int64 uint64;

#ifdef X32
typedef uint32 bptr;
#else
typedef uint64 bptr;
#endif
#ifdef X32
typedef uint32 bsize;
#else
typedef uint64 bsize;
#endif
#ifdef X32
typedef int32 bint;
#else
typedef int64 bint;
#endif

#include <Windows.h>