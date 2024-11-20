#pragma once
#include "ActorComponent.h"

// Ό³Έν :
class UInputComponent : public UActorComponent
{
public:
	// constrcuter destructer
	UInputComponent();
	~UInputComponent();

	// delete Function
	UInputComponent(const UInputComponent& _Other) = delete;
	UInputComponent(UInputComponent&& _Other) noexcept = delete;
	UInputComponent& operator=(const UInputComponent& _Other) = delete;
	UInputComponent& operator=(UInputComponent&& _Other) noexcept = delete;

	virtual void TickComponent(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

