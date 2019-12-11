#pragma once
class BEARTOOL_API BearDebug
{
	BEAR_CLASS_STATIC(BearDebug);
public:
	static void DebugBreak();
	
	static void FatalError(const bchar * chenk, const bchar * name, const char * function_name, uint32 line, const bchar*text, ...);
	static void ErrorMessage(const bchar*text, ...);
	static void SetCallBack(void(*callback)(void));
private:
	static void ShowMessage(const bchar*title, const bchar*text);
};
