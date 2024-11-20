#pragma once
#include <EngineCore/AIController.h>

#include "PuyoBoard.h"

enum class EPuyoAIState
{
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

	std::vector<std::vector<int>> WeightBoard;

	UEngineRandom RandomDevice;

	EPuyoAIState State = EPuyoAIState::Down;
};

