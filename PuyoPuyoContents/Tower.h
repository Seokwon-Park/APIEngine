#pragma once
#include "TowerUnit.h"

// Ό³Έν :
class ATower : public AActor
{
public:
	// constrcuter destructer
	ATower();
	~ATower();

	// delete Function
	ATower(const ATower& _Other) = delete;
	ATower(ATower&& _Other) noexcept = delete;
	ATower& operator=(const ATower& _Other) = delete;
	ATower& operator=(ATower&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	const std::vector<FVector2D> TowerSize =
	{
		FVector2D(256,80),
		FVector2D(224,80),
		FVector2D(192,80),
		FVector2D(160,80),
		FVector2D(128,80),
		FVector2D(96,80),
		FVector2D(64,16)
	};
	ATowerUnit* Test;
};

