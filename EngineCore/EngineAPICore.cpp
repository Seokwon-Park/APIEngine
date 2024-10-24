#include "aepch.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;


UEngineAPICore::UEngineAPICore()
{

}

UEngineAPICore::~UEngineAPICore()
{
	for (auto& Level: Levels)
	{
		if (nullptr != Level.second)
		{
			delete Level.second;
			Level.second = nullptr;
		}
	}

	Levels.clear();
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();

	EngineDelegate StartDelegate(std::bind(&EngineBeginPlay));
	EngineDelegate FrameDelegate(std::bind(&EngineTick));
	return UEngineWindow::WindowMessageLoop(StartDelegate, FrameDelegate);
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string LevelName = _LevelName.data();

	if (false == Levels.contains(LevelName))
	{
		MSGASSERT(LevelName + "��� �̸��� ������ �������� �ʽ��ϴ�.");
	}

	CurrentLevel = Levels[LevelName];
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	UserCore->Tick();
	MainCore->Tick();
}


void UEngineAPICore::Tick()
{
	if (nullptr == CurrentLevel)
	{
		MSGASSERT("���� �ھ ���� ������ �������� �ʾҽ��ϴ�.");
		return;
	}
	CurrentLevel->Tick();
	CurrentLevel->Render();
}


