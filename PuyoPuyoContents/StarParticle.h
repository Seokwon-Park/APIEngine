#pragma once
#include "Star.h"

// Ό³Έν :
class AStarParticle : public AActor
{
public:
	// constrcuter destructer
	AStarParticle();
	~AStarParticle();

	// delete Function
	AStarParticle(const AStarParticle& _Other) = delete;
	AStarParticle(AStarParticle&& _Other) noexcept = delete;
	AStarParticle& operator=(const AStarParticle& _Other) = delete;
	AStarParticle& operator=(AStarParticle&& _Other) noexcept = delete;

	void Init(FVector2D _Location);
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	
};

