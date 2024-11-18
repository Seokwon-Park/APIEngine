#include "aepch.h"
#include "GameOverText.h"

AGameOverText::AGameOverText()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("GameOver");
	Sr->SetSprite("Gameovertext");
	Sr->SetComponentScale({ 192, 96 });
	Sr->SetRemoveBackground(true);
	Sr->SetPivot(EPivotType::TopLeft);
}

AGameOverText::~AGameOverText()
{
}


void AGameOverText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (GetActorLocation().Y < 96.0f)
	{
		AddActorLocation(FVector2D::DOWN * _DeltaTime * 50.0f);
	}
	ElapsedTime += _DeltaTime;
	SetActorLocation({ GetActorLocation().X +0.1f* sin(ElapsedTime*5.0f), GetActorLocation().Y});
}
void AGameOverText::BeginPlay()
{
	Super::BeginPlay();
}
