#include "BearCore.hpp"

void BearCore::BearDebug::DebugBreak()
{
	__debugbreak();
}

void BearCore::BearDebug::FatalError(const bchar * text, ...)
{
	DebugBreak();
}

void BearCore::BearDebug::ErrorPrintf(const bchar * text, ...)
{
	va_list va;
	va_start(va, text);
#ifdef UNICODE
	vfwprintf(stderr, text, va);
#else
	vfprintf(stderr, text, va);
#endif
	va_end(va);
}
