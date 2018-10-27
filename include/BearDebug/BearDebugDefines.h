#pragma once
#ifdef DEBUG
#define BEAR_ASSERT(A) if(!(A)){BearCore::BearDebug::DebugBreak();}
#else
#define BEAR_ASSERT(A) (void(0))
#endif

#define BEAR_FATALERROR(exp,text,...)if(!(exp)){BearCore::BearDebug::FatalError(text,__VA_ARGS__);}
	