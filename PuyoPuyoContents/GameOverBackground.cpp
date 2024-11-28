#include "aepch.h"
#include "GameOverBackground.h"

AGameOverBackground::AGameOverBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("GameOverBG");
	Sr->SetSprite("GameOverBack");
	Sr->SetComponentScale({ 640, 480 });
	Sr->SetPivot(EPivotType::TopLeft);
}

AGameOverBackground::~AGameOverBackground()
{
}


void AGameOverBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AGameOverBackground::BeginPlay()
{
	Super::BeginPlay();
}
