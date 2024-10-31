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
	for (AActor* Actor : AllActors)
	{
		if (nullptr != Actor)
		{
			Actor->BeginPlay();
		}
	}
}

void ULevel::Tick(float _DeltaTime)
{
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
