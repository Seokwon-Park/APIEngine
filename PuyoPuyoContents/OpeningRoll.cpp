#include "aepch.h"
#include "OpeningRoll.h"

AOpeningRoll::AOpeningRoll()
{
	Anim = CreateDefaultSubobject<UAnimatorComponent>("");
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("OpeningRoll");
	Sr->SetSprite("OP_ROLL.CNS.Bmp");
	Sr->SetRemoveBackground(true);
	Sr->SetComponentScale({ 640,640 });
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetAnimator(Anim);

	Anim->CreateAnimation("ToSepia", "SepiaRoll", { 0,1,2,3,4,5 }, 0.1f, false);
	Anim->SetAnimationEvent("ToSepia", 1, [=]() {SepiaFilter->SetActive(true); });

	SepiaFilter = CreateDefaultSubobject<USpriteRendererComponent>("");
	SepiaFilter->SetSprite("Sepia");
	SepiaFilter->SetAlphaRate(0.0f);
	SepiaFilter->SetComponentScale({ 640,480 });
	SepiaFilter->SetPivot(EPivotType::TopLeft);
	SepiaFilter->SetOrder(ERenderLayer::TitleSepia);
	SepiaFilter->SetActive(false);
}

AOpeningRoll::~AOpeningRoll()
{
}


void AOpeningRoll::SetupRoll(FVector2D _Start, float _TargetY, float _Speed)
{
	TargetY = _TargetY;
	Speed = _Speed;
	SetActorLocation(_Start);
	Amount = abs(TargetY - GetActorLocation().Y);
	if(TargetY - GetActorLocation().Y <0)
	{
		Dir = -1;
	}
	else
	{
		Dir = 1;
	}
}

void AOpeningRoll::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (Amount > 0.0f)
	{
		Amount -= Speed * _DeltaTime;
		AddActorLocation(FVector2D::DOWN * Dir * Speed * _DeltaTime);
	}
	
}
void AOpeningRoll::BeginPlay()
{
	Super::BeginPlay();
}
