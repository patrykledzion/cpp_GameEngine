#include "Window.h"


namespace nWindow {
	HMENU Window::contextMenu;
	ATOM Window::WINDOW_CLASS = NULL;

	LRESULT Wndproc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam
	) {
		Window* wnd = (Window*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
		switch (uMsg)
		{
		case WM_RBUTTONUP:
		{
			for (auto& handle : wnd->rbClickHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			
			break;
		}

		case WM_LBUTTONUP:
		{ 
			for (auto& handle : wnd->lbClickHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		case WM_MOUSEMOVE:
		{ 
			for (auto& handle : wnd->mouseMoveHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		case WM_KEYDOWN:
		{ 
			for (auto& handle : wnd->keyboardDownHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		case WM_KEYUP:
		{ 
			for (auto& handle : wnd->keyboardUpHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		case WM_COMMAND:
		{ 
			for (auto& handle : wnd->contextMenuHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		case WM_KILLFOCUS:
		{ 
			for (auto& handle : wnd->unfocusHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		case WM_SETFOCUS:
		{ 
			for (auto& handle : wnd->focusHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break; 
		}

		case WM_SIZE:
		{
			wnd->OnResize(hWnd, uMsg, wParam, lParam);
			for (auto& handle : wnd->resizeHandle)
			{
				if (handle == NULL)break;;
				handle(hWnd, uMsg, wParam, lParam);
			}
			break;
		}

		default:
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
		}
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}

	void Window::InitWindowClass()
	{
		WNDCLASS wndClass;
		wndClass.style = 0;
		wndClass.lpfnWndProc = &Wndproc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = NULL;
		wndClass.hIcon = NULL;
		wndClass.hCursor = NULL;
		wndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = L"WINDOW";

		this->WINDOW_CLASS = (ATOM)RegisterClass(&wndClass);

	}
	void nWindow::Window::InitWindow()
	{
		if (Window::WINDOW_CLASS != NULL)return;
		this->InitWindowClass();
		if (Window::WINDOW_CLASS == NULL)return;
		ATOM wndClass = Window::WINDOW_CLASS;
		HWND wnd = CreateWindowEx(
			0,
			(LPCWSTR)Window::WINDOW_CLASS,
			(LPWSTR)this->title,
			WS_TILEDWINDOW,
			100, 100,
			this->width, this->height,
			NULL, NULL, NULL, NULL
		);

		if (!wnd)return;
		this->windowPtr = wnd;
		SetWindowLongPtrW(this->windowPtr, GWLP_USERDATA, (LONG_PTR)this);
		ShowWindow(wnd, SW_NORMAL);
		UpdateWindow(wnd);
	}

	void nWindow::Window::InitGL()
	{
		if (this->windowPtr == NULL)return;

		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.iLayerType = PFD_MAIN_PLANE;

		HDC hdc = GetDC(this->windowPtr);
		this->hdc = hdc;
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if (!SetPixelFormat(hdc, pixelFormat, &pfd)) {
			MessageBox(NULL, L"Failed to set pixel format", L"Error", MB_OK);
			return;
		}

		HGLRC hglrc = wglCreateContext(hdc);
		

		if(!hglrc || !wglMakeCurrent(hdc, hglrc))
		{
			int x = 2137;
			MessageBox(NULL, L"Failed to initialize OpenGL context", L"Error", MB_OK);
		}

		RECT rcCli;
		GetClientRect(WindowFromDC(hdc), &rcCli);
		this->width = rcCli.right;
		this->height = rcCli.bottom;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		gluOrtho2D(0, this->width, this->height, 0);

	}

	void Window::HandleEvents()
	{
		MSG msg;
		if (PeekMessageA(&msg, 0, 0, 0, 1))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else {
			Sleep(1);
		}
	}


	void Window::OnResize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);

		RECT rect;
		GetClientRect(this->windowPtr, &rect);
		this->width = rect.right;
		this->height = rect.bottom;
		glViewport(0, 0, this->width, this->height);
		gluOrtho2D(0, this->width, 0, this->height);
	}

	Image* Window::OpenBMP(std::string filename)
	{
		if (filename.empty())return nullptr;
		return new Image(filename); 
	}


	nWindow::Window::Window(const char* title, int width, int height) : title((char*)title), width(width), height(height)
	{
		this->InitWindow();
		this->InitGL();
	}

	void Window::Update()
	{
		this->HandleEvents();
	}

	void Window::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(this->hdc);
		glFlush();
	}

	void Window::CreateContextMenu(std::vector<struct ContextMenuOption> options, HWND hWnd)
	{
		Window::contextMenu = CreatePopupMenu();

		for (struct ContextMenuOption& element : options)
		{ 
			AppendMenu(Window::contextMenu, MF_STRING, element.id, (LPCWSTR)element.value);
			if (element.isLast)AppendMenu(Window::contextMenu, MF_SEPARATOR, 0, NULL);
		}

		SetForegroundWindow(hWnd);
		POINT pt;
		GetCursorPos(&pt);
		TrackPopupMenu(Window::contextMenu, 0, pt.x, pt.y, 0, hWnd, NULL);
	}
	void Window::ShowMessageBox(LPCWSTR title, LPCWSTR message, UINT type)
	{
		MessageBox(NULL, message, title, type);
	}
}

