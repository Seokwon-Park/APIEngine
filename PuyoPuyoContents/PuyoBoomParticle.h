#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APuyoBoomParticle : public AActor
{
public:
	// constrcuter destructer
	APuyoBoomParticle();
	~APuyoBoomParticle();

	// delete Function
	APuyoBoomParticle(const APuyoBoomParticle& _Other) = delete;
	APuyoBoomParticle(APuyoBoomParticle&& _Other) noexcept = delete;
	APuyoBoomParticle& operator=(const APuyoBoomParticle& _Other) = delete;
	APuyoBoomParticle& operator=(APuyoBoomParticle&& _Other) noexcept = delete;

	void Tick(float _DeltaTime)override;
protected:
	void BeginPlay() override;
private:

};

