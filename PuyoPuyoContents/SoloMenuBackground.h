#pragma once

#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>


// Ό³Έν :
class ASoloMenuBackground : public AActor
{
public:
	// constrcuter destructer
	ASoloMenuBackground();
	~ASoloMenuBackground();

	// delete Function
	ASoloMenuBackground(const ASoloMenuBackground& _Other) = delete;
	ASoloMenuBackground(ASoloMenuBackground&& _Other) noexcept = delete;
	ASoloMenuBackground& operator=(const ASoloMenuBackground& _Other) = delete;
	ASoloMenuBackground& operator=(ASoloMenuBackground&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;

protected:
	virtual void BeginPlay() override;
private:
	std::vector<std::vector<USpriteRendererComponent*>> BgRenderers;


};

