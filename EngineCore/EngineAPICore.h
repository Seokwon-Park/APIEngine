#pragma once
// �����е��� ���⿡�ٰ� �̷��� Ư�� ����� ������
// F5�� ����������. #include <Windows.h>�� ����� �ȴ�.
// �̸������ϵ� ����� ����ϸ�
// �̸������ϵ� ����� �־��� ����� ���带�ϸ� .pch���Ͽ� �������� ����
// ���Ŀ��� ������� �ʴ´�.
// ������ �ð��� 
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
			MSGASSERT(LevelName + "��� �̸��� ������ �������� �ʽ��ϴ�.");
		}

		CurrentLevel = Levels[LevelName];
	}

protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	UEngineWindow EngineMainWindow; // ���� ���� ������

	// �̳༮���� ���ư��� ������ ���ư���.
	void Tick();

	ULevel* CurrentLevel = nullptr;

	std::map<std::string, ULevel*> Levels;
};



