#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AGameEndText : public AActor
{
public:
	// constrcuter destructer
	AGameEndText();
	~AGameEndText();

	// delete Function
	AGameEndText(const AGameEndText& _Other) = delete;
	AGameEndText(AGameEndText&& _Other) noexcept = delete;
	AGameEndText& operator=(const AGameEndText& _Other) = delete;
	AGameEndText& operator=(AGameEndText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	float ElapsedTime = 0.0f;

};

