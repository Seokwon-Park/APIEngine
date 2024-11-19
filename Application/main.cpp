//#include <Windows.h>
//#include <EnginePlatform/EngineWindow.h>
//#include <EngineBase/EngineDelegate.h>
//
//#pragma comment (lib, "EngineBase.lib")
//#pragma comment (lib, "EnginePlatform.lib")
#include "aepch.h"
#include <PuyoPuyoContents/PuyoPuyoContentsCore.h>

#include <EngineCore/EngineAPICore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "PuyoPuyoContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	srand(time(nullptr));
	PuyoPuyoContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}