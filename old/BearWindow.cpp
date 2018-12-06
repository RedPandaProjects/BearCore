#include "BearCore.hpp"
#ifdef WINDOWS
#include "Windows/BearWindow_Windows.h"
#elif LINUX
#endif
BearCore::BearWindow::BearWindow():m_ref(0)
{
}

BearCore::BearWindow::~BearWindow()
{
	close();
}

