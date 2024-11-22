#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOptionsValue : public AActor
{
public:
	// constrcuter destructer
	AOptionsValue();
	~AOptionsValue();

	// delete Function
	AOptionsValue(const AOptionsValue& _Other) = delete;
	AOptionsValue(AOptionsValue&& _Other) noexcept = delete;
	AOptionsValue& operator=(const AOptionsValue& _Other) = delete;
	AOptionsValue& operator=(AOptionsValue&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
};

