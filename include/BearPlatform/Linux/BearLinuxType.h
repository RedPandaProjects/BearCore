
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
#define TEXT_I(a) L ## a
#define TEXT(a) TEXT_I(a)
typedef  bchar16 bchar;
#else
#define TEXT(a)  a
typedef  bchar8 bchar;
#endif
typedef signed   long long int64;
typedef unsigned  long long uint64;

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

#define BEAR_PATH TEXT("/")
#define MAX_PATH 512
