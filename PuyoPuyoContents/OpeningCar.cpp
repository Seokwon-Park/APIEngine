#include "aepch.h"
#include "OpeningCar.h"

AOpeningCar::AOpeningCar()
{
	OPCar = CreateDefaultSubobject<USpriteRendererComponent>("");
	OPCar->SetSprite("OPCAR");
	OPCar->SetComponentScale({ 448, 480 });
	OPCar->SetRemoveBackground(true);
	OPCar->SetPivot(EPivotType::TopLeft);

	Anim = CreateDefaultSubobject<UAnimatorComponent>("");
	OPCarJewel = CreateDefaultSubobject<USpriteRendererComponent>("");
	OPCarJewel->SetSprite("OPCARJEWEL");
	OPCarJewel->SetComponentScale({ 48, 72 });
	OPCarJewel->SetComponentLocation({ 0, 220});
	OPCarJewel->SetRemoveBackground(true);
	OPCarJewel->SetPivot(EPivotType::TopLeft);
	OPCarJewel->SetAnimator(Anim);

	Anim->CreateAnimation("Bling", "OPCARJEWEL",0,4, 0.1f, false);
	Anim->ChangeAnimation("Bling");
}

AOpeningCar::~AOpeningCar()
{
}

void AOpeningCar::BeginPlay()
{
	Super::BeginPlay();
}

void AOpeningCar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

