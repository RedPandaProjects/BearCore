#include "BearCore.hpp"
static void(*LCallBack)(void) = 0;
extern BearStringPath LogFileOut;
#ifndef GCC
#include "BugTrap.h"
#pragma warning(disable:4091)
#include <dbghelp.h> // MiniDump flags
void CALLBACK GErrorHandler(INT_PTR)
{
	if (LCallBack)LCallBack();
	BearLog::Flush();
	BT_AddLogFile(LogFileOut);
	BT_SaveSnapshot(0);
}

#elif UNIX
#include <signal.h>
#endif


void BearDebug::DebugBreak()
{
#ifdef WINDOWS
	__debugbreak();
#else
   __builtin_trap();
#endif
}




void BearDebug::FatalError(const bchar * chenk, const bchar * name, const char * function_name, uint32 line, const bchar * text, ...)
{
	BearString str;

	str.append(TEXT("\r\nОшибка в файле:")).append(name);
	str.append(TEXT("\r\nМесто:")).append(chenk);
#ifdef UNICODE
	str.append(TEXT("\r\nФункция:")).append(*BearEncoding::FastToUnicode( function_name));
#else
	str.append(TEXT("\r\nФункция:")).append(function_name);
#endif
	str.append(TEXT("\r\nСтока:"));
	str.append_printf(TEXT("%u"),line);
	str.append(TEXT("\r\nКомментарий"));
	va_list va;
	va_start(va, text);
	str.append_printf_va(text, va);
	va_end(va);
	BearLog::Printf(TEXT(BEAR_PRINT_STR_CURRENT),*str);
#ifdef DEBUG
	ShowMessage(TEXT("FATAL ERROR!!!"), *str);
#endif
#ifndef GCC

	BT_SetDialogMessage(
		BTDM_INTRO2,
		TEXT("")
	);
#endif
	if (LCallBack)LCallBack();
	LCallBack = 0;
	DebugBreak();
}

void BearDebug::ErrorMessage(const bchar * text, ...)
{
	BearString str;
	va_list va;
	va_start(va, text);
	str.append_printf_va(text, va);
	va_end(va);
	ShowMessage(TEXT("ERROR!!!"), *str);
	exit(-1);
}

void BearDebug::SetCallBack(void(*callback)(void))
{
	LCallBack = callback;
}


void BearDebug::ShowMessage(const bchar * title, const bchar * text)
{
#ifdef WINDOWS
	MessageBox(NULL, text, title, MB_ICONERROR);
#elif UNIX
	//printf(text);
#endif
}
