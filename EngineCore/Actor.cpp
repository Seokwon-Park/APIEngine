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
		UEngineDebugHelper::SetDebugPos(Pos - CameraPos, UEngineDebugHelper::EDebugPosType::Circle);
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




