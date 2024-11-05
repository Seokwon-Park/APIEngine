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

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void MoveFunction(FVector2D _Dir);
protected:

private:
	float Speed = 100.0f;
	//int MySpriteIndex = 0;

	//USpriteRendererComponent* Sr;
};

