#pragma once
#include <EngineCore/SpriteRendererComponent.h>
// Ό³Έν :
class APuyo : public AActor
{
public:
	// constrcuter destructer
	APuyo();
	~APuyo();

	// delete Function
	APuyo(const APuyo& _Other) = delete;
	APuyo(APuyo&& _Other) noexcept = delete;
	APuyo& operator=(const APuyo& _Other) = delete;
	APuyo& operator=(APuyo&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
protected:

private:
	USpriteRendererComponent* Sr;
};

