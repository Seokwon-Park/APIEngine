#pragma once

#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOpeningCoin : public AActor
{
public:
	// constrcuter destructer
	AOpeningCoin();
	~AOpeningCoin();

	// delete Function
	AOpeningCoin(const AOpeningCoin& _Other) = delete;
	AOpeningCoin(AOpeningCoin&& _Other) noexcept = delete;
	AOpeningCoin& operator=(const AOpeningCoin& _Other) = delete;
	AOpeningCoin& operator=(AOpeningCoin&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Anim;
};

