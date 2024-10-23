#pragma once
#include <Windows.h>
#include <string>
#include <map>

const std::string defaultClassName = "Default";
const std::string defaultTitleName = "Window";

// Ό³Έν :
class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	static bool IsWindowClass(const std::string_view _Text);
	static int WindowMessageLoop();

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

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	HWND WindowHandle;
};

