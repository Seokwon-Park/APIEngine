#pragma once

#include "PuyoWarn.h"
#include <EngineCore/SpriteRendererComponent.h>

// ���� :
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

	void SetupChainFX(APuyoWarn* _Target, FVector2D _Start, FVector2D _End, EPuyoBoardColor _Color,bool _IsCounter, float _Duration = 1.0f, 
		APuyoWarn* CounterWarn = nullptr, FVector2D _CounterTarget = FVector2D::ZERO);

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
	int Color = 0;
	bool IsCounter = false;
	APuyoWarn* Target = nullptr;
	std::vector<std::string> ColorSprites;
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Animator;

};

