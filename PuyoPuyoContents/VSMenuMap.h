#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AVSMenuMap : public AActor
{
public:
	// constrcuter destructer
	AVSMenuMap();
	~AVSMenuMap();

	// delete Function
	AVSMenuMap(const AVSMenuMap& _Other) = delete;
	AVSMenuMap(AVSMenuMap&& _Other) noexcept = delete;
	AVSMenuMap& operator=(const AVSMenuMap& _Other) = delete;
	AVSMenuMap& operator=(AVSMenuMap&& _Other) noexcept = delete;

	inline void Setup(int _Index) { MapRenderer->SetSprite("VSBG", _Index); }
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	const std::vector<FVector2D> FrameLoc = {
		FVector2D(0,0),FVector2D(16,0),FVector2D(320,0),
		FVector2D(0,16),FVector2D(328,16),
		FVector2D(0,240),FVector2D(16,240),FVector2D(320,240)
	};
	const std::vector<FVector2D> FrameScale = 
	{
		FVector2D(16,16),FVector2D(304,16),FVector2D(16,16),
		FVector2D(8,224),FVector2D(8,224),
		FVector2D(16,16),FVector2D(304,16),FVector2D(16,16)
	};

	USpriteRendererComponent* MapRenderer;
	std::vector<USpriteRendererComponent*> Frame;
};

