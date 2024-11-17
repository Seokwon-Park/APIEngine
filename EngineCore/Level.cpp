#include "aepch.h"
#include "Level.h"
#include "EngineAPICore.h"
#include "SpriteRendererComponent.h"



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
	GetInputSystem().BindAction(EKey::MouseRight, KeyEvent::Down, std::bind(&EngineDebugHelper::PivotDebugSwitch));

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
	while(false == WaitForBeginPlay.empty())
	{
		AActor* SpawnedActor = WaitForBeginPlay.front();
		WaitForBeginPlay.pop();
		SpawnedActor->BeginPlay();
		AllActors.push_back(SpawnedActor);
	}

	InputSystem.KeyCheck(_DeltaTime);

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
	InputSystem.EventCheck();

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

	if (UEngineWindow::Resize != UEngineAPICore::GetEngineWindow().GetWindowSize())
	{
		UEngineWinImage* BackBuffer = UEngineAPICore::GetBackBuffer();
		UEngineWinImage* NewBack = new UEngineWinImage();
		NewBack->Create(BackBuffer, UEngineWindow::Resize);
		StretchBlt(NewBack->GetDC(), 0, 0, UEngineWindow::Resize.iX(), UEngineWindow::Resize.iY(), BackBuffer->GetDC(), 0, 0, 640, 480, SRCCOPY);

		&BackBuffer = &NewBack;

		delete BackBuffer;
	}

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
