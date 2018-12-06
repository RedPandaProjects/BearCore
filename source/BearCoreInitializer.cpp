#include "BearCore.hpp"
#ifdef WINDOWS
#include "BugTrap.h"
#pragma warning(disable:4091)
#include <dbghelp.h> // MiniDump flags
#endif
extern BearCore::BearVector<BearCore::BearStringConteniar> *LogData ;
static bool bInitialize=false;
extern BearCore::BearStringPath LogFileOut;
void BearCore::Initialize(const bchar * app_name, const bchar * log_path, const bchar * email)
{
	BEAR_ASSERT(!bInitialize);
	BearMemory::DebugOff();
	BearString::Copy(LogFileOut, log_path);
	BearString::Contact(LogFileOut, BEAR_PATH);
	BearString::Contact(LogFileOut, app_name);
	BearString::Contact(LogFileOut, TEXT(".txt"));
	LogData = new BearVector<BearStringConteniar>;
	LogData->reserve(1024);
	BearLog::Printf(TEXT("BearCore build %s"), *BearLog::GetBuild(2015, 07, 27));

#ifdef WINDOWS
	BT_InstallSehFilter();
	BT_SetActivityType(BTA_SHOWUI);
	BT_SetDialogMessage(
		BTDM_INTRO2,
		TEXT("���������� ������!!!")
	);
	BT_SetDialogMessage(
		BTDM_INTRO1,
		TEXT("��������� �� �����!!!")
	);
	BT_SetReportFormat(BTRF_TEXT);
	BT_SetFlags(/**/BTF_DETAILEDMODE | /**BTF_EDIETMAIL | /**/BTF_ATTACHREPORT /**| BTF_LISTPROCESSES /**| BTF_SHOWADVANCEDUI /**| BTF_SCREENCAPTURE/**/);

	if(email)
	BT_SetSupportEMail(email);
	BT_SetDumpType(MiniDumpWithDataSegs | MiniDumpWithIndirectlyReferencedMemory);
	BT_SetAppName(app_name);
#endif
	bInitialize = true;

}

BEARTOOL_API void BearCore::Destroy()
{
	BEAR_ASSERT(bInitialize);
	BearProjectTool::Destory();
	BearLog::Flush();
	BearMemory::DebugOff();
	BearMemory::DebugCheak();
	delete LogData;
	bInitialize = false;
}