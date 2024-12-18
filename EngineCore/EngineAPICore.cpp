#include "aepch.h"
#include "EngineAPICore.h"
#include "ImageManager.h"
#include "AudioManager.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInputSystem.h>
#include <EnginePlatform/EngineWindow.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
	:CurLevel(nullptr), NextLevel(nullptr), DeltaTimer(UEngineTimer()), EngineMainWindow(UEngineWindow())

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

	//사운드를 먼저 할당해제시켜줘야 경고가 안뜸
	UAudioManager::GetInstance().ReleaseSounds();
	UEngineAudio::Release();
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(14867);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);
	UEngineAudio::Init();

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	UEngineDelegate StartDelegate(std::bind(&EngineBeginPlay));
	UEngineDelegate FrameDelegate(std::bind(&EngineTick));
	return UEngineWindow::WindowMessageLoop(StartDelegate, FrameDelegate);
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string UpperName = UEngineStringHelper::ToUpper(_LevelName);

	if (false == Levels.contains(UpperName))
	{
		MSGASSERT(UpperName + "라는 이름의 레벨이 존재하지 않습니다.");
	}

	NextLevel = Levels[UpperName];
	//CurLevel->BeginPlay();
}

// TODO : 나중에 시간날 때 수정
void UEngineAPICore::LoadResources(std::string_view _FolderName)
{
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory(_FolderName))
	{
		MSGASSERT(std::string(_FolderName) + "라는 이름의 리소스 폴더를 찾지 못했습니다.");
		return;
	}

	//이미지 리소스 로드
	LoadImageResources(Dir.ToString());
	LoadSoundResources(Dir.ToString());
}

// TODO : 나중에 시간날 때 수정
void UEngineAPICore::LoadImageResources(std::string_view _FolderName,
	std::string_view _ImageFolderName)
{
	UEngineDirectory Dir(_FolderName);
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
void UEngineAPICore::LoadSoundResources(std::string_view _FolderName, std::string_view _SoundFolderName)
{
	UEngineDirectory Dir(_FolderName);
	Dir.AppendDirectory(_SoundFolderName);

	if (false == Dir.IsExists())
	{
		MSGASSERT("사운드 리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> SoundFiles = Dir.GetAllFile();
	for (size_t i = 0; i < SoundFiles.size(); i++)
	{
		std::string FilePath = SoundFiles[i].ToString();
		UAudioManager::GetInstance().Load(FilePath);
	}
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
	CheckLevel();
	
	UEngineInputSystem::GetInstance().KeyCheck(DeltaTime);

	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다.");
		return;
	}

	UEngineAudio::AudioUpdate();
	UEngineEventSystem::UpdateEvents(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->Render();
	CurLevel->Release();
}

void UEngineAPICore::CheckLevel()
{
	if (IsCurLevelRemoved ==true && CurLevel != nullptr)
	{
		delete CurLevel;
		IsCurLevelRemoved = false;
		CurLevel = nullptr;
	}
	if (nullptr != NextLevel)
	{
		if (CurLevel == NextLevel)
		{
			DBGPRINT("같은 레벨로 이동을 시도했습니다.");
			return;
		}
		if (nullptr != CurLevel)
		{
			CurLevel->EndPlay();
		}

		CurLevel = NextLevel;

		NextLevel->BeginPlay();
		NextLevel = nullptr;
	}
}


