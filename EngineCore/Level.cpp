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
	for (AActor* Actor : AllActors)
	{
		if (nullptr != Actor)
		{
			Actor->Render();
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
