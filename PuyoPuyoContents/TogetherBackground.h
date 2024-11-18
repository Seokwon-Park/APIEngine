#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ATogetherBackground : public AActor
{
public:
	// constrcuter destructer
	ATogetherBackground();
	~ATogetherBackground();

	// delete Function
	ATogetherBackground(const ATogetherBackground& _Other) = delete;
	ATogetherBackground(ATogetherBackground&& _Other) noexcept = delete;
	ATogetherBackground& operator=(const ATogetherBackground& _Other) = delete;
	ATogetherBackground& operator=(ATogetherBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;

};

