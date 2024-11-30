#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AGameOverBackground : public AActor
{
public:
	// constrcuter destructer
	AGameOverBackground();
	~AGameOverBackground();

	// delete Function
	AGameOverBackground(const AGameOverBackground& _Other) = delete;
	AGameOverBackground(AGameOverBackground&& _Other) noexcept = delete;
	AGameOverBackground& operator=(const AGameOverBackground& _Other) = delete;
	AGameOverBackground& operator=(AGameOverBackground&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	USpriteRendererComponent* Arle;
	USpriteRendererComponent* Continue[3];
	//5*7

};

