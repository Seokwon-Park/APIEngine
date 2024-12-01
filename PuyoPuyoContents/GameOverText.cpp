#include "aepch.h"
#include "GameOverText.h"

AGameOverText::AGameOverText()
{
	Sr.resize(8, nullptr);
	float PosX = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		Sr[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		Sr[i]->SetSprite("GameOverText",SpriteIndex[i]);
		Sr[i]->SetComponentScale(SpriteSize[i]);
		Sr[i]->SetPivot(EPivotType::TopLeft);
		Sr[i]->SetComponentLocation({ PosX ,0.0f});
		PosX += SpriteSize[i].X-4.0f;
		Sr[i]->SetRemoveBackground(true);
		Sr[i]->SetOrder(ERenderLayer::Text);

	}
}

AGameOverText::~AGameOverText()
{
}

void AGameOverText::BeginPlay()
{
	Super::BeginPlay();
}

void AGameOverText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsWave)
	{
		Timer += _DeltaTime;
		for (int i = 0; i < 8; ++i) {
			float BaseY = Sr[i]->GetComponentLocation().Y;
			float y = 15.0f * std::sin(10.0f * Timer + i * 1.5f);
			Sr[i]->SetComponentLocation({ Sr[i]->GetComponentLocation().X, y });
		}
	}
	else
	{
		for (int i = 0; i < 8; ++i) 
		{
			Sr[i]->SetComponentLocation({ Sr[i]->GetComponentLocation().X, 0.0f });
		}
	}
	
}
