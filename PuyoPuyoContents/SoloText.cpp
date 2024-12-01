#include "aepch.h"
#include "SoloText.h"

ASoloText::ASoloText()
{
	Sr.resize(8);
	for (int i = 0; i < 8; i++)
	{
		Sr[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		Sr[i]->SetSprite("EnemySelectText", i);
		Sr[i]->SetComponentScale({ 32,32 });
		Sr[i]->SetRemoveBackground(true);
		Sr[i]->SetRemoveColor({3,3});
		Sr[i]->SetPivot(EPivotType::TopLeft);
	}
	for (int i = 0; i < 3; i++)
	{
		Sr[i]->SetComponentLocation({ 32 + i*32, 0});

	}
	for (int i = 0; i < 5; i++)
	{
		Sr[i+3]->SetComponentLocation({ i * 32, 32 });

	}
}

ASoloText::~ASoloText()
{
}


void ASoloText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ASoloText::BeginPlay()
{
	Super::BeginPlay();
}
