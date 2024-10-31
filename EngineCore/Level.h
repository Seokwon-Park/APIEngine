#pragma once
#include "GameMode.h"

// 설명 :
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
	void Tick(float _DeltaTime);
	void Render();

	template <typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;

		//NewActor->BeginPlay();
		AllActors.push_back(NewActor);
		return NewActor;
	}
protected:

private:
	void SwapBuffer();
	void ScreenClear();
	void PushRenderer(class USpriteRendererComponent* _Renderer);
	void ChangeRenderOrder(class USpriteRendererComponent* _Renderer, int _PrevOrder);

	// 게임레벨과 메인폰을 만들어서 게임을 준비 시키는 함수
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

		AllActors.push_back(GameMode);
		AllActors.push_back(MainPawn);
	}

	AGameMode* GameMode = nullptr;
	AActor* MainPawn = nullptr;

	std::list<AActor*> AllActors;
	std::map<int, std::list<class USpriteRendererComponent*>> AllRenderers;
};

