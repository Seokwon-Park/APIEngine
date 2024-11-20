#pragma once

#include "PuyoBoard.h"
#include <EngineCore/PlayerController.h>

// ���� :
class APuyoPlayerController : public APlayerController
{
public:
	// constrcuter destructer
	APuyoPlayerController();
	~APuyoPlayerController();

	// delete Function
	APuyoPlayerController(const APuyoPlayerController& _Other) = delete;
	APuyoPlayerController(APuyoPlayerController&& _Other) noexcept = delete;
	APuyoPlayerController& operator=(const APuyoPlayerController& _Other) = delete;
	APuyoPlayerController& operator=(APuyoPlayerController&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	void SetKey(int _CWRotate, int _CCWRotate, int _Down, int _Left, int _Right);
protected:
	virtual void BeginPlay() override;

private:
	APuyoBoard* Board;
	//Key�ڵ� �� ������ �޴� ����
	int CWRotateKey = 0;
	int CCWRotateKey = 0;
	int DownKey = 0;
	int LeftKey = 0;
	int RightKey = 0;
};

