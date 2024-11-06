#pragma once
#include <EngineBase/EngineRandom.h>
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AMenuBackground : public AActor
{
public:
	// constrcuter destructer
	AMenuBackground();
	~AMenuBackground();

	// delete Function
	AMenuBackground(const AMenuBackground& _Other) = delete;
	AMenuBackground(AMenuBackground&& _Other) noexcept = delete;
	AMenuBackground& operator=(const AMenuBackground& _Other) = delete;
	AMenuBackground& operator=(AMenuBackground&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;

protected:
	virtual void BeginPlay() override;
private:
	UEngineRandom Random;
	std::vector<int> Selected;
	std::vector<std::vector<int>> Combinations;
	std::vector<std::vector<USpriteRendererComponent*>> BgRenderers;
	std::vector<UAnimatorComponent*> BgAnimators;
};

