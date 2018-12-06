#pragma once
namespace BearCore
{
	class BEARTOOL_API BearDebug
	{
		BEAR_CLASS_STATIC(BearDebug);
	public:
		static void DebugBreak();
		BEAR_FUNCTION_DEBUG(static void, DebugPrintf, const bchar * text, ...);
		static void FatalError(const bchar * chenk, const bchar * name, const bchar * function_name, uint32 line, const bchar*text, ...);
		static void ErrorMessage(const bchar*text, ...);
	private:
		static void ShowMessage(const bchar*title, const bchar*text);
	};
}