



typedef signed   char int8;
typedef unsigned char uint8;
typedef signed   short int16;
typedef unsigned short uint16;
typedef signed   int int32;
typedef unsigned int uint32;
typedef char bchar8;
#if defined(_MSC_VER)
typedef wchar_t bchar16;
#else
typedef uint16 bchar16;
#endif
#ifdef _UNICODE
#define BEARUNICODE
#endif
#ifdef BEARUNICODE
typedef  bchar16 bchar;
#undef TEXT
#define TEXT(t) L##t
#else
typedef  char bchar;
#undef TEXT
#define TEXT(t) t
#endif
#if defined(_MSC_VER)
typedef signed   __int64 int64;
typedef unsigned __int64 uint64;
#else
typedef signed   long long int64;
typedef unsigned long long uint64;
#endif
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
 
typedef float float32;
typedef double float64;
#ifdef _LIB
#define BEARTOOL_API
#else
#ifdef _GCC
#ifndef BEARTOOL_EXPORTS
#define BEARTOOL_API 
#error
#else
#define BEARTOOL_API
#endif
#elif _MSC_VER
#ifdef BEARTOOL_EXPORTS
#define BEARTOOL_API __declspec(dllexport)
#else
#define BEARTOOL_API __declspec(dllimport)
#endif
#else
#error "Этот компилятор не подерживается"
#endif
#endif
namespace BearCore
{
	namespace Encoding
	{
		enum Encoding
		{
			ANSI,
			UTF8,
			UTF16
		};
	}
}
#ifdef WIN
#define BEAR_PATH TEXT("\\")
#else
#define BEAR_PATH TEXT("/")
#endif
#define BEAR_CLASS_STATIC(CL)\
	CL()=delete;\
	CL&operator=(const CL&cl)=delete;
#define BEAR_FUNCTION_DELETE(TYPE,FUN)\
	TYPE FUN()=delete;
#define BEAR_CLASS_NO_COPY(CL)\
	CL(const CL&cl) = delete;\
	CL(CL&&cl) = delete;\
	CL&operator=(const CL&cl) = delete;\
	CL&operator=(CL&&cl) = delete;
#ifdef DEBUG
#define BEAR_FUNCTION_DEBUG(RET,FUN,ARGS)\
	RET FUN(ARGS);
#else
#define BEAR_FUNCTION_DEBUG(RET,FUN,ARGS)\
	inlien RET FUN(ARGS){}
#endif
#ifdef UNICODE
#define BEAR_PRINT_UNICODE TEXT("%s")
#define BEAR_PRINT_ANSI TEXT("%S")
#else
#define BEAR_PRINT_UNICODE TEXT("%S")
#define BEAR_PRINT_ANSI TEXT("%s")
#endif