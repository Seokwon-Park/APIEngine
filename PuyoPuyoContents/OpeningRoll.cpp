#include "aepch.h"
#include "OpeningRoll.h"

AOpeningRoll::AOpeningRoll()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("OpeningRoll");
	Sr->SetSprite("OP_ROLL.CNS.BMP");
	Sr->SetRemoveBackground(true);
	Sr->SetComponentScale({ 640,480 });
}

AOpeningRoll::~AOpeningRoll()
{
}


void AOpeningRoll::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOpeningRoll::BeginPlay()
{
	Super::BeginPlay();
}
