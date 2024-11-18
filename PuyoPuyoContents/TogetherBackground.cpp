#include "aepch.h"
#include "TogetherBackground.h"
#include <EngineCore/EngineAPICore.h>

ATogetherBackground::ATogetherBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	Sr->SetOrder(ERenderLayer::BACKGROUND);
	Sr->SetSprite("VSBG", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	Sr->SetPivot(EPivotType::TopLeft);
}

ATogetherBackground::~ATogetherBackground()
{
}

void ATogetherBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATogetherBackground::BeginPlay()
{
	Super::BeginPlay();
}
