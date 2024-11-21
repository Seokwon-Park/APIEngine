#pragma once
#include "PuyoBoard.h"
#include "PlayFrame.h"
#include "PlayBackground.h"

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

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	APuyoBoard* PuyoBoardP1;
	APuyoBoard* PuyoBoardP2;

	APlayFrame* Frame;
	APlayBackground* Background;
private:

};

