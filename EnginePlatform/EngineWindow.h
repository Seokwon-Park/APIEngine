#pragma once

#include "EngineWinImage.h"
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDelegate.h>

const std::string DefaultClassName = "Default";
const std::string DefaultTitleName = "Window";

class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	static WNDCLASSEXA CreateWNDCLASSEX();

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);
	void SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale);

	// constructer destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = DefaultClassName);
	void Open(std::string_view _TitleName = DefaultTitleName);

	inline FVector2D GetWindowSize() const
	{
		return WindowSize;
	}

	inline UEngineWinImage* GetBackBufferImage() const
	{
		return BackBufferImage;
	}

	inline UEngineWinImage* GetWindowImage() const
	{
		return WindowImage;
	}
	//Temp
	inline HWND GetHandle()
	{
		return WindowHandle;
	}

	inline void SetWindowTitle(std::string_view Text)
	{
		SetWindowTextA(WindowHandle, Text.data());
	}
protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	FVector2D WindowSize;

	UEngineWinImage* BackBufferImage;
	UEngineWinImage* WindowImage;
	HWND WindowHandle;
};

