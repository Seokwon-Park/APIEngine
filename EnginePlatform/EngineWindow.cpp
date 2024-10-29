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
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
	{

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
		MSGASSERT("같은 이름의 윈도우 클래스를 2번 등록했습니다." + std::string(_Class.lpszClassName));
		return;
	}

	RegisterClassExA(&_Class);

	WindowClasses.insert(std::make_pair(_Class.lpszClassName, _Class));
}

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
	MSG msg = MSG();

	// GetMessage
	// 메세지가 없다 => 영원히 기다림
	// 메세지가 있다 => 처리하고 리턴

	// PeekMessage
	// 처리하고 리턴
	// 메세지가 없다 => 리턴
	// 메세지가 있다 => 처리하고 리턴
	if (true == _StartFunction.IsBind())
	{
		_StartFunction();
	}

	while (WindowCount)
	{
		// if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))  
		// => 윈도우 단축키 자체를 사용하지
		// 않을 것이므로 그냥 무시

		// PM_REMOVE == 내가 처리할때 지금까지 쌓인 메세지 다지우기
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 메세지 처리하고 나서 게임엔진 루프.
		if (true == _FrameFunction.IsBind())
		{
			_FrameFunction();
		}
	}

	return static_cast<int>(msg.wParam);
}

void UEngineWindow::SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale)
{
	if (WindowSize != _Scale)
	{
		if (nullptr != BackBufferImage)
		{
			delete BackBufferImage;
			BackBufferImage = nullptr;
		}
		BackBufferImage = new UEngineWinImage();
		BackBufferImage->Create(WindowImage, _Scale);
	}

	WindowSize = _Scale;

	RECT Rect = { 0,0,_Scale.iX(), _Scale.iY() };

	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);

	::SetWindowPos(WindowHandle, nullptr, _Pos.iX(), _Pos.iY(),
		Rect.right - Rect.left,
		Rect.bottom - Rect.top,
		SWP_NOZORDER);
}



UEngineWindow::UEngineWindow()
	:BackBufferImage(nullptr), WindowImage(nullptr), WindowHandle(nullptr)
{

}

UEngineWindow::~UEngineWindow()
{
	if (nullptr != WindowImage)
	{
		delete WindowImage;
		WindowImage = nullptr;
	}

	if (nullptr != BackBufferImage)
	{
		delete BackBufferImage;
		BackBufferImage = nullptr;
	}
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
	if (false == WindowClasses.contains(_ClassName.data()))
	{
		MSGASSERT(std::string(_ClassName) + "등록하지 않은 클래스로 윈도우창을 만들려고 했습니다");
		return;
	}

	WindowHandle = CreateWindow(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	/*WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, _ClassName.data(), _TitleName.data(), WS_POPUP,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), nullptr, nullptr, hInstance, nullptr);*/

	if (nullptr == WindowHandle)
	{
		MSGASSERT(std::string(_TitleName) + "윈도우 생성에 실패했습니다.");
		return;
	}

	HDC WindowDC = GetDC(WindowHandle);

	if (nullptr == WindowDC)
	{
		MSGASSERT("윈도우 HDC가 nullptr이었습니다.");
		return;
	}

	WindowImage = new UEngineWinImage();
	WindowImage->Create(WindowDC);
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

