#include "aepch.h"
#include "Level.h"
#include "EngineAPICore.h"
#include "SpriteRendererComponent.h"
#include "EngineKeyEvent.h"



void ULevel::BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void()> _Function)
{
	//if (false == Keys.contains(_KeyIndex))
	//{
	//	MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
	//	return;
	//}

	switch (_EventType)
	{
	case KeyEvent::Down:
		KeyEvents[_KeyIndex].DownEvents.push_back(_Function);
		break;
	case KeyEvent::Press:
		KeyEvents[_KeyIndex].PressEvents.push_back(_Function);
		break;
	case KeyEvent::Free:
		KeyEvents[_KeyIndex].FreeEvents.push_back(_Function);
		break;
	case KeyEvent::Up:
		KeyEvents[_KeyIndex].UpEvents.push_back(_Function);
		break;
	default:
		break;
	}
}

void ULevel::EventCheck()
{
	for (auto& Itr : KeyEvents)
	{
		UEngineKeyEvent& CurEvent = Itr.second;
		CurEvent.EventCheck(Itr.first);
	}
}

ULevel::ULevel()
	:GameMode(nullptr), MainPawn(nullptr)
{
}

//RAII - SpawnActor<>();
ULevel::~ULevel()
{
	while (false == WaitForBeginPlay.empty())
	{
		AActor* Actor = WaitForBeginPlay.front();
		WaitForBeginPlay.pop();
		if (nullptr != Actor)
		{
			delete Actor;
			Actor = nullptr;
		}
	}

	for (auto* PostProcess : PostProcesses)
	{
		if (nullptr != PostProcess)
		{
			delete PostProcess;
			PostProcess = nullptr;
		}
	}

	for (AActor* Actor : AllActors)
	{
		if (nullptr != Actor)
		{
			delete Actor;
			Actor = nullptr;
		}
	}
}

void ULevel::BeginPlay()
{
	BindAction(EKey::MouseRight, KeyEvent::Down, std::bind(&EngineDebugHelper::PivotDebugSwitch));

	// 이게 안되는 이유는 게임 중간에 스폰하는 액터에 대해서는 BeginPlay실행이 안돼
	//for (AActor* Actor : AllActors)
	//{
	//	if (nullptr != Actor)
	//	{
 // 			Actor->BeginPlay();
	//	}
	//}
}

void ULevel::EndPlay()
{
}

void ULevel::Tick(float _DeltaTime)
{

	//새로 스폰되는 액터에 대해서도 확인해줘야 하므로
	while (false == WaitForBeginPlay.empty())
	{
		AActor* SpawnedActor = WaitForBeginPlay.front();
		WaitForBeginPlay.pop();
		SpawnedActor->BeginPlay();
		AllActors.push_back(SpawnedActor);
	}

	EventCheck();
	for (AActor* Actor : AllActors)
	{
		if (false == Actor->IsActivated())
		{
			continue;
		}
		if (nullptr != Actor)
		{
			Actor->Tick(_DeltaTime);
		}
	}

}

void ULevel::Render()
{
	ScreenClear();

	if (true == IsCameraToMainPawn)
	{
		CameraPos = MainPawn->GetTransform().Location + CameraPivot;
	}

	for (auto& RenderList : AllRenderers)
	{
		for (USpriteRendererComponent* Renderer : RenderList.second)
		{
			if (false == Renderer->IsActivated())
			{
				continue;
			}
			Renderer->Render();
		}
	}

	for (auto Effect : PostProcesses)
	{
		Effect->EffectTick();
	}


	EngineDebugHelper::PrintEngineDebugRender();

	SwapBuffer();
}

void ULevel::Release()
{

	for (auto& RenderList : AllRenderers)
	{
		auto EndItr = RenderList.second.end();
		for (auto Itr = RenderList.second.begin(); Itr != EndItr;)
		{
			USpriteRendererComponent* Renderer = *Itr;
			if (!Renderer->GetOwner()->CheckDestroy())
			{
				Itr++;
				continue;
			}
			Itr = RenderList.second.erase(Itr);
		}
	}

	for (std::list<AActor*>::iterator Itr = AllActors.begin(); Itr != AllActors.end();)
	{
		AActor* CurActor = *Itr;
		if (false == CurActor->CheckDestroy())
		{
			Itr++;
			continue;
		}
		delete CurActor;
		Itr = AllActors.erase(Itr);
	}
}

void ULevel::PivotDebugOn()
{
	for (AActor* Actor : AllActors)
	{
		if (false == Actor->IsActivated())
		{
			continue;
		}
		if (nullptr != Actor)
		{
			Actor->SetActorDebug(true);
		}
	}
}

void ULevel::PivotDebugOff()
{
	for (AActor* Actor : AllActors)
	{
		if (false == Actor->IsActivated())
		{
			continue;
		}
		if (nullptr != Actor)
		{
			Actor->SetActorDebug(false);
		}
	}
}

void ULevel::SwapBuffer()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* WindowImage = UEngineAPICore::GetWindowBuffer();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();

	FTransform Transform;
	Transform.Location = MainWindow.GetWindowSize().Half();
	Transform.Scale = MainWindow.GetWindowSize();

	BackBufferImage->CopyToBit(WindowImage, Transform);
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetEngineWindow();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -1, -1, Size.iX() + 2, Size.iY() + 2);
}

void ULevel::PushRenderer(USpriteRendererComponent* _Renderer)
{
	int Order = _Renderer->GetOrder();
	AllRenderers[Order].push_back(_Renderer);
}

void ULevel::ChangeRenderOrder(USpriteRendererComponent* _Renderer, int _PrevOrder)
{
	AllRenderers[_PrevOrder].remove(_Renderer);
	int Order = _Renderer->GetOrder();
	AllRenderers[Order].push_back(_Renderer);
}
