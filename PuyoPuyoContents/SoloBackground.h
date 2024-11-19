#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ASoloBackground : public AActor
{
public:
	// constrcuter destructer
	ASoloBackground();
	~ASoloBackground();

	// delete Function
	ASoloBackground(const ASoloBackground& _Other) = delete;
	ASoloBackground(ASoloBackground&& _Other) noexcept = delete;
	ASoloBackground& operator=(const ASoloBackground& _Other) = delete;
	ASoloBackground& operator=(ASoloBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;

};

