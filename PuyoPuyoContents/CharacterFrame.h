#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ACharacterFrame : public AActor
{
public:
	// constrcuter destructer
	ACharacterFrame();
	~ACharacterFrame();

	// delete Function
	ACharacterFrame(const ACharacterFrame& _Other) = delete;
	ACharacterFrame(ACharacterFrame&& _Other) noexcept = delete;
	ACharacterFrame& operator=(const ACharacterFrame& _Other) = delete;
	ACharacterFrame& operator=(ACharacterFrame&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	//bool IsPlayer = false;
	USpriteRendererComponent* CharacterImage;
	USpriteRendererComponent* FrameRenderer;
	USpriteRendererComponent* InfoFrameRenderer;
};

