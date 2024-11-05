#include "aepch.h"
#include "IntroBackground.h"

AIntroBackground::AIntroBackground()
{
	SetActorLocation(UEngineAPICore::GetEngineWindow().GetWindowSize() / 2);
	SetActorScale({ 100,100 });

	Sr = CreateDefaultSubobject<USpriteRendererComponent>("IntroBackground");
	Sr->SetOrder(-1);
	Sr->SetSprite("AAA.CNS.BMP", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
}

AIntroBackground::~AIntroBackground()
{
}

void AIntroBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Sr->SetSprite("OP_LINE.CNS.BMP", 0);

}

void AIntroBackground::BeginPlay()
{
	Super::BeginPlay();
}
