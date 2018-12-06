#include <process.h>
static int32 FunctionTread(void*arg_)
{
	void**args = reinterpret_cast<void**>(arg_);
	auto*function = reinterpret_cast<BearFunctionRef*>(args[0]);
	auto*args_list = reinterpret_cast<BearArgumentsList*>(args[1]);
	function->CallWithArgumentsList<int32>(*args_list);
	bear_free(arg_);
	_endthreadex(0);
	return 0;

}

void BearCore::BearThread::Join(const char*name)
{
	if (!m_id) {
		void**arg = bear_alloc<void*>(sizeof(void*) * 2);
		arg[0] = reinterpret_cast<void*>(m_fun);
		arg[1] = reinterpret_cast<void*>(&m_arg);
		RunThread(name,(void*)FunctionTread, arg);
	}
}
void BearCore::BearThread::Wait()
{
	if (m_id)
	{
		BEAR_FATALERROR(m_thread != GetCurrentThreadId(), TEXT("Поток не может ждать самого себя"));
		WaitForSingleObject(m_id, INFINITE);
	}
}
void BearCore::BearThread::Terminate()
{
	if (m_id)
		TerminateThread(m_id, 0);
}
BearCore::BearThread::~BearThread()
{
	if (m_id)
		CloseHandle((HANDLE)m_id);
}
void BearCore::BearThread::Swap(BearThread & sw)
{
	m_arg.swap(sw.m_arg);
	bear_swap(m_fun,sw.m_fun);
	bear_swap(m_id, sw.m_id);
	bear_swap(m_thread, sw.m_thread);
}

const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)  
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.  
	LPCSTR szName; // Pointer to name (in user addr space).  
	DWORD dwThreadID; // Thread ID (-1=caller thread).  
	DWORD dwFlags; // Reserved for future use, must be zero.  
} THREADNAME_INFO;
#pragma pack(pop)  
static void SetThreadName(DWORD dwThreadID, const char* threadName) {
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;
#pragma warning(push)  
#pragma warning(disable: 6320 6322)  
	__try {
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
#pragma warning(pop)  
}

void BearCore::BearThread::RunThread(const char*name,void * fun, void * arg)
{
	m_id = reinterpret_cast<void*>(_beginthreadex(NULL, 0, (_beginthreadex_proc_type)fun, arg, 0, &m_thread));
	SetThreadName(static_cast<DWORD>(m_thread), name);
}
