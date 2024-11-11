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
	// y = AX^2+b
	FVector2D CalcParabola(const float _A, const FVector2D _XYOffset, const float _X)const
	{
		float X = (_X - _XYOffset.X);
		float Y = _A * X * X + _XYOffset.Y;
		return { _X, Y };
	}
protected:
	void BeginPlay() override;
private:
	std::vector<std::string> ColorSprites;
	std::vector<USpriteRendererComponent*> Particles;
	std::vector<float> A;
	std::vector<FVector2D> XYStart;
	std::vector<FVector2D> Top;
	std::vector<FVector2D> Dir;
	float FXTimer = 0.0f;
};

