#include "aepch.h"
#include "PlayBackground.h"
#include <EngineCore/EngineAPICore.h>

APlayBackground::APlayBackground()
{
	SetActorLocation(UEngineAPICore::GetEngineWindow().GetWindowSize()/2);
	SetActorScale({100,100});

	Sr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	Sr->SetOrder(-1);
	Sr->SetSprite("L1_F.CNS.bmp", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
}

APlayBackground::~APlayBackground()
{
}
