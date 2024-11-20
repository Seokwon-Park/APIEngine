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

	void CalculateBoard();

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	APuyoBoard* Board = nullptr;
	UEngineRandom RandomDevice;
	EPuyoAIState State = EPuyoAIState::Calculation;
	std::vector<std::vector<int>> BoardState;
	std::vector<std::vector<std::vector<int>>> EvaluateBoard;
	float Delay = 0.0f;

	int TargetX;
	int TargetY;
	int TargetDir;
};

