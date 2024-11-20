#pragma once
#include "Controller.h"

// Ό³Έν :
class AAIController : public AController
{
public:
	// constrcuter destructer
	AAIController();
	~AAIController();

	// delete Function
	AAIController(const AAIController& _Other) = delete;
	AAIController(AAIController&& _Other) noexcept = delete;
	AAIController& operator=(const AAIController& _Other) = delete;
	AAIController& operator=(AAIController&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

