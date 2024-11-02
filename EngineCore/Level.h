#pragma once
#include "GameMode.h"

// ���� :
class ULevel
{
public:
	friend class USpriteRendererComponent;
	friend class UEngineAPICore;
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void BeginPlay();
	void EndPlay();
	void Tick(float _DeltaTime);
	void Render();

	template <typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;

		//NewActor->BeginPlay();
		WaitForBeginPlay.push(NewActor);
		
		return NewActor;
	}
protected:

private:
	void SwapBuffer();
	void ScreenClear();
	void PushRenderer(class USpriteRendererComponent* _Renderer);
	void ChangeRenderOrder(class USpriteRendererComponent* _Renderer, int _PrevOrder);

	// ���ӷ����� �������� ���� ������ �غ� ��Ű�� �Լ�
	template <typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		GameMode->World = this;
		MainPawn->World = this;

		//GameMode->GetWorld = this;
		//GameMode->BeginPlay();
		//MainPawn->BeginPlay();
		WaitForBeginPlay.push(GameMode);
		WaitForBeginPlay.push(MainPawn);
	}

	AGameMode* GameMode = nullptr;
	AActor* MainPawn = nullptr;

	std::list<AActor*> AllActors;
	std::queue<AActor*> WaitForBeginPlay;
	std::map<int, std::list<class USpriteRendererComponent*>> AllRenderers;
};

