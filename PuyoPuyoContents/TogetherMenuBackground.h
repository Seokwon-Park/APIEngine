#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ATogetherMenuBackground : public AActor
{
public:
	// constrcuter destructer
	ATogetherMenuBackground();
	~ATogetherMenuBackground();

	// delete Function
	ATogetherMenuBackground(const ATogetherMenuBackground& _Other) = delete;
	ATogetherMenuBackground(ATogetherMenuBackground&& _Other) noexcept = delete;
	ATogetherMenuBackground& operator=(const ATogetherMenuBackground& _Other) = delete;
	ATogetherMenuBackground& operator=(ATogetherMenuBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;

};

