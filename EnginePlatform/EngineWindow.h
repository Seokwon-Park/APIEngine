#pragma once

// user header
#include <EngineBase/EngineDelegate.h>

const std::string defaultClassName = "Default";
const std::string defaultTitleName = "Window";

class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	// constructer destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = defaultClassName);
	void Open(std::string_view _TitleName = defaultTitleName);

	inline HDC GetBackBuffer()
	{
		return BackBuffer;
	}
protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	HDC BackBuffer;
	HWND WindowHandle;
};

