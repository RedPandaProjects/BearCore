#include "BearCore.hpp"
#include "BugTrap.h"
static void(*LCallBack)(void) = 0;

void BearCore::BearDebug::DebugBreak()
{
	__debugbreak();
}

extern BearCore::BearStringPath LogFileOut;

void CALLBACK GErrorHandler(INT_PTR)
{
#ifdef WINDOWS
	if (LCallBack)LCallBack();
	BearCore::BearLog::Flush();
	BT_AddLogFile(LogFileOut);
	BT_SaveSnapshot(0);
#endif
}

void BearCore::BearDebug::FatalError(const bchar * chenk, const bchar * name, const bchar * function_name, uint32 line, const bchar * text, ...)
{
	BearString str;

	str.append(TEXT("\r\nОшибка в файле:")).append(name);
	str.append(TEXT("\r\nМесто проблемы:")).append(chenk);
	str.append(TEXT("\r\nФункция:")).append(function_name);
	str.append(TEXT("\r\nСтрока:"));
	str.append_printf(TEXT("%u"),line);
	str.append(TEXT("\r\nКоментарий:"));
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
	MessageBox(NULL, text, title, MB_ICONERROR);
}
