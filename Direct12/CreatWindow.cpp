#include "CreatWindow.h"

// Handle to the window
extern HWND hwnd = NULL;
// name of the window (not the title)
extern  LPCTSTR WindowName = L"Miccall App";
// title of the window
extern  LPCTSTR WindowTitle = L"Miccall Window";
// width and height of the window
extern  int Width = 800;
extern  int Height = 600;
// is window full screen?
extern  bool FullScreen = false;
// we will exit the program when this becomes false
extern  bool isRuning = true;

// create and show the window
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, bool fullscreen)
{
	if (fullscreen)
	{
		HMONITOR hmon = MonitorFromWindow(hwnd,
			MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
		GetMonitorInfo(hmon, &mi);

		Width = mi.rcMonitor.right - mi.rcMonitor.left;
		Height = mi.rcMonitor.bottom - mi.rcMonitor.top;
	}

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	hwnd = CreateWindowEx(NULL,
		WindowName,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Width, Height,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating window",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (fullscreen)
	{
		SetWindowLong(hwnd, GWL_STYLE, 0);
	}

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// ESC key 
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				// 弹框提示 
				if (MessageBox(0, L"Are you sure you want to exit?",
					L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					isRuning = false;
					DestroyWindow(hwnd);
				}
			}
			return 0;
		
		// 关闭按钮 
		case WM_DESTROY: // x button on top right corner of window was pressed
			isRuning = false;
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}

void mainloop()
{
	// 消息 
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (isRuning)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			D3DLib* d = D3DLib::getInstance();
			d->Update();
			d->Render();
			// update the game logic
			// execute the command queue (rendering the scene is the result of the gpu executing the command lists)
		}
	}
}

