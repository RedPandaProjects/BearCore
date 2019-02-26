#include "BearCore.hpp"
#ifdef WINDOWS
#include "BugTrap.h"
#pragma warning(disable:4091)
#include <dbghelp.h> // MiniDump flags
#endif

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lzo/lzoconf.h>
#include <lzo/lzo1x.h>
#include <zlib/zlib.h>

extern BearCore::BearVector<BearCore::BearStringConteniar> *LogData ;
static bool bInitialize=false;
extern BearCore::BearStringPath LogFileOut;
extern lzo_voidp GLZOWrkmem;

#ifdef WINDOWS
extern void CALLBACK GErrorHandler(INT_PTR);
#endif

z_stream GzlibStream;
void BearCore::Initialize(const bchar * app_name,  const bchar * email)
{
#ifdef LINUX 
#ifdef UNICODE
	fwide (stdout,1);
	fputws(L"",stdout);
	BEAR_RASSERT(fwide(stdout,0)>0);
#else
	fwide (stdout,0);
	fputs(L"",stdout);
	BEAR_RASSERT(fwide(stdout,0)==0);
#endif

	
#endif
	BEAR_ASSERT(!bInitialize);
	bear_fill(GzlibStream);

	BearMemory::DebugOff();
	LogData = new BearVector<BearStringConteniar>;
	LogData->reserve(1024);
	BearLog::Printf(TEXT("BearCore build " BEAR_PRINT_CURRENT), *BearLog::GetBuild(2015, 07, 27));

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
	BT_SetFlags(/**/BTF_DETAILEDMODE | /**BTF_EDIETMAIL |*/BTF_ATTACHREPORT /**| BTF_LISTPROCESSES *| BTF_SHOWADVANCEDUI *| BTF_SCREENCAPTURE*/);

	if(email)
	BT_SetSupportEMail(email);
	BT_SetDumpType(MiniDumpWithDataSegs | MiniDumpWithIndirectlyReferencedMemory);
	BT_SetAppName(app_name);
	BT_SetPreErrHandler(GErrorHandler, 0);
#endif
	bInitialize = true;

	BEAR_FATALERROR(lzo_init() == LZO_E_OK, TEXT("LZO Не поддерживается"));

	BEAR_FATALERROR(inflateInit(&GzlibStream) == Z_OK, TEXT("ZLIB Не поддерживается"));	inflateEnd(&GzlibStream);
}






BEARTOOL_API void BearCore::Destroy()
{

	BEAR_ASSERT(bInitialize);
	if (GLZOWrkmem)bear_free(GLZOWrkmem);
	BearProjectTool::Destory();
	BearLog::Flush();
	BearMemory::DebugOff();
	BearMemory::DebugCheak();
	delete LogData;
	bInitialize = false;
}
