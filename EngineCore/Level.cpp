#include "aepch.h"
#include "Level.h"
#include "EngineAPICore.h"
#include "SpriteRendererComponent.h"

ULevel::ULevel()
{
}

//RAII - SpawnActor<>();
ULevel::~ULevel()
{
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

	for (AActor* Actor : AllActors)
	{
		if (nullptr != Actor)
		{
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render()
{
	ScreenClear();

	for (auto& RenderList : AllRenderers)
	{
		for (USpriteRendererComponent* Renderer : RenderList.second)
		{
			Renderer->Render();
		}
	}

	UEngineDebugHelper::PrintEngineDebugText();

	SwapBuffer();
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
