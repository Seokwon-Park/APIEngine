#include "aepch.h"
#include "OpeningRoll.h"

AOpeningRoll::AOpeningRoll()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("OpeningRoll");
	Sr->SetSprite("OP_ROLL.CNS.BMP");
	Sr->SetRemoveBackground(true);
	Sr->SetComponentScale({ 640,640 });
	Sr->SetComponentLocation({ 0,-160 });
	Sr->SetPivot(EPivotType::TopLeft);
}

AOpeningRoll::~AOpeningRoll()
{
}


void AOpeningRoll::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Timer += _DeltaTime;
	if (GetActorLocation().Y + Sr->GetComponentLocation().Y <= 0.0f)
	{
		Sr->SetComponentLocation(FVector2D::Lerp({ 0,-160 }, { 0,0 }, Timer/1.0f));
	}
	
}
void AOpeningRoll::BeginPlay()
{
	Super::BeginPlay();
}
