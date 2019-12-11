#pragma once
typedef void(*BearLogCallBack)(const bchar*) ;
class BEARTOOL_API BearLog
{
	BEAR_CLASS_STATIC(BearLog);
public:
	static void Printf(const bchar*text, ...);
	static void Flush();
	static BearLogCallBack SetCallBack(BearLogCallBack call_back);
	static const BearVector<BearString>&Lock();
	static void Unlock();
	static void SetFile(const bchar*file);
	inline static BearString GetBuild(int32 year, int32 month, int32 day)
	{
#ifdef WINDOWS
		return BearString().append_printf(TEXT("%d," BEAR_PRINT_STR), GetBuildImpl(__DATE__, year, month, day), __DATE__);
#else 
		return BearString().append_printf(TEXT("%d," BEAR_PRINT_STR), GetBuildImpl(__DATE__, year, month, day), __DATE__);
#endif
	
	}
	BEAR_FUNCTION_DEBUG(static void, DebugPrintf, const bchar * text, ...);
private:
	static void Push( bchar*string);
	static int32 GetBuildImpl(const char* date, int32 year, int32 month, int32 day);
};
