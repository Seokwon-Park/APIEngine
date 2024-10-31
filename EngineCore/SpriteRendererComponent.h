#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class SpriteRendererComponent : public USceneComponent
{
public:
	// constrcuter destructer
	SpriteRendererComponent();
	~SpriteRendererComponent();

	// delete Function
	SpriteRendererComponent(const SpriteRendererComponent& _Other) = delete;
	SpriteRendererComponent(SpriteRendererComponent&& _Other) noexcept = delete;
	SpriteRendererComponent& operator=(const SpriteRendererComponent& _Other) = delete;
	SpriteRendererComponent& operator=(SpriteRendererComponent&& _Other) noexcept = delete;

protected:

private:
	class UEngineSprite* Sprite;
	int CurIndex;
};

