#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰�
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

void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
	hInstance = _Instance;

	WNDCLASSEXA wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "Default";
	wcex.hIconSm = nullptr;
	CreateWindowClass(wcex);

}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
	if (WindowClasses.contains(_Class.lpszClassName))
	{
		MSGASSERT("���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�." + std::string(_Class.lpszClassName));
		return;
	}

	RegisterClassExA(&_Class);

	WindowClasses.insert(std::make_pair(_Class.lpszClassName, _Class));
}

int UEngineWindow::WindowMessageLoop()
{
	MSG msg;

	// �⺻ �޽��� ����
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	return (int)msg.wParam;
}



UEngineWindow::UEngineWindow()
	:WindowHandle(nullptr)
{

}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
	if (false == WindowClasses.contains(_ClassName.data()))
	{
		MSGASSERT(std::string(_ClassName) + "������� ���� Ŭ������ ������â�� ������� �߽��ϴ�");
		return;
	}

	WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (nullptr == WindowHandle)
	{
		MSGASSERT("������ ������ �����߽��ϴ�." + std::string(_TitleName));
		return;
	}
}


void UEngineWindow::Open(std::string_view _TitleName)
{
	if (nullptr == WindowHandle)
	{
		Create(defaultTitleName);
	}

	if (nullptr != WindowHandle)
	{
		ShowWindow(WindowHandle, SW_SHOW);
		UpdateWindow(WindowHandle);
	}
	// ShowWindow(WindowHandle, SW_HIDE);
}

