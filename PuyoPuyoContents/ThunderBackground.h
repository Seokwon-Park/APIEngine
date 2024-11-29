#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AThunderBackground : public AActor
{
public:
	// constrcuter destructer
	AThunderBackground();
	~AThunderBackground();

	// delete Function
	AThunderBackground(const AThunderBackground& _Other) = delete;
	AThunderBackground(AThunderBackground&& _Other) noexcept = delete;
	AThunderBackground& operator=(const AThunderBackground& _Other) = delete;
	AThunderBackground& operator=(AThunderBackground&& _Other) noexcept = delete;

	inline void SetColor(std::string_view _ColorName) { ColorSr->SetSprite(_ColorName); }
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	USpriteRendererComponent* ColorSr;
	bool Temp = false;
	float Timer = 0.0f;
	int Counter = 0;
};

