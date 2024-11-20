#include "aepch.h"
#include "Actor.h"
#include "ImageManager.h"
 
#include <EngineCore/EngineAPICore.h>

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

void AActor::Tick(float _DeltaTime)
{
	if (true == IsDebug)
	{
		FVector2D Pos = GetActorLocation();
		FVector2D CameraPos = GetWorld()->GetCameraPos();
		EngineDebugHelper::SetDebugPos(Pos - CameraPos, EngineDebugHelper::EDebugPosType::Circle);
	}

	for (auto Component : Components)
	{
		if (false == Component->IsActivated())
		{
			continue;
		}
		if (nullptr != Component)
		{
			Component->TickComponent(_DeltaTime);
		}
	}
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




