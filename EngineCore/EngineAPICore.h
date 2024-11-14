#pragma once
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTimer.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

const std::string DefaultResourceFolder = "Resources";
const std::string DefaultImageFolder = "Images";
const std::string DefaultSoundFolder = "Sounds";

class UEngineAPICore
{
public:
	// constrcuter destructer
	UEngineAPICore();
	~UEngineAPICore();

	// delete Function
	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);

	static class UEngineAPICore* GetCore()
	{
		return MainCore;
	}
	static class UEngineWindow& GetEngineWindow()
	{
		return MainCore->EngineMainWindow;
	}

	static class UEngineWinImage* GetBackBuffer()
	{
		return MainCore->EngineMainWindow.GetBackBufferImage();
	}

	static class UEngineWinImage* GetWindowBuffer()
	{
		return MainCore->EngineMainWindow.GetWindowImage();
	}
	
	static float GetEngineDeltaTime()
	{
		return MainCore->GetDeltaTime();
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

	float GetDeltaTime() 
	{
		return DeltaTimer.GetDeltaTime();
	}

	inline static ULevel* GetCurrentLevel()
	{
		return MainCore->CurLevel;
	}

	template <typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		ULevel* NewLevel = new ULevel();

		// GameMode = 레벨의 특성을 설정하는 객체
		NewLevel->CreateGameMode<GameModeType, MainPawnType>();

		Levels.insert(std::make_pair(_LevelName.data(), NewLevel));

		return NewLevel;
	}

	void OpenLevel(std::string_view _LevelName);
	void LoadResources(std::string_view _FolderName = DefaultResourceFolder);
	void LoadImageResources(std::string_view _FolderName = DefaultResourceFolder,
		std::string_view _ImageFolderName = DefaultImageFolder);
	void LoadSoundResources(std::string_view _FolderName = DefaultSoundFolder);

protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	// 이녀석들이 돌아가야 게임이 돌아간다.
	void Tick();

	void CheckLevel();
	
	UEngineTimer DeltaTimer;
	UEngineWindow EngineMainWindow; // 엔진 메인 윈도우

	class ULevel* CurLevel;
	class ULevel* NextLevel;

	std::map<std::string, class ULevel*> Levels;
};



