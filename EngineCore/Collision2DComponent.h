#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class UCollision2DComponent : public USceneComponent
{
public:
	// constrcuter destructer
	UCollision2DComponent();
	~UCollision2DComponent();

	// delete Function
	UCollision2DComponent(const UCollision2DComponent& _Other) = delete;
	UCollision2DComponent(UCollision2DComponent&& _Other) noexcept = delete;
	UCollision2DComponent& operator=(const UCollision2DComponent& _Other) = delete;
	UCollision2DComponent& operator=(UCollision2DComponent&& _Other) noexcept = delete;

	void BeginPlay() override {};
	void TickComponent(float _DeltaTime) override {};
protected:

private:

};

