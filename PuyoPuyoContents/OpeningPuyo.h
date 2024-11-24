#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// ���� :
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
	
	void Init();
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* OPPuyoTop;
	USpriteRendererComponent* OPPuyoBot;
	USpriteRendererComponent* OPPuyoEyeL;
	USpriteRendererComponent* OPPuyoEyeR;

	float Time = 0.0f;
};

