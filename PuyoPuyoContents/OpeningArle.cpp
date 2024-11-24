#include "aepch.h"
#include "OpeningArle.h"

AOpeningArle::AOpeningArle()
{
	OPArle = CreateDefaultSubobject<USpriteRendererComponent>("");
	OPArle ->SetSprite("OPARLE");
	OPArle ->SetComponentScale({ 640, 480 });
	OPArle ->SetRemoveBackground(true);
	OPArle ->SetPivot(EPivotType::TopLeft);

	OPArleFinger.resize(4, nullptr);
	for (int i = 0; i < 4; i++)
	{
		OPArleFinger[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		OPArleFinger[i]->SetSprite("OPFINGER",i);

		OPArleFinger[i]->SetRemoveBackground(true);
		OPArleFinger[i]->SetPivot(EPivotType::BottomLeft);
	}

	OPArleFinger[0]->SetComponentScale({ 144, 104 });
	OPArleFinger[0]->SetComponentLocation({ 0,584 });

	OPArleFinger[1]->SetComponentScale({ 176, 104 });
	OPArleFinger[1]->SetComponentLocation({ 8,688 });

	OPArleFinger[2]->SetComponentScale({ 144, 104 });
	OPArleFinger[2]->SetComponentLocation({ 328,584 });

	OPArleFinger[3]->SetComponentScale({ 176, 104 });
	OPArleFinger[3]->SetComponentLocation({ 288,688 });
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

	if (OPArleFinger[1]->GetComponentLocation().Y < 480)return;
	for (int i = 0; i < 4; i++)
	{
		OPArleFinger[i]->SetComponentLocation(OPArleFinger[i]->GetComponentLocation() + FVector2D::UP * _DeltaTime * 100.0f);
	}
}

