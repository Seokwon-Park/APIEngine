#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AIntroBackground : public AActor
{
public:
	// constrcuter destructer
	AIntroBackground();
	~AIntroBackground();

	// delete Function
	AIntroBackground(const AIntroBackground& _Other) = delete;
	AIntroBackground(AIntroBackground&& _Other) noexcept = delete;
	AIntroBackground& operator=(const AIntroBackground& _Other) = delete;
	AIntroBackground& operator=(AIntroBackground&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;

protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr[2];
	UAnimatorComponent* Animator;
	float WaitTimer = .5f;
};

