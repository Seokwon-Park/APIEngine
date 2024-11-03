#pragma once
#include "Puyo.h"

#include <EngineCore/Actor.h>

enum class EPuyoLogicStep
{
	PuyoCreate, // 뿌요 블럭 생성
	PuyoMove, // 뿌요 움직임
	PuyoBlockUpdate, // 뿌요가 닿았을 때? 옆에 친구가 떨어져야 할수도 있다.
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

	void SetupPuyoBoard(FVector2D _Offset, FVector2D _PuyoSize, FVector2D _BoardSize = FVector2D(6,13));

	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoBlockUpdateLogic(float _DeltaTime);
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();

	FVector2D GetPosByIndex(int _X, int _Y);
	bool CanMoveDown();
	bool CanMoveLR(FVector2D _Dir);

	void MoveLR(FVector2D _Dir);
	void Rotate();
	void PuyoForceDown();
protected:

private:
	const int Dx[4] = { 0, 1, 0, -1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	FVector2D Offset;
	FVector2D PuyoSize;
	FVector2D BoardSize;
	float PuyoDropTimer;
	float PuyoDropDelay;
	int PuyoTick;
	int BlockX;
	int BlockY;
	int Dir; // 0,1,2,3 시계방향으로 위,오른쪽,아래,왼쪽
	EPuyoLogicStep CurStep;
	std::vector<APuyo*> Block; // 0번 뿌요를 기준으로 회전
	std::vector<std::vector<APuyo*>> Board;
};

