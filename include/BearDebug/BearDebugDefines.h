#pragma once
#ifdef DEBUG
#define BEAR_ASSERT(A) if(!(A)){BearDebug::DebugBreak();}
#else
#define BEAR_ASSERT(A) (void(A));
#endif
#define BEAR_RASSERT(A) if(!(A)){BearDebug::DebugBreak();}
#define BEAR_FATALERROR(exp,text,...)if(!(exp)){BearDebug::FatalError(TEXT( BEAR_TO_STRING(exp) ),TEXT(__FILE__),__FUNCTION__,__LINE__,text, ##__VA_ARGS__);}
#define BEAR_ERRORMESSAGE(exp,text,...)if(!(exp)){BearDebug::ErrorMessage(text, ##__VA_ARGS__);}
