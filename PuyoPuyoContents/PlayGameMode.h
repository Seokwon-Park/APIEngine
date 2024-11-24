#pragma once
#include "PuyoBoard.h"
#include "PlayFrame.h"
#include "PlayBackground.h"
#include "BottomFrame.h"
#include "BottomBackground.h"


// Ό³Έν :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	inline std::pair<APlayFrame*, APlayBackground*> GetMapPtr() { return { Frame, Background }; }
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	APuyoBoard* PuyoBoardP1;
	APuyoBoard* PuyoBoardP2;

	APlayFrame* Frame;
	APlayBackground* Background;
	ABottomBackground* BotBackgroundL;
	ABottomBackground* BotBackgroundR;
	std::vector<ABottomFrame*> BotFrameL;
	std::vector<ABottomFrame*> BotFrameR;
private:

};

