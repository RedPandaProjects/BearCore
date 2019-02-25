#include "BearCore.hpp"
#ifdef WINDOWS
#include "BugTrap.h"
#pragma warning(disable:4091)
#include <dbghelp.h> // MiniDump flags
void CALLBACK GErrorHandler(INT_PTR)
{
	if (LCallBack)LCallBack();
	BearCore::BearLog::Flush();
	BT_AddLogFile(LogFileOut);
	BT_SaveSnapshot(0);
}

#elif LINUX
#include <signal.h>
#endif
static void(*LCallBack)(void) = 0;

void BearCore::BearDebug::DebugBreak()
{
#ifdef WINDOWS
	__debugbreak();
#else
   __builtin_trap();
#endif
}

extern BearCore::BearStringPath LogFileOut;


void BearCore::BearDebug::FatalError(const bchar * chenk, const bchar * name, const bchar * function_name, uint32 line, const bchar * text, ...)
{
	BearString str;

	str.append(TEXT("\r\n������ � �����:")).append(name);
	str.append(TEXT("\r\n����� ��������:")).append(chenk);
	str.append(TEXT("\r\n�������:")).append(function_name);
	str.append(TEXT("\r\n������:"));
	str.append_printf(TEXT("%u"),line);
	str.append(TEXT("\r\n����������:"));
	va_list va;
	va_start(va, text);
	str.append_printf_va(text, va);
	va_end(va);
	BearLog::Printf(TEXT("%s"),*str);
#ifdef DEBUG
	ShowMessage(TEXT("FATAL ERROR!!!"), *str);
#endif
#ifdef WINDOWS

	BT_SetDialogMessage(
		BTDM_INTRO2,
		TEXT("")
	);
#endif
	if (LCallBack)LCallBack();
	LCallBack = 0;
	DebugBreak();
}

void BearCore::BearDebug::ErrorMessage(const bchar * text, ...)
{
	BearString str;
	va_list va;
	va_start(va, text);
	str.append_printf_va(text, va);
	va_end(va);
	ShowMessage(TEXT("ERROR!!!"), *str);
	exit(-1);
}

void BearCore::BearDebug::SetCallBack(void(*callback)(void))
{
	LCallBack = callback;
}


void BearCore::BearDebug::ShowMessage(const bchar * title, const bchar * text)
{
#ifdef WINDOWS
	MessageBox(NULL, text, title, MB_ICONERROR);
#elif LINUX
	//printf(text);
#endif
}
