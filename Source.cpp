#include <atlbase.h>
CComModule _Module;
#include <atlwin.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND	hBrowser;
	switch (msg)
	{
	case WM_CREATE:
		AtlAxWinInit();
		hBrowser = CreateWindow(TEXT("AtlAxWin120"),
			TEXT("mshtml:<iframe width=\"100%\" height=\"100%\" src=\"http://www.youtube.com/embed/JfgOjtq440o?rel=0&#038;vq=hd1080\"></iframe>"),
			WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, 0,
			((LPCREATESTRUCT)lParam)->hInstance,
			0);
		break;
	case WM_SIZE:
		MoveWindow(hBrowser, 0, 0, LOWORD(lParam), HIWORD(lParam), 1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	_Module.Init(NULL, hInstance);
	MSG msg;
	WNDCLASS wndclass = {
		0,
		WndProc,
		0,
		0,
		hInstance,
		0,
		0,
		0,
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("YouTube"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
		);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	_Module.Term();
	return msg.wParam;
}