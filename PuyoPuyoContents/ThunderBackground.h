#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AThunderBackground : public AActor
{
public:
	// constrcuter destructer
	AThunderBackground();
	~AThunderBackground();

	// delete Function
	AThunderBackground(const AThunderBackground& _Other) = delete;
	AThunderBackground(AThunderBackground&& _Other) noexcept = delete;
	AThunderBackground& operator=(const AThunderBackground& _Other) = delete;
	AThunderBackground& operator=(AThunderBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	USpriteRendererComponent* YellowSr;
	bool Temp = false;
	float Timer = 0.0f;
};

