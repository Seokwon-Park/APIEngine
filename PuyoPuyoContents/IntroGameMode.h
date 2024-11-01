#pragma once
#include "EngineCore/GameMode.h"

// Ό³Έν :
class AIntroGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AIntroGameMode();
	~AIntroGameMode();

	// delete Function
	AIntroGameMode(const AIntroGameMode& _Other) = delete;
	AIntroGameMode(AIntroGameMode&& _Other) noexcept = delete;
	AIntroGameMode& operator=(const AIntroGameMode& _Other) = delete;
	AIntroGameMode& operator=(AIntroGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void MoveScene();

protected:

private:
	
};

