#pragma once
#include "Puyo.h"

#include <EngineCore/Actor.h>

enum class EPuyoLogicStep
{
	PuyoCreate, // 뿌요 블럭 생성
	PuyoMove, // 뿌요 움직임
	PuyoPlace, // 뿌요 착지로직
	PuyoConnect, // 뿌요 연결 로직
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

	void SetupPuyoBoard(FVector2D _Offset, FVector2D _PuyoSize, FIntPoint _BoardSize = FIntPoint(6,13));
	std::vector<APuyo*> CreatePuyoBlock();

	//LogicStep
	void PuyoCreateLogic();
	void PuyoMoveLogic();
	void PuyoPlaceLogic(float _DeltaTime);
	void PuyoConnectLogic(float _DeltaTime);
	void PuyoCheckLogic();
	void PuyoDestroyLogic();
	void PuyoUpdateLogic();

	FVector2D GetLocationByIndex(int _X, int _Y);
	bool CanMoveDown();
	bool CanMoveLR(FVector2D _Dir);

	void MoveLR(FVector2D _Dir);
	void Rotate();
	void PuyoForceDown();
protected:

private:
	//위쪽 방향부터 반시계 방향으로 -> 위쪽 -> 왼쪽 -> 아래쪽 -> 오른쪽
	const int Dx[4] = { 0, -1, 0, 1 };
	const int Dy[4] = { -1, 0, 1, 0 };
	FVector2D Offset;
	FVector2D PuyoSize;
	FIntPoint BoardSize;
	// Slave Puyo
	FIntPoint MainPuyoCoord;
	float PuyoDropTimer;
	float PuyoDropDelay;
	int PuyoTick;
	int Dir; // 0,1,2,3 시계방향으로 위,오른쪽,아래,왼쪽
	EPuyoLogicStep CurStep;
	std::vector<APuyo*> Block; // 0번 뿌요를 기준으로 회전
	std::vector<APuyo*> NextBlock; // 다음뿌요
	std::vector<APuyo*> NextNextBlock; // 다음다음뿌요
	std::vector<FIntPoint> PuyoConnectList;
	std::vector<FIntPoint> PlaceCheckList;
	
	std::vector<std::vector<APuyo*>> Board;
};

