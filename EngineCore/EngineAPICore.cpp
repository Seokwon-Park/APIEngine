#include "aepch.h"
#include "EngineAPICore.h"
#include "ImageManager.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
	:CurLevel(nullptr), DeltaTimer(UEngineTimer()), EngineMainWindow(UEngineWindow())

{

}

UEngineAPICore::~UEngineAPICore()
{
	for (auto& Level : Levels)
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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(7946);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	EngineDelegate StartDelegate(std::bind(&EngineBeginPlay));
	EngineDelegate FrameDelegate(std::bind(&EngineTick));
	return UEngineWindow::WindowMessageLoop(StartDelegate, FrameDelegate);
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string LevelName = _LevelName.data();

 	if (false == Levels.contains(LevelName))
	{
		MSGASSERT(LevelName + "라는 이름의 레벨이 존재하지 않습니다.");
	}

	CurLevel = Levels[LevelName];
	CurLevel->BeginPlay();
}

// TODO : 나중에 시간날 때 수정
void UEngineAPICore::LoadResources(std::string_view _FolderName)
{
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT(std::string(_FolderName) + "라는 이름의 리소스 폴더를 찾지 못했습니다.");
		return;
	}

	//이미지 리소스 로드
	LoadImageResources(Dir.ToString());
	LoadSoundResources();
}

// TODO : 나중에 시간날 때 수정
void UEngineAPICore::LoadImageResources(std::string_view _FolderDir, 
	std::string_view _ImageFolderName)
{
	UEngineDirectory Dir(_FolderDir);
	Dir.AppendDirectory(_ImageFolderName);

	if (false == Dir.IsExists())
	{
		MSGASSERT("이미지 리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].ToString();
		UImageManager::GetInstance().Load(FilePath);
	}
}

// TODO : 나중에 시간날 때 수정
void UEngineAPICore::LoadSoundResources(std::string_view _FolderName)
{
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
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();


	UEngineInput::GetInst().KeyCheck(DeltaTime);
	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다.");
		return;
	}

	UEngineInput::GetInst().EventCheck();
	CurLevel->Tick(DeltaTime);
	CurLevel->Render();
}


