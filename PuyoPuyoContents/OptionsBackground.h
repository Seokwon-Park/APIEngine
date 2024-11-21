#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOptionsBackground : public AActor
{
public:
	// constrcuter destructer
	AOptionsBackground();
	~AOptionsBackground();

	// delete Function
	AOptionsBackground(const AOptionsBackground& _Other) = delete;
	AOptionsBackground(AOptionsBackground&& _Other) noexcept = delete;
	AOptionsBackground& operator=(const AOptionsBackground& _Other) = delete;
	AOptionsBackground& operator=(AOptionsBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
};

