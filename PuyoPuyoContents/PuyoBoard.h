#pragma once
#include "Puyo.h"

#include <EngineCore/Actor.h>

enum PuyoLogicStep
{
	PuyoCreate,
	PuyoMove,
	PuyoCheck,
	PuyoDestroy,
	PuyoUpdate,
};
// 설명 :
class APuyoBoard : public AActor
{
public:
	// constrcuter destructer
	APuyoBoard();
	~APuyoBoard();

	// delete Function
	APuyoBoard(const APuyoBoard& _Other) = delete;
	APuyoBoard(APuyoBoard&& _Other) noexcept = delete;
	APuyoBoard& operator=(const APuyoBoard& _Other) = delete;
	APuyoBoard& operator=(APuyoBoard&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();

	FVector2D GetPosByIndex(int _X, int _Y);
	bool CanMoveDown();

	void Move(FVector2D _Dir);
	void PuyoForceDown();
protected:

private:
	FVector2D Offset;
	float PuyoDropTimer;
	float PuyoDropDelay;
	int PuyoTick;
	int BlockX;
	int BlockY;
	int Dir; // 0,1,2,3 시계방향으로 위,오른쪽,아래,왼쪽
	PuyoLogicStep CurStep;
	std::vector<APuyo*> Block; // 0번 뿌요를 기준으로 회전
	std::vector<std::vector<APuyo*>> Board;
};

