#include "aepch.h"
#include "Level.h"
#include "EngineAPICore.h"

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

	for (AActor* Actor : AllActors)
	{
		if (nullptr != Actor)
		{
			Actor->Render();
		}
	}

	SwapBuffer();
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetEngineWindow();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -1, -1, Size.iX()+2, Size.iY() + 2);
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
