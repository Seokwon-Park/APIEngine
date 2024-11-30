#include "aepch.h"
#include "GameEndText.h"

AGameEndText::AGameEndText()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("GameOver");
	Sr->SetSprite("Kwadankyu");
	Sr->SetComponentScale({ 192, 96 });
	Sr->SetRemoveBackground(true);
	Sr->SetPivot(EPivotType::TopLeft);
}

AGameEndText::~AGameEndText()
{
}


void AGameEndText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (GetActorLocation().Y < 96.0f)
	{
		AddActorLocation(FVector2D::DOWN * _DeltaTime * 50.0f);
	}
	ElapsedTime += _DeltaTime;
	SetActorLocation({ GetActorLocation().X +0.1f* sin(ElapsedTime*5.0f), GetActorLocation().Y});
}
void AGameEndText::BeginPlay()
{
	Super::BeginPlay();
}
