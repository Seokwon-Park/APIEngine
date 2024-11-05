#pragma once
#include "GameMode.h"

// ���� :
class ULevel : public UObject
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
	void Release();

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

	// Camera -> ������Ʈ�� ���� ����?
	inline void SetCameraToMainPawn(bool _IsCameraToMainPawn){IsCameraToMainPawn = _IsCameraToMainPawn;}
	inline void SetCameraPivot(FVector2D _Pivot){CameraPivot = _Pivot;}
	inline void SetCameraPos(FVector2D _Pos){CameraPos = _Pos;}
	inline FVector2D GetCameraPivot() const {return CameraPivot;}
	inline FVector2D GetCameraPos() const {return CameraPos;}
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

	AGameMode* GameMode;
	AActor* MainPawn;

	bool IsCameraToMainPawn = true;
	// �Ʒ� ������ 2���� ī�޶�.
	FVector2D CameraPos;
	FVector2D CameraPivot;

	std::list<AActor*> AllActors;
	std::queue<AActor*> WaitForBeginPlay;
	std::map<int, std::list<class USpriteRendererComponent*>> AllRenderers;
};

