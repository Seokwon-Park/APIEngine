#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ATrainingFrame : public AActor
{
public:
	// constrcuter destructer
	ATrainingFrame();
	~ATrainingFrame();

	// delete Function
	ATrainingFrame(const ATrainingFrame& _Other) = delete;
	ATrainingFrame(ATrainingFrame&& _Other) noexcept = delete;
	ATrainingFrame& operator=(const ATrainingFrame& _Other) = delete;
	ATrainingFrame& operator=(ATrainingFrame&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

