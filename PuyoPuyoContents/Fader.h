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

	void Tick(float _DeltaTime) override;

	
protected:
	void BeginPlay() override;
private:
	USpriteRendererComponent* FadeRenderer;
	unsigned char Alpha = 0;

};

