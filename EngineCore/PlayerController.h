#pragma once
#include "Controller.h"
#include "InputComponent.h"

// Ό³Έν :
class APlayerController : public AController
{
public:
	// constrcuter destructer
	APlayerController();
	~APlayerController();

	// delete Function
	APlayerController(const APlayerController& _Other) = delete;
	APlayerController(APlayerController&& _Other) noexcept = delete;
	APlayerController& operator=(const APlayerController& _Other) = delete;
	APlayerController& operator=(APlayerController&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UInputComponent* InputComponent;
private:
};

