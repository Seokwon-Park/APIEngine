#include "aepch.h"
#include "Fader.h"

AFader::AFader()
{
	FadeRenderer = CreateDefaultSubobject<USpriteRendererComponent>("Fader");
	FadeRenderer->SetSprite("Black");
	FadeRenderer->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	FadeRenderer->SetAlphaChar(150);
	FadeRenderer->SetPivot(EPivotType::TopLeft);

}

AFader::~AFader()
{
}

void AFader::BeginPlay()
{
	Super::BeginPlay();
}

void AFader::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Alpha += 1;
	FadeRenderer->SetAlphaChar(Alpha);
}
