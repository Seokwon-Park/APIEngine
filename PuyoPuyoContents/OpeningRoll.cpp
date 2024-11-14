#include "aepch.h"
#include "OpeningRoll.h"

AOpeningRoll::AOpeningRoll()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("OpeningRoll");
	Sr->SetSprite("OP_ROLL.CNS.BMP");
	Sr->SetRemoveBackground(true);
	Sr->SetComponentScale({ 640,640 });
	Sr->SetComponentLocation({ 0,-160});
	Sr->SetPivot(EPivotType::TopLeft);
}

AOpeningRoll::~AOpeningRoll()
{
}


void AOpeningRoll::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::DOWN * _DeltaTime);
}
void AOpeningRoll::BeginPlay()
{
	Super::BeginPlay();
}