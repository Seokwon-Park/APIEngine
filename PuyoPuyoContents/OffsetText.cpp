#include "aepch.h"
#include "OffsetText.h"

AOffsetText::AOffsetText()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("OffsetText");
	Sr->SetOrder(ERenderLayer::Warn);
	Sr->SetComponentScale({ 64,32 });
	Sr->SetRemoveBackground(true);
	Sr->SetPivot(EPivotType::TopLeft);
}

AOffsetText::~AOffsetText()
{
}


void AOffsetText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::DOWN * _DeltaTime * 50.0f);
	
}
void AOffsetText::BeginPlay()
{
	Super::BeginPlay();
}
