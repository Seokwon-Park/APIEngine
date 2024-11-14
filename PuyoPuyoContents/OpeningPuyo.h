#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOpeningPuyo : public AActor
{
public:
	// constrcuter destructer
	AOpeningPuyo();
	~AOpeningPuyo();

	// delete Function
	AOpeningPuyo(const AOpeningPuyo& _Other) = delete;
	AOpeningPuyo(AOpeningPuyo&& _Other) noexcept = delete;
	AOpeningPuyo& operator=(const AOpeningPuyo& _Other) = delete;
	AOpeningPuyo& operator=(AOpeningPuyo&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* OPPuyoTop;
	USpriteRendererComponent* OPPuyoBot;
	USpriteRendererComponent* OPPuyoEye;
};

