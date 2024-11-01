#pragma once
#include "EngineCore/Actor.h"
#include "EngineCore/SpriteRendererComponent.h"


class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();
	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);
protected:

private:
	float Speed = 100.0f;
	int MySpriteIndex = 0;

	USpriteRendererComponent* Sr;
};

