#pragma once

#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AFader : public AActor
{
public:
	// constrcuter destructer
	AFader();
	~AFader();

	// delete Function
	AFader(const AFader& _Other) = delete;
	AFader(AFader&& _Other) noexcept = delete;
	AFader& operator=(const AFader& _Other) = delete;
	AFader& operator=(AFader&& _Other) noexcept = delete;

	// Lighter and Lighter
	void FadeIn(float _Duration);
	// Darker and Darker
	void FadeOut(float _Duration);

	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay() override;
private:
	USpriteRendererComponent* FadeRenderer;
	float Start = 0.0f;
	float End = 1.0f;
	float ElapsedTime = 1.0f;
	float Duration = 1.0f;
	bool IsFading = false;
};

