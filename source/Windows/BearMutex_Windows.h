
BearCore::BearMutex::BearMutex()
{
	InitializeCriticalSection(&m_mutex);
}

BearCore::BearMutex::~BearMutex()
{
	DeleteCriticalSection(&m_mutex);
}

void BearCore::BearMutex::Lock()
{
	EnterCriticalSection(&m_mutex);
}

void BearCore::BearMutex::Unlock()
{
	LeaveCriticalSection(&m_mutex);
}

void BearCore::BearMutex::Swap(BearMutex & r)
{
	bear_swap(r.m_mutex, m_mutex);
}
