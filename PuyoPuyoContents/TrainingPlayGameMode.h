#pragma once
#include "PlayGameMode.h"

// Ό³Έν :
class ATrainingPlayGameMode : public APlayGameMode
{
public:
	// constrcuter destructer
	ATrainingPlayGameMode();
	~ATrainingPlayGameMode();

	// delete Function
	ATrainingPlayGameMode(const ATrainingPlayGameMode& _Other) = delete;
	ATrainingPlayGameMode(ATrainingPlayGameMode&& _Other) noexcept = delete;
	ATrainingPlayGameMode& operator=(const ATrainingPlayGameMode& _Other) = delete;
	ATrainingPlayGameMode& operator=(ATrainingPlayGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	class APuyoPlayerController* ControllerP1;
	class APuyoPlayerController* ControllerP2;
};

