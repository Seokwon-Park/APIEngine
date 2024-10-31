#pragma once
#include "ActorComponent.h"

// Ό³Έν :
class USceneComponent : public UActorComponent
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	inline FVector2D GetComponentScale() { return Transform.Scale; }
	inline FVector2D GetComponentLocation() { return Transform.Location; }
	inline FTransform GetTransform() { return Transform; }

	inline void SetComponentScale(FVector2D _Scale) { Transform.Scale = _Scale; }
	inline void SetComponentLocation(FVector2D _Location) { Transform.Location = _Location; }

	FTransform GetWorldTransform();


protected:
	FTransform Transform; //Relative

private:

};

