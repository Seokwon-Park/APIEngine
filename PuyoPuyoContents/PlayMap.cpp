#include "aepch.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>

APlayMap::APlayMap()
{
	SetActorLocation({ 640, 360 });
	SetActorScale({100,100});

	Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	Sr->SetOrder(-1);
	Sr->SetSprite("toko_bg2.cns.bmp", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
}

APlayMap::~APlayMap()
{
}
