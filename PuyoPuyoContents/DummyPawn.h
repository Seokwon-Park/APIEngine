#pragma once
#include "EngineCore/Actor.h"
#include "EngineCore/SpriteRendererComponent.h"


class ADummyPawn : public AActor
{
public:
	ADummyPawn();
	~ADummyPawn();
	// delete Function
	ADummyPawn(const ADummyPawn& _Other) = delete;
	ADummyPawn(ADummyPawn&& _Other) noexcept = delete;
	ADummyPawn& operator=(const ADummyPawn& _Other) = delete;
	ADummyPawn& operator=(ADummyPawn&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay() override;

private:
};

