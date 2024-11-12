#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class APuyoBoomFX : public AActor
{
public:
	// constrcuter destructer
	APuyoBoomFX();
	~APuyoBoomFX();

	// delete Function
	APuyoBoomFX(const APuyoBoomFX& _Other) = delete;
	APuyoBoomFX(APuyoBoomFX&& _Other) noexcept = delete;
	APuyoBoomFX& operator=(const APuyoBoomFX& _Other) = delete;
	APuyoBoomFX& operator=(APuyoBoomFX&& _Other) noexcept = delete;

	void Tick(float _DeltaTime)override;

	void SetupBoomFX(EPuyoColor _Color, float _Delay);
protected:
	void BeginPlay() override;
private:
	std::string SpriteName;
	std::vector<std::string> ColorSprites;
	std::vector<USpriteRendererComponent*> Particles;
	std::vector<float> A;
	std::vector<FVector2D> XYStart;
	std::vector<FVector2D> Top;
	std::vector<FVector2D> Dir;
	float FXTimer = 0.0f;
	float FXDelay = 0.0f;
};

