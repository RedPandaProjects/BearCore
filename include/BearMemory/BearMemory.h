#pragma once
class BEARTOOL_API BearMemory
{
public:
	static void* Malloc(bsize size
#ifdef DEBUG
		,const char*name
#endif
	);
	static void* Realloc(void*old, bsize new_size
#ifdef DEBUG
		,const char*name
#endif
	);

	static void  Free(void*ptr);
	static void Swap(void*a, void*b, bsize size);
	BEAR_FUNCTION_DEBUG(static void, DebugCheak,);
	BEAR_FUNCTION_DEBUG(static void, DebugOn, );
	BEAR_FUNCTION_DEBUG(static void, DebugOff, );
};