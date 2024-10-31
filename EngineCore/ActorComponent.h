#pragma once
#include <EngineBase/Object.h>

// Ό³Έν :
class UActorComponent : public UObject
{
public:
	// constrcuter destructer
	UActorComponent();
	virtual ~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

protected:

private:
	class AActor* ParentActor;

};

