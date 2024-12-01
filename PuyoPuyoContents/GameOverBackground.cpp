#include "aepch.h"
#include "GameOverBackground.h"

AGameOverBackground::AGameOverBackground()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("GameOverBG");
	Sr->SetSprite("GameOverBack");
	Sr->SetComponentScale({ 640, 480 });
	Sr->SetPivot(EPivotType::TopLeft);

	Arle = CreateDefaultSubobject<USpriteRendererComponent>("GameOverArle");
	Arle->SetSprite("GameOverArle");
	Arle->SetComponentScale({ 256, 112 });
	Arle->SetComponentLocation({ 192, 304 });
	Arle->SetPivot(EPivotType::TopLeft);

	for (int i = 0; i < 3; i++)
	{
		Continue[i]= CreateDefaultSubobject<USpriteRendererComponent>("GameOverArle");
		Continue[i]->SetSprite("GameOverContinue");
		Continue[i]->SetComponentScale({ 432, 32 });
		Continue[i]->SetComponentLocation({i * 432,432});
		Continue[i]->SetPivot(EPivotType::TopLeft);

	}
}

AGameOverBackground::~AGameOverBackground()
{
}


void AGameOverBackground::RemoveText()
{
	for (int i = 0; i < 3; i++)
	{
		Continue[i]->SetActive(false);
	}
}

void AGameOverBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	for (int i = 0; i < 3; i++)
	{
		Continue[i]->SetComponentLocation(Continue[i]->GetComponentLocation() + FVector2D::LEFT * _DeltaTime * 100.0f);
		if (Continue[i]->GetComponentLocation().X < -432.0f)
		{
			Continue[i]->SetComponentLocation({ 864.0f,432.0f });
		}
	}
}
void AGameOverBackground::BeginPlay()
{
	Super::BeginPlay();
}
