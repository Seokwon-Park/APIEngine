#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ATogetherFrame : public AActor
{
public:
	// constrcuter destructer
	ATogetherFrame();
	~ATogetherFrame();

	// delete Function
	ATogetherFrame(const ATogetherFrame& _Other) = delete;
	ATogetherFrame(ATogetherFrame&& _Other) noexcept = delete;
	ATogetherFrame& operator=(const ATogetherFrame& _Other) = delete;
	ATogetherFrame& operator=(ATogetherFrame&& _Other) noexcept = delete;

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

