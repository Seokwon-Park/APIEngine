#include "EngineWindow.h"

HINSTANCE UEngineWindow::hInstance = nullptr;

void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
	hInstance = _Instance;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int UEngineWindow::WindowMessageLoop()
{
	// 단축키 인데 게임
// HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		// 단축키를 아예 안사용하므로 단축키를 처리한다는 일 자차게 없으므로 의미가 없는 코드가 되었다.
		if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

UEngineWindow::UEngineWindow()
{
	// 선생님은 다 멀티바이트 형태로 함수들을 사용하겠다고 했으므로 
	// WNDCLASSEXW => WNDCLASSEXA 
	WNDCLASSEXA wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	// wcex.hInstance = nullptr;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;
	// wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExA(&wcex);

	WindowHandle = CreateWindowA("DefaultWindow", "MainWindow", WS_OVERLAPPEDWINDOW,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!WindowHandle)
	{
		return;
	}
}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Open()
{
	// 단순히 윈도창을 보여주는 것만이 아니라
	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);
	// ShowWindow(WindowHandle, SW_HIDE);
}

