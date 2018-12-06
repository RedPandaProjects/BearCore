#include "BearCore.hpp"
#include "BugTrap.h"


void BearCore::BearDebug::DebugBreak()
{
	__debugbreak();
}


void BearCore::BearDebug::FatalError(const bchar * chenk, const bchar * name, const bchar * function_name, uint32 line, const bchar * text, ...)
{
	BearString str;

	str.append(TEXT("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"));
	str.append(TEXT("\r\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"));
	str.append(TEXT("\r\nОшибка в сценарие:")).append(name);
	str.append(TEXT("\r\nМесто проблемы:")).append(chenk);
	str.append(TEXT("\r\nФункцыя:")).append(function_name);
	str.append(TEXT("\r\nСтрока:"));
	str.append_printf(TEXT("%u"),line);
	str.append(TEXT("\r\nКоментарий:"));
	va_list va;
	va_start(va, text);
	str.append_printf_va(text, va);
	va_end(va);
	str.append(TEXT("\r\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"));
	str.append(TEXT("\r\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"));
	BearLog::Printf(TEXT("%s"),*str);
	ShowMessage(TEXT("FATAL ERROR!!!"), *str);
	BT_SetDialogMessage(
		BTDM_INTRO2,
		*str
	);
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


void BearCore::BearDebug::ShowMessage(const bchar * title, const bchar * text)
{
	MessageBox(NULL, text, title, MB_ICONERROR);
}
