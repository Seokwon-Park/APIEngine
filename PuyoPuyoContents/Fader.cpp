#include "aepch.h"
#include "Fader.h"

AFader::AFader()
{
	FadeRenderer = CreateDefaultSubobject<USpriteRendererComponent>("Fader");
	FadeRenderer->SetSprite("Black");
	FadeRenderer->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	FadeRenderer->SetAlpha(0);
	FadeRenderer->SetPivot(EPivotType::TopLeft);

}

AFader::~AFader()
{
}

void AFader::BeginPlay()
{
	Super::BeginPlay();
}

void AFader::FadeIn(float _Duration)
{
	Duration = _Duration;
	Start = 1.0f;
	End = 0.0f;
	ElapsedTime = 0.0f;
	FadeRenderer->SetAlphaRate(Start);
	IsFading = true;
}

void AFader::FadeOut(float _Duration)
{
	Duration = _Duration;
	Start = 0.0f;
	End = 1.0f;
	ElapsedTime = 0.0f;
	FadeRenderer->SetAlphaRate(Start);
	IsFading = true;
}

void AFader::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsFading)
	{
		ElapsedTime += _DeltaTime;
		float Alpha = FEngineMath::Lerp(Start, End, ElapsedTime / Duration);
		FadeRenderer->SetAlphaRate(Alpha);
		if (ElapsedTime >= Duration+1.0f)
		{
			IsFading = false;
		}
	}
}
