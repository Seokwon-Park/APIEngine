#include "aepch.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent()
{
}

USceneComponent::~USceneComponent()
{
}

FTransform USceneComponent::GetWorldTransform()
{
	FTransform ActorTransform = GetOwner()->GetTransform();
	FTransform Result;

	Result.Location = ActorTransform.Location + Transform.Location;
	Result.Scale = Transform.Scale;
	return Result;
}
