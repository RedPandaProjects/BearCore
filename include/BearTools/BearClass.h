#pragma once

#define BEAR_CLASS_STATIC(CL)\
	CL()=delete;\
	CL&operator=(const CL&cl)=delete;
	
#define BEAR_FUNCTION_DELETE(TYPE,FUN)\
	TYPE FUN()=delete;
	
#define BEAR_CLASS_NO_COPY(CL)\
	CL(const CL&cl) = delete;\
	CL(CL&&cl) = delete;\
	CL&operator=(const CL&cl) = delete;\
	CL&operator=(CL&&cl) = delete;
	
#ifdef DEBUG
#define BEAR_FUNCTION_DEBUG(RET,FUN,ARGS)\
	RET FUN(ARGS);
#else
#define BEAR_FUNCTION_DEBUG(RET,FUN,ARGS)\
	inlien RET FUN(ARGS){}	
#endif