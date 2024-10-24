#pragma once
// 여러분들이 여기에다가 이렇게 특정 헤더를 넣으면
// F5를 누를때마다. #include <Windows.h>가 재빌드 된다.
// 미리컴파일된 헤더를 사용하면
// 미리컴파일된 헤더에 넣어진 헤더는 빌드를하면 .pch파일에 빌드결과가 남고
// 그후에는 빌드되지 않는다.
// 컴파일 시간이 
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDebug.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

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

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

	void CreateLevel(std::string_view _LevelName)
	{
		ULevel* NewLevel = new ULevel();

		Levels.insert(std::make_pair(_LevelName.data(), NewLevel));
	}

	void OpenLevel(std::string_view _LevelName)
	{
		std::string LevelName = _LevelName.data();

		if (false == Levels.contains(LevelName))
		{
			MSGASSERT(LevelName + "라는 이름의 레벨이 존재하지 않습니다.");
		}

		CurrentLevel = Levels[LevelName];
	}

protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	UEngineWindow EngineMainWindow; // 엔진 메인 윈도우

	// 이녀석들이 돌아가야 게임이 돌아간다.
	void Tick();

	ULevel* CurrentLevel = nullptr;

	std::map<std::string, ULevel*> Levels;
};



