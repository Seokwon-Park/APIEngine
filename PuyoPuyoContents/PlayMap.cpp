#include "aepch.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>

APlayMap::APlayMap()
{
	FVector2D WindowSize = UEngineAPICore::GetEngineWindow().GetWindowSize();

	SetActorScale(WindowSize);
	SetActorLocation(WindowSize.Half());
}

APlayMap::~APlayMap()
{
}
