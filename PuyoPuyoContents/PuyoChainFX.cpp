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
	Animator->CreateAnimation("Start", ColorSprites[0], { 0, 1 }, { 0.1f, 0.1f }, false);
	Animator->CreateAnimation("Loop", ColorSprites[0], { 2, 3 }, { 0.1f, 0.1f });
	Animator->CreateAnimation("Pop", ColorSprites[0], {4,5,6,7}, .1f, false);
	Animator->ChangeAnimation("Start");
	Animator->SetAnimationEvent("Start", 1, std::bind(&APuyoChainFX::ChangeScaleAndAnimation, this));
	Animator->SetAnimationEvent("Pop", 3, std::bind(&APuyoChainFX::Destroy, this, 0.0f));
	Animator->SetAnimationEvent("Pop", 3, [=]() {Target->AddWarnNums(AttackAmount);  Target->UpdateWarning(); });

}

APuyoChainFX::~APuyoChainFX()
{
}


void APuyoChainFX::SetupChainFX(APuyoBoard* _Target, FVector2D _Start, FVector2D _End, int _Amount, float _Duration)
{
	Target = _Target;
	StartLocation = _Start;
	TargetLocation = _End;
	Duration = _Duration;
	Elapsed = 0.0f;
	AttackAmount = _Amount;
}

void APuyoChainFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Elapsed += _DeltaTime;
	if (Elapsed < Duration)
	{
		SetActorLocation(FVector2D::Lerp(StartLocation, TargetLocation, Elapsed / Duration));
		return;
	}
	Animator->ChangeAnimation("Pop");


}
void APuyoChainFX::BeginPlay()
{
	Super::BeginPlay();
}

void APuyoChainFX::ChangeScaleAndAnimation()
{
	Sr->SetComponentScale({ 64,64 });
	Sr->SetSprite(ColorSprites[0], 2);
	Animator->ChangeAnimation("Loop");


}
