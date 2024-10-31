#include "aepch.h"
#include "Actor.h"
#include "ImageManager.h"
 
#include <EngineCore/EngineAPICore.h>
#include "ActorComponent.h"

AActor::AActor()
	:World(nullptr), Transform(FTransform())
{
}

AActor::~AActor()
{
	for (auto Component : Components)
	{
		if (nullptr != Component)
		{
			delete Component;
			Component = nullptr;
		}
	}

	Components.clear();
}

void AActor::BeginPlay()
{
	for (auto Component : Components)
	{
		if (nullptr != Component)
		{
			Component->BeginPlay();
		}
	}
}




