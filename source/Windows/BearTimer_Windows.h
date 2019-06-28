#include <time.h>
#include <ctime>
#include <assert.h>
static double CyclesPerMicrosecond;
struct Initializer
{
	
	inline void Initialize()
	{
		static bool ok = false;
		if (ok)return;
		ok = true;
		LARGE_INTEGER Frequency;
		assert(QueryPerformanceFrequency(&Frequency));
		CyclesPerMicrosecond = (1.0 / Frequency.QuadPart)*(1000.0)*(1000.0);
	}

};
static Initializer init;
BearCore::BearTime BearCore::BearTimer::GetCurrentTime() 
{
	init.Initialize();
	LARGE_INTEGER Cycles;
	QueryPerformanceCounter(&Cycles);
	return BearTime(static_cast<int64>((Cycles.QuadPart * CyclesPerMicrosecond)));
}