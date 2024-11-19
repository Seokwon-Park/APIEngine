#include "aepch.h"
#include "PuyoChainFX.h"

APuyoChainFX::APuyoChainFX()
{
	ColorSprites.push_back("ChainFXR");
	ColorSprites.push_back("ChainFXB");
	Animator = CreateDefaultSubobject<UAnimatorComponent>("ChainFXAnim");
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("ChainFX");
	Sr->SetSprite(ColorSprites[0]);
	Sr->SetOrder(200);
	Sr->SetRemoveBackground(true);
	Sr->SetComponentScale({ 32,32 });
	Sr->SetAnimator(Animator);
	for (int i = 0; i < 2; i++)
	{
		Animator->CreateAnimation("Start" + std::to_string(i), ColorSprites[i], {0, 1}, {0.1f, 0.1f}, false);
		Animator->CreateAnimation("Loop" + std::to_string(i), ColorSprites[i], { 2, 3 }, { 0.1f, 0.1f });
		Animator->CreateAnimation("Pop" + std::to_string(i), ColorSprites[i], { 4,5,6,7 }, .1f, false);

		Animator->SetAnimationEvent("Start" + std::to_string(i), 1, std::bind(&APuyoChainFX::ChangeScaleAndAnimation, this));
		Animator->SetAnimationEvent("Pop" + std::to_string(i), 3, std::bind(&APuyoChainFX::Destroy, this, 0.0f));
		Animator->SetAnimationEvent("Pop" + std::to_string(i), 3, [=]() { Target->UpdateWarning(); });
	}
}

APuyoChainFX::~APuyoChainFX()
{
}


void APuyoChainFX::SetupChainFX(APuyoWarn* _Target, FVector2D _Start, FVector2D _End, EPuyoBoardColor _Color, bool _IsCounter, float _Duration, 
	APuyoWarn* _CounterWarn, FVector2D _CounterTarget)
{
	Target = _Target;
	StartLocation = _Start;
	TargetLocation = _End;
	Duration = _Duration;
	Elapsed = 0.0f;
	Color = static_cast<int>(_Color);
	if (_IsCounter)
	{
		Animator->SetAnimationEvent("Pop" + std::to_string(Color), 3, [=]()
			{
				APuyoChainFX* APCF = GetWorld()->SpawnActor<APuyoChainFX>();  
				APCF->SetupChainFX(_CounterWarn, _End, _CounterTarget, _Color, false);
			});
	}
	Sr->SetSprite(ColorSprites[Color]);
	Animator->ChangeAnimation("Start"+std::to_string(Color));
}

void APuyoChainFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Elapsed += _DeltaTime;
	if (Elapsed < Duration)
	{
		SetActorLocation(FVector2D::BezierLerp(StartLocation, { StartLocation.X, TargetLocation.Y }, TargetLocation, Elapsed / Duration));
		return;
	}
	Animator->ChangeAnimation("Pop" + std::to_string(Color));
}

void APuyoChainFX::BeginPlay()
{
	Super::BeginPlay();
}

void APuyoChainFX::ChangeScaleAndAnimation()
{
	Sr->SetComponentScale({ 64,64 });
	Sr->SetSprite(ColorSprites[0], 2);
	Animator->ChangeAnimation("Loop" + std::to_string(Color));
}
