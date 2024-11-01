#include "aepch.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>

APlayMap::APlayMap()
{
	SetActorLocation(UEngineAPICore::GetEngineWindow().GetWindowSize()/2);
	SetActorScale({100,100});

	Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	Sr->SetOrder(-1);
	Sr->SetSprite("L1_F.CNS.bmp", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
}

APlayMap::~APlayMap()
{
}
