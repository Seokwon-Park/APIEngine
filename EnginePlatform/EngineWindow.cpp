#include "aepch.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;
int WindowCount = 0;

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
		--WindowCount;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
	hInstance = _Instance;
	WNDCLASSEXA wcex = CreateWNDCLASSEX();
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

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
	MSG msg = MSG();

	// GetMessage
	// �޼����� ���� => ������ ��ٸ�
	// �޼����� �ִ� => ó���ϰ� ����

	// PeekMessage
	// ó���ϰ� ����
	// �޼����� ���� => ����
	// �޼����� �ִ� => ó���ϰ� ����
	_StartFunction();

	while (WindowCount)
	{
		// if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))  
		// => ������ ����Ű ��ü�� �������
		// ���� ���̹Ƿ� �׳� ����

		// PM_REMOVE == ���� ó���Ҷ� ���ݱ��� ���� �޼��� �������
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// �޼��� ó���ϰ� ���� ���ӿ��� ����.
		if (true == _FrameFunction.IsBind())
		{
			_FrameFunction();
		}
	}

	return (int)msg.wParam;
}



UEngineWindow::UEngineWindow()
	:BackBuffer(nullptr), WindowHandle(nullptr)
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
		MSGASSERT(std::string(_TitleName) + "������ ������ �����߽��ϴ�.");
		return;
	}

	BackBuffer = GetDC(WindowHandle);
}


void UEngineWindow::Open(std::string_view _TitleName)
{
	if (nullptr == WindowHandle)
	{
		Create(_TitleName);
	}

	if (nullptr == WindowHandle)
	{
		return;
	}

	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);
	++WindowCount;
	// ShowWindow(WindowHandle, SW_HIDE);
}

WNDCLASSEXA UEngineWindow::CreateWNDCLASSEX()
{
	WNDCLASSEXA Return;

	Return.cbSize = sizeof(WNDCLASSEX);
	Return.style = CS_HREDRAW | CS_VREDRAW;
	Return.lpfnWndProc = WndProc;
	Return.cbClsExtra = 0;
	Return.cbWndExtra = 0;
	Return.hInstance = hInstance;
	Return.hIcon = nullptr;
	Return.hCursor = LoadCursor(nullptr, IDC_ARROW);
	Return.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	Return.lpszMenuName = nullptr;
	Return.lpszClassName = DefaultClassName.c_str();
	Return.hIconSm = nullptr;

	return Return;
}

