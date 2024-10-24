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

void ULevel::Tick()
{
	for (AActor* Actor : AllActors)
	{
		if (nullptr != Actor)
		{
			Actor->Tick();
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
