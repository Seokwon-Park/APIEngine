#pragma once

#include <EngineCore/SpriteRendererComponent.h>

// 클래스 설명 :
class AGameOverPuyo : public AActor
{
public:
	// Constrcuter Destructer
	AGameOverPuyo();
	~AGameOverPuyo();

	// Delete Function
	AGameOverPuyo(const AGameOverPuyo& _Other) = delete;
	AGameOverPuyo(AGameOverPuyo&& _Other) noexcept = delete;
	AGameOverPuyo& operator=(const AGameOverPuyo& _Other) = delete;
	AGameOverPuyo& operator=(AGameOverPuyo&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Anim;
};
