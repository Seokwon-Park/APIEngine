#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ASoloFrame : public AActor
{
public:
	// constrcuter destructer
	ASoloFrame();
	~ASoloFrame();

	// delete Function
	ASoloFrame(const ASoloFrame& _Other) = delete;
	ASoloFrame(ASoloFrame&& _Other) noexcept = delete;
	ASoloFrame& operator=(const ASoloFrame& _Other) = delete;
	ASoloFrame& operator=(ASoloFrame&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* HeadSr;
	USpriteRendererComponent* CenterSr;
	USpriteRendererComponent* LeftSideSr;
	USpriteRendererComponent* InnerLeftSideSr;
	USpriteRendererComponent* RightSideSr;
	USpriteRendererComponent* InnerRightSideSr;
	USpriteRendererComponent* TailSr;

};

