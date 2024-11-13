#pragma once

#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class APublisherLogo : public AActor
{
public:
	// constrcuter destructer
	APublisherLogo();
	~APublisherLogo();

	// delete Function
	APublisherLogo(const APublisherLogo& _Other) = delete;
	APublisherLogo(APublisherLogo&& _Other) noexcept = delete;
	APublisherLogo& operator=(const APublisherLogo& _Other) = delete;
	APublisherLogo& operator=(APublisherLogo&& _Other) noexcept = delete;

protected:

private:
	USpriteRendererComponent* CKLogo;

};

