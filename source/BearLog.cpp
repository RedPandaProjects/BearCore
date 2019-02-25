#include "BearCore.hpp"
#ifdef WINDOWS
#include "BugTrap.h"
#endif
BearCore::BearVector<BearCore::BearStringConteniar> *LogData=0;
static BearCore::BearMutex LogMutex;
static BearCore::BearLogCallBack LogCallBack=0;
BearCore::BearStringPath LogFileOut=TEXT("");

#ifdef DEBUG
void BearCore::BearLog::DebugPrintf(const bchar * text, ...)
{
	
	BearMutexLock lock(LogMutex);
	BearString8192 var1;
	va_list va;
	va_start(va, text);
	BearString::PrintfVa(var1, text, va);
	va_end(va);
#if  defined(WINDOWS)&&defined(DEBUG)
	OutputDebugString(var1);
	OutputDebugString(TEXT("\r\n"));
#endif
#ifdef WINDOWS
	char text866[8192];
	CharToOem(var1, text866);
	printf(text866);
	printf("\r\n");
#elif LINUX
	wprintf(var1);
	wprintf(TEXT("\n"));
#endif
	Push(var1);
}
#endif
void BearCore::BearLog::Printf(const bchar * text, ...)
{

	BearMutexLock lock(LogMutex);
	BearString8192 var1;
	va_list va;
	va_start(va, text);
	BearString::PrintfVa(var1, text, va);
	va_end(va);
#if  defined(WINDOWS)&&defined(DEBUG)
	OutputDebugString(var1);
	OutputDebugString(TEXT("\r\n"));
#endif
#ifdef WINDOWS
	char text866[8192];
	CharToOem(var1, text866);
	printf(text866);
	printf("\r\n");
#elif LINUX
	wprintf(var1);
	wprintf(TEXT("\n"));
#endif
	Push(var1);
}

void BearCore::BearLog::Flush()
{
	if (!LogFileOut[0])
	{
		LogData->clear();
		return;
		
	}
	BearMutexLock lock(LogMutex);
	auto b = LogData->begin();
	auto e = LogData->end();
	BearCore::BearFileStream LogFile ;
	if (!LogFile.Open(LogFileOut, LogFile.M_Write))return;
	while (b != e)
	{
		LogFile.Write((void*)**b, sizeof(bchar)*(b->size()));
#ifdef WINDOWS
		LogFile.Write(TEXT("\r\n"), sizeof(bchar) * 2);
#else
		LogFile.Write((void*)TEXT("\n"), sizeof(bchar) * 2);
#endif
		b++;
	}
	LogData->clear();
}

void BearCore::BearLog::SetCallBack(BearLogCallBack call_back)
{
	LogCallBack = call_back;
}

const BearCore::BearVector<BearCore::BearStringConteniar>& BearCore::BearLog::Lock()
{
	LogMutex.Lock();
	return *LogData;
}

void BearCore::BearLog::Unlock()
{
	LogMutex.Unlock();
}

void BearCore::BearLog::SetFile(const bchar * file)
{
	BearString::Copy(LogFileOut, file);
}


void BearCore::BearLog::Push(bchar * string)
{

	bsize cur = 0;
	for (bsize i = 0; string[i]; i++)
	{
		if (string[i] == TEXT("\r")[0])
		{
			string[i] = 0;
			if (string[i + 1] == TEXT("\n")[0])
				i++;
			i++;	
			if (string[cur]) {
				LogData->push_back(&string[cur]);
				if (LogCallBack)LogCallBack(&string[cur]);
			}
			cur = i;
		}
		else if (string[i] == TEXT("\n")[0])
		{
			string[i] = 0;
			i++;	
			if (string[cur]) {
				LogData->push_back(&string[cur]);
				if (LogCallBack)LogCallBack(&string[cur]);
			}
			cur = i;
		}
	}
	if (string[cur]) {
		LogData->push_back(&string[cur]);
		if (LogCallBack)LogCallBack(&string[cur]);
	}
}

int32 BearCore::BearLog::GetBuildImpl(const char * date, int32 start_year, int32 start_month, int32 start_day)
{
	static const bchar* month_id[12] =
	{
		TEXT("Jan"), TEXT("Feb"), TEXT("Mar"),TEXT("Apr"),TEXT("May"), TEXT("Jun"), TEXT("Jul"), TEXT("Aug"),TEXT("Sep"), TEXT("Oct"), TEXT("Nov"), TEXT("Dec")
	};
	int32 build_id = 0;
	static int days_in_month[12] =
	{
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	BearString data;
	data.append_printf(TEXT(BEAR_PRINT_ANSI), date);
	BearString16 month;
	uint32 days = 0, year = 0;
	data.scanf(TEXT("%s %d %d"), month, &days, &year);
	int32 months = 0;
	for (int i = 0; i < 12; i++)
	{
		if (BearString::Compare(month, month_id[i]) != 0)
			continue;

		months = i;
		break;
	}

	build_id = (year - start_year) * 365 + days - start_day;

	for (int i = 0; i < months; ++i)
		build_id += days_in_month[i];

	for (int i = 0; i < start_month - 1; ++i)
		build_id -= days_in_month[i];
	data.clear();
	return build_id;
}
