#include "aepch.h"
#include "OpeningCompile.h"

AOpeningCompile::AOpeningCompile()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("Compile");
	Sr->SetComponentScale({ 416,32 });
	Sr->SetRemoveBackground(true);
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetOrder(ERenderLayer::Warn);
}

AOpeningCompile::~AOpeningCompile()
{
}

void AOpeningCompile::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AOpeningCompile::BeginPlay()
{
	Super::BeginPlay();
}

