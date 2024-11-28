#pragma once
#include "EngineCore/GameMode.h"


// Ό³Έν :
class AGameOverGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AGameOverGameMode();
	~AGameOverGameMode();

	// delete Function
	AGameOverGameMode(const AGameOverGameMode& _Other) = delete;
	AGameOverGameMode(AGameOverGameMode&& _Other) noexcept = delete;
	AGameOverGameMode& operator=(const AGameOverGameMode& _Other) = delete;
	AGameOverGameMode& operator=(AGameOverGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};

