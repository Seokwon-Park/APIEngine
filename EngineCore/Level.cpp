#include "aepch.h"
#include "Level.h"

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
}
