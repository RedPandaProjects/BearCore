#pragma once
#ifdef DEBUG
#define BEAR_ASSERT(A) if(!(A)){BearCore::BearDebug::DebugBreak();}
#else
#define BEAR_ASSERT(A) (void(A));
#endif
#define BEAR_RASSERT(A) if(!(A)){BearCore::BearDebug::DebugBreak();}
#define BEAR_FATALERROR(exp,text,...)if(!(exp)){BearCore::BearDebug::FatalError(TEXT( BEAR_TO_STRING(exp) ),TEXT(__FILE__),TEXT(__FUNCTION__),__LINE__,text, ##__VA_ARGS__);}
#define BEAR_ERRORMESSAGE(exp,text,...)if(!(exp)){BearCore::BearDebug::ErrorMessage(text, ##__VA_ARGS__);}
