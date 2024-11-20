#pragma once
#include "PlayGameMode.h"

#include "SoloFrame.h"
#include "SoloBackground.h"
// ���� :
class ASoloPlayGameMode : public APlayGameMode
{
public:
	// constrcuter destructer
	ASoloPlayGameMode();
	~ASoloPlayGameMode();

	// delete Function
	ASoloPlayGameMode(const ASoloPlayGameMode& _Other) = delete;
	ASoloPlayGameMode(ASoloPlayGameMode&& _Other) noexcept = delete;
	ASoloPlayGameMode& operator=(const ASoloPlayGameMode& _Other) = delete;
	ASoloPlayGameMode& operator=(ASoloPlayGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	class APuyoPlayerController* ControllerP1;
	class APuyoAIController* ControllerP2;
};
