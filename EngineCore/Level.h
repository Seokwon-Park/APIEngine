#pragma once
#include "GameMode.h"
#include "EnginePostProcess.h"
#include "EngineKeyEvent.h"


enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

// 설명 :
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

	virtual void BeginPlay();
	virtual void EndPlay();
	void EventCheck();
	void Tick(float _DeltaTime);
	void Render();
	void Release();

	void BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void()> _Function);


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

	template <typename PostProcessType>
	PostProcessType* AddPostProcess()
	{ 
		PostProcessType* NewPostProcess= new PostProcessType();

		UEnginePostProcess* PostProcessPtr = dynamic_cast<UEnginePostProcess*>(NewPostProcess);

		PostProcesses.push_back(NewPostProcess);

		return NewPostProcess;
	}


	void PivotDebugOn();
	void PivotDebugOff();


	// Camera -> 컴포넌트로 따로 뺄까?
	inline void SetCameraToMainPawn(bool _IsCameraToMainPawn) { IsCameraToMainPawn = _IsCameraToMainPawn; }
	inline void SetCameraPivot(FVector2D _Pivot) { CameraPivot = _Pivot; }
	inline void SetCameraPos(FVector2D _Pos) { CameraPos = _Pos; }
	AGameMode* GetGameMode()
	{
		return GameMode;
	}
	template<typename ActorType>
	ActorType* GetMainPawn()
	{
		ActorType* CastMainPawn = dynamic_cast<ActorType*>(MainPawn);
		return CastMainPawn;
	}
	inline FVector2D GetCameraPivot() const { return CameraPivot; }
	inline FVector2D GetCameraPos() const { return CameraPos; }
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
		WaitForBeginPlay.push(GameMode);
		WaitForBeginPlay.push(MainPawn);
	}


	AGameMode* GameMode;
	AActor* MainPawn;

	bool IsCameraToMainPawn = true;
	// 아래 포지션 2개가 카메라.
	FVector2D CameraPos;
	FVector2D CameraPivot;

	std::list<AActor*> AllActors;
	std::queue<AActor*> WaitForBeginPlay;
	std::map<int, std::list<class USpriteRendererComponent*>> AllRenderers;

	//Todo : 디버깅 기능땜에 만들어놓음
	//레벨 단에서 이벤트 설정을 해야하나? 여기다가 한다.
	std::map<int, UEngineKeyEvent> KeyEvents;

	std::vector<class UEnginePostProcess*> PostProcesses;
};

  