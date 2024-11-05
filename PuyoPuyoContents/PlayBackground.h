#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// ���� :
class APlayBackground : public AActor
{
public:
	// constrcuter destructer
	APlayBackground();
	~APlayBackground();

	// delete Function
	APlayBackground(const APlayBackground& _Other) = delete;
	APlayBackground(APlayBackground&& _Other) noexcept = delete;
	APlayBackground& operator=(const APlayBackground& _Other) = delete;
	APlayBackground& operator=(APlayBackground&& _Other) noexcept = delete;

protected:

private:
	USpriteRendererComponent* Sr;
};

