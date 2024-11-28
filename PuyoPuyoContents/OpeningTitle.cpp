#include "aepch.h"
#include "OpeningTitle.h"

AOpeningTitle::AOpeningTitle()
{
	Sr.resize(4, nullptr);
	for (int i = 0; i < 4; i++)
	{
		Sr[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		if (i % 2 == 0)
		{
			Sr[i]->SetSprite("Pu");
			Sr[i]->SetComponentScale({108,96});
		}
		else
		{
			Sr[i]->SetSprite("Yo");
			Sr[i]->SetComponentScale({ 116,96 });
		}
		Sr[i]->SetRemoveBackground(true);
		Sr[i]->SetActive(false);
		Sr[i]->SetPivot(EPivotType::TopLeft);
	}
}

AOpeningTitle::~AOpeningTitle()
{
}


void AOpeningTitle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOpeningTitle::BeginPlay()
{
	Super::BeginPlay();
}
