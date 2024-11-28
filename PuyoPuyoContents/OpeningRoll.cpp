#include "aepch.h"
#include "OpeningRoll.h"

AOpeningRoll::AOpeningRoll()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("OpeningRoll");
	Sr->SetSprite("OP_ROLL.CNS.BMP");
	Sr->SetRemoveBackground(true);
	Sr->SetComponentScale({ 640,640 });
	Sr->SetPivot(EPivotType::TopLeft);
}

AOpeningRoll::~AOpeningRoll()
{
}


void AOpeningRoll::SetupRoll(FVector2D _Start, float _TargetY, float _Speed)
{
	TargetY = _TargetY;
	Speed = _Speed;
	SetActorLocation(_Start);
}

void AOpeningRoll::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (GetActorLocation().Y < TargetY)
	{
		AddActorLocation(FVector2D::DOWN * Speed * _DeltaTime);
	}
	
}
void AOpeningRoll::BeginPlay()
{
	Super::BeginPlay();
}
