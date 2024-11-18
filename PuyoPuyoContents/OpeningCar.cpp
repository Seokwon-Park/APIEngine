#include "aepch.h"
#include "OpeningCar.h"

AOpeningCar::AOpeningCar()
{
	OPCar = CreateDefaultSubobject<USpriteRendererComponent>("");
	OPCar->SetSprite("OPCAR");
	OPCar->SetComponentScale({ 448, 480 });
	OPCar->SetRemoveBackground(true);
	OPCar->SetPivot(EPivotType::TopLeft);
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

