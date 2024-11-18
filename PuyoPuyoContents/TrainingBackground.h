#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ATrainingBackground : public AActor
{
public:
	// constrcuter destructer
	ATrainingBackground();
	~ATrainingBackground();

	// delete Function
	ATrainingBackground(const ATrainingBackground& _Other) = delete;
	ATrainingBackground(ATrainingBackground&& _Other) noexcept = delete;
	ATrainingBackground& operator=(const ATrainingBackground& _Other) = delete;
	ATrainingBackground& operator=(ATrainingBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;

};

