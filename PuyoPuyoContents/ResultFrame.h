#pragma once

#include "NameText.h"
#include "PuyoText.h"
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AResultFrame : public AActor
{
public:
	// constrcuter destructer
	AResultFrame();
	~AResultFrame();

	// delete Function
	AResultFrame(const AResultFrame& _Other) = delete;
	AResultFrame(AResultFrame&& _Other) noexcept = delete;
	AResultFrame& operator=(const AResultFrame& _Other) = delete;
	AResultFrame& operator=(AResultFrame&& _Other) noexcept = delete;

	void OpenFrame();
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::vector<USpriteRendererComponent*> Frames;
	std::vector<UAnimatorComponent*> FrameAnimator;
	std::vector<ANameText*> NameTexts;

	const std::vector<FVector2D> FrameLoc = {
	FVector2D(0,144),FVector2D(176,144),FVector2D(0,240),FVector2D(176,240),
	FVector2D(176,160),FVector2D(16,240),FVector2D(16,144),FVector2D(0,160)
	};
	const std::vector<FVector2D> FrameScale =
	{
		FVector2D(16,16),FVector2D(16,16),FVector2D(16,16),FVector2D(16,16),
		FVector2D(16,80),FVector2D(160,16),FVector2D(160,16),FVector2D(16,80)
	};

	
	
};

