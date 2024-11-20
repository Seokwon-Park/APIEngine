#include "aepch.h"
#include "SoloBackground.h"

#include <EngineCore/EngineAPICore.h>

ASoloBackground::ASoloBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("SoloBackground");
	Sr->SetOrder(ERenderLayer::BACKGROUND);
	Sr->SetSprite("LVBG", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	Sr->SetPivot(EPivotType::TopLeft);
}

ASoloBackground::~ASoloBackground()
{
}


void ASoloBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ASoloBackground::BeginPlay()
{
	Super::BeginPlay();
}
