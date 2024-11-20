#pragma once
#include "PlayGameMode.h"

#include "TogetherFrame.h"
#include "TogetherBackground.h"

// ³Ê¶û³ª¶û »Ñ¿ä»Ñ¿ä
class ATogetherPlayGameMode : public APlayGameMode
{
public:
	// constrcuter destructer
	ATogetherPlayGameMode();
	~ATogetherPlayGameMode();

	// delete Function
	ATogetherPlayGameMode(const ATogetherPlayGameMode& _Other) = delete;
	ATogetherPlayGameMode(ATogetherPlayGameMode&& _Other) noexcept = delete;
	ATogetherPlayGameMode& operator=(const ATogetherPlayGameMode& _Other) = delete;
	ATogetherPlayGameMode& operator=(ATogetherPlayGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;
protected:
	void Tick(float _DeltaTime) override;
private:
	class APuyoPlayerController* ControllerP1;
	class APuyoPlayerController* ControllerP2;

};

