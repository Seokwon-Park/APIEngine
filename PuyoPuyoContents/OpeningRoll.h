#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOpeningRoll : public AActor
{
public:
	// constrcuter destructer
	AOpeningRoll();
	~AOpeningRoll();

	// delete Function
	AOpeningRoll(const AOpeningRoll& _Other) = delete;
	AOpeningRoll(AOpeningRoll&& _Other) noexcept = delete;
	AOpeningRoll& operator=(const AOpeningRoll& _Other) = delete;
	AOpeningRoll& operator=(AOpeningRoll&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
};

