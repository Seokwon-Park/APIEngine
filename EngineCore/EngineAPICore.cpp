#include "aepch.h"
#include "EngineAPICore.h"
#include "ImageManager.h"
#include "SoundManager.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
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

	//���带 ���� �Ҵ������������ ��� �ȶ�
	USoundManager::GetInstance().ReleaseSounds();
	UEngineAudio::Release();
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(252);

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
	std::string LevelName = _LevelName.data();

	if (false == Levels.contains(LevelName))
	{
		MSGASSERT(LevelName + "��� �̸��� ������ �������� �ʽ��ϴ�.");
	}

	NextLevel = Levels[LevelName];
	//CurLevel->BeginPlay();
}

// TODO : ���߿� �ð��� �� ����
void UEngineAPICore::LoadResources(std::string_view _FolderName)
{
	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory(_FolderName))
	{
		MSGASSERT(std::string(_FolderName) + "��� �̸��� ���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	//�̹��� ���ҽ� �ε�
	LoadImageResources(Dir.ToString());
	LoadSoundResources(Dir.ToString());
}

// TODO : ���߿� �ð��� �� ����
void UEngineAPICore::LoadImageResources(std::string_view _FolderName,
	std::string_view _ImageFolderName)
{
	UEngineDirectory Dir(_FolderName);
	Dir.AppendDirectory(_ImageFolderName);

	if (false == Dir.IsExists())
	{
		MSGASSERT("�̹��� ���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].ToString();
		UImageManager::GetInstance().Load(FilePath);
	}
}

// TODO : ���߿� �ð��� �� ����
void UEngineAPICore::LoadSoundResources(std::string_view _FolderName, std::string_view _SoundFolderName)
{
	UEngineDirectory Dir(_FolderName);
	Dir.AppendDirectory(_SoundFolderName);

	if (false == Dir.IsExists())
	{
		MSGASSERT("���� ���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	std::vector<UEngineFile> SoundFiles = Dir.GetAllFile();
	for (size_t i = 0; i < SoundFiles.size(); i++)
	{
		std::string FilePath = SoundFiles[i].ToString();
		USoundManager::GetInstance().Load(FilePath);
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

	if (nullptr == CurLevel)
	{
		MSGASSERT("���� �ھ ���� ������ �������� �ʾҽ��ϴ�.");
		return;
	}
	UEngineAudio::AudioUpdate();
	CurLevel->Tick(DeltaTime);
	CurLevel->Render();
	CurLevel->Release();
}

void UEngineAPICore::CheckLevel()
{
	if (nullptr != NextLevel)
	{
		if (CurLevel == NextLevel)
		{
			DBGPRINT("���� ������ �̵��� �õ��߽��ϴ�.");
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


