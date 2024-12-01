#include "aepch.h"
#include "TowerUnit.h"

ATowerUnit::ATowerUnit()
{
	Pillar = CreateDefaultSubobject<USpriteRendererComponent>("");
	Pillar->SetSprite("Tower");
	Pillar->SetPivot(EPivotType::BottomCenter);
	Pillar->SetRemoveColor(UColor(255, 0, 0, 0));
	Pillar->SetOrder(ERenderLayer::BottomCover);
	for (int i = 0; i < 2; i++)
	{
		Side[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		Side[i]->SetSprite("TOWEREdge",i);
		Side[i]->SetComponentScale({16,16});
		Side[i]->SetRemoveColor(UColor(255, 0, 0, 0));
		Side[i]->SetOrder(ERenderLayer::BottomCover);

	}
	Side[0]->SetPivot(EPivotType::BottomRight);
	Side[1]->SetPivot(EPivotType::BottomLeft);
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
	Side[0]->SetComponentLocation({ -_Scale.Half().X, 0.0f });
	Side[1]->SetComponentLocation({ _Scale.Half().X, 0.0f });
}

void ATowerUnit::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
