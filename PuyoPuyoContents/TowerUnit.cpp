#include "aepch.h"
#include "TowerUnit.h"

ATowerUnit::ATowerUnit()
{
	Pillar = CreateDefaultSubobject<USpriteRendererComponent>("");
	Pillar->SetSprite("Tower");
	for (int i = 0; i < 2; i++)
	{
		Side[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		Side[i]->SetSprite("TOWEREdge");
	}
}

ATowerUnit::~ATowerUnit()
{
}

void ATowerUnit::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerUnit::SetupPillar(FVector2D _Scale, int _Floor)
{
	Pillar->SetSprite("Tower", _Floor);
	Pillar->SetComponentScale(_Scale);

}

void ATowerUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
