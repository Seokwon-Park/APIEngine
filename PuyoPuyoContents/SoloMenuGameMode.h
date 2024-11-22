#pragma once
#include "EngineCore/GameMode.h"


// Ό³Έν :
class ASoloMenuGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ASoloMenuGameMode();
	~ASoloMenuGameMode();

	// delete Function
	ASoloMenuGameMode(const ASoloMenuGameMode& _Other) = delete;
	ASoloMenuGameMode(ASoloMenuGameMode&& _Other) noexcept = delete;
	ASoloMenuGameMode& operator=(const ASoloMenuGameMode& _Other) = delete;
	ASoloMenuGameMode& operator=(ASoloMenuGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
protected:

private:
};

