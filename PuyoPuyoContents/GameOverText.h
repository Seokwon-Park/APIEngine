#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AGameOverText : public AActor
{
public:
	// constrcuter destructer
	AGameOverText();
	~AGameOverText();

	// delete Function
	AGameOverText(const AGameOverText& _Other) = delete;
	AGameOverText(AGameOverText&& _Other) noexcept = delete;
	AGameOverText& operator=(const AGameOverText& _Other) = delete;
	AGameOverText& operator=(AGameOverText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	float ElapsedTime = 0.0f;

};

