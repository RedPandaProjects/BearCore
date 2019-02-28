
typedef signed   char int8;
typedef unsigned char uint8;
typedef signed   short int16;
typedef unsigned short uint16;
typedef signed   int int32;
typedef unsigned int uint32;
typedef char bchar8;
typedef wchar_t bchar16;
typedef int8 bchar_utf8;
#ifdef UNICODE
#define TEXT_I(a) L ## a
#define TEXT(a) TEXT_I(a)
typedef  bchar16 bchar;
#elif UTF_8
#define TEXT(a)  ((bchar_utf8*)a)
typedef  bchar_utf8 bchar;
#else 
#error "UNIX Не поддерживает ANSI"
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

#ifdef UNICODE
#define BEAR_PRINT_UTF8 "%s"
#define BEAR_PRINT_UNICODE "%S"
#define BEAR_PRINT_CURRENT "%S"
#else
#define BEAR_PRINT_UTF8 "%s"
#define BEAR_PRINT_UNICODE "%S"
#define BEAR_PRINT_CURRENT "%s"
#endif

#define BEARPROJECT_EXPORT
#define BEARPROJECT_IMPORT

