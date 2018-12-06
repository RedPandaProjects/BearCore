static bsize count = 0;
static LRESULT CALLBACK globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(handle, message, wParam, lParam);
}
void BearCore::BearWindow::create(const bchar * Title, uint32 width, uint32 height, bool fullscrean)
{
	close();
	HINSTANCE hMainInst = GetModuleHandle(NULL);
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(0);
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = globalOnEvent;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(69, 22, 28));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("BEAR");
	wc.cbSize = sizeof(WNDCLASSEX);


	RegisterClassEx(&wc);
	count++;
	DWORD Style = WS_OVERLAPPED | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN ;
	m_ref = CreateWindowEx(WS_EX_APPWINDOW, TEXT("BEAR"), TEXT(""), Style, 0, 0, 1, 1, NULL, NULL, hMainInst, NULL);
	ShowWindow((HWND)m_ref, SW_SHOW);
	setSize(width, height);
	setFullScreen(fullscrean);
}

bool BearCore::BearWindow::draw(bool onclosed)
{
	MSG msg;
	if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT&& onclosed)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT && onclosed)
		return false;
	return true;
}

void BearCore::BearWindow::setTitle(const bchar * Title)
{
	if (!m_ref)
		return;
	SetWindowText((HWND)m_ref, Title);
	m_title = Title;
}

void BearCore::BearWindow::setSize(uint32 width, uint32 height)
{
	if (!m_ref)
		return;
	if (!m_bfullscreen)
	{
		uint32 xpos = ((uint32)GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
		uint32 ypos = ((uint32)GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

		RECT rectangle = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
		AdjustWindowRect(&rectangle, GetWindowLong((HWND)m_ref, GWL_STYLE), false);
		int w = rectangle.right - rectangle.left;
		int h = rectangle.bottom - rectangle.top;
		SetWindowPos((HWND)m_ref, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
		SetWindowPos((HWND)m_ref, NULL, xpos, ypos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos((HWND)m_ref, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED);
	}
	m_size.array[0] = width;
	m_size.array[1] = height;
}

void BearCore::BearWindow::setFullScreen(bool fs)
{
	if (!m_ref)
		return;
	if (fs)
	{
		SetWindowLong((HWND)m_ref, GWL_STYLE, WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE);
		m_bfullscreen = true;
		ShowWindow((HWND)m_ref, SW_MAXIMIZE);
		return;
	}
	else
	{
		SetWindowLong((HWND)m_ref, GWL_STYLE, WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
		m_bfullscreen = false;
		ShowWindow((HWND)m_ref, SW_SHOW);
		setSize(m_size.x, m_size.y);
	}
}




bool BearCore::BearWindow::isActive() const
{
	return GetActiveWindow() == (HWND)m_ref;
}

void BearCore::BearWindow::close()
{
	DestroyWindow((HWND)m_ref);
	if(--count)UnregisterClass(TEXT("BEAR"), GetModuleHandle(NULL));
}
