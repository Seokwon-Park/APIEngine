#pragma once

#include "PuyoWarn.h"
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class APuyoChainFX : public AActor
{
public:
	// constrcuter destructer
	APuyoChainFX();
	~APuyoChainFX();

	// delete Function
	APuyoChainFX(const APuyoChainFX& _Other) = delete;
	APuyoChainFX(APuyoChainFX&& _Other) noexcept = delete;
	APuyoChainFX& operator=(const APuyoChainFX& _Other) = delete;
	APuyoChainFX& operator=(APuyoChainFX&& _Other) noexcept = delete;

	void SetupChainFX(APuyoWarn* _Target, FVector2D _Start, FVector2D _End, int _Amount, float _Duration = 1.0f);

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	void ChangeScaleAndAnimation();
	FVector2D StartLocation;
	FVector2D TargetLocation;
	float Elapsed = 0.0f;
	float Duration;
	int AttackAmount = 0;
	APuyoWarn* Target = nullptr;
	std::vector<std::string> ColorSprites;
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Animator;

};

