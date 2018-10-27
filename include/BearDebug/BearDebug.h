#pragma once
namespace BearCore
{
class BEARTOOL_API BearDebug
	{
		BEAR_CLASS_STATIC(BearDebug);
	public:
		static void DebugBreak();
		static void FatalError(const bchar*text, ...);
		static void ErrorPrintf(const bchar*text, ...);
	};
}