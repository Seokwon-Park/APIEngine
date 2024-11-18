#include "aepch.h"
#include "OpeningArle.h"

AOpeningArle::AOpeningArle()
{
	OPArle = CreateDefaultSubobject<USpriteRendererComponent>("");
	OPArle ->SetSprite("OPARLE");
	OPArle ->SetComponentScale({ 640, 480 });
	OPArle ->SetRemoveBackground(true);
	OPArle ->SetPivot(EPivotType::TopLeft);
}

AOpeningArle::~AOpeningArle()
{
}

void AOpeningArle::BeginPlay()
{
	Super::BeginPlay();
}

void AOpeningArle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

