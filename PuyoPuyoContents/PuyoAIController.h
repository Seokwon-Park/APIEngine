#pragma once
#include <EngineCore/AIController.h>

#include "PuyoBoard.h"

enum class EPuyoAIState
{
	Calculation,
	Down,
	Left,
	Right,
	Rotate
};
// Ό³Έν :
class APuyoAIController : public AAIController
{
public:
	// constrcuter destructer
	APuyoAIController();
	~APuyoAIController();

	// delete Function
	APuyoAIController(const APuyoAIController& _Other) = delete;
	APuyoAIController(APuyoAIController&& _Other) noexcept = delete;
	APuyoAIController& operator=(const APuyoAIController& _Other) = delete;
	APuyoAIController& operator=(APuyoAIController&& _Other) noexcept = delete;

	inline void SetThinkDelay(float _Delay) { ThinkDelay = _Delay; }
	void ReceiveBlockColors();
	void CalculateBoard();
	void DebugEvaluateBoard();
	int CalculateBFS(int x, int y);

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	const int Dx[4] = { 0,-1,0,1 };
	const int Dy[4] = { -1,0,1,0 };

	APuyoBoard* Board = nullptr;
	UEngineRandom RandomDevice;
	EPuyoAIState State = EPuyoAIState::Calculation;
	std::vector<std::vector<int>> BoardState;
	std::vector<std::vector<std::vector<int>>> EvaluateBoard;
	float ThinkTime = 0.0f;
	float ThinkDelay = 0.3f;
	std::vector<int> BlockColors;


	int TargetX = 0;
	int TargetY = 12;
	int TargetDir;
};

